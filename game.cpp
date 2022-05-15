#include "game.h"

game::game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(0);
	}
	isRunning = true;
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
	{
		this->bullets[bulletIndex] = NULL;
	}
	for (int villianIndex = 0; villianIndex < MAX_VILLIANS; villianIndex++)
	{
		this->villian_obj[villianIndex] = NULL;
	}
	this->Asteroid_obj = NULL;
	//rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(0);
	};
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "bullet hell");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazkow 
	charset = SDL_LoadBMP("./cs8x8.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);
	SDL_SetColorKey(charset, true, 0x000000);

	background = SDL_LoadBMP("./bmp/backgroundDuzy.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	hero_bmp = SDL_LoadBMP("./bmp/hero.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	alien1 = SDL_LoadBMP("./bmp/alien1.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	alien2 = SDL_LoadBMP("./bmp/alien2.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	alien3 = SDL_LoadBMP("./bmp/alien3.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	bullet_bmp = SDL_LoadBMP("./bmp/bulletS.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);	

	ogien1 = SDL_LoadBMP("./bmp/ogien1.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	ogien2 = SDL_LoadBMP("./bmp/ogien2.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	ogien3 = SDL_LoadBMP("./bmp/ogien3.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barVillian3 = SDL_LoadBMP("./bmp/barVillian3.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barVillian2 = SDL_LoadBMP("./bmp/barVillian2.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barVillian1 = SDL_LoadBMP("./bmp/barVillian1.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero1 = SDL_LoadBMP("./bmp/heroBar1.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero2= SDL_LoadBMP("./bmp/heroBar2.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero3 = SDL_LoadBMP("./bmp/heroBar3.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero4 = SDL_LoadBMP("./bmp/heroBar4.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero5 = SDL_LoadBMP("./bmp/heroBar5.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero6 = SDL_LoadBMP("./bmp/heroBar6.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero7 = SDL_LoadBMP("./bmp/heroBar7.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero8 = SDL_LoadBMP("./bmp/heroBar8.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero9 = SDL_LoadBMP("./bmp/heroBar9.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	barHero10 = SDL_LoadBMP("./bmp/heroBar10.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	astronaut_bmp = SDL_LoadBMP("./bmp/guy.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);

	endBackground = SDL_LoadBMP("./bmp/newB.bmp");
	CheckAndExecuteLoadError(charset, screen, scrtex, window, renderer);


	t1 = SDL_GetTicks();
	
	frames = 0;
	framesNotPerSecond = 0;
	fpsTimer = 0;
	fps = 0;
	worldTime = 0;
	distance = 0;
	distance2 = 0;
	heroSpeed = 15;
	villianSpeed = 1;
	isRunning = true;
	aPressed = false;
	isMoving = false;
	gameEnded = false;
	
	bgX = SCREEN_WIDTH/6;
	bgY = SCREEN_HEIGHT/2;
	x = bgX;
	y = bgY;
	bulletx = x;
	bullety = y;
	
	this->initializeVillians();
	heros = new Hero(x, y, hero_bmp);
	Asteroid_obj = new Asteroid(bgX, y, astronaut_bmp, -10);
	printf("zainicializowane\n");	
}
void game::initializeVillians()
{
	villian_obj[0] = new villian(bgX + SCREEN_WIDTH + 100, bgY, alien1, 3, 0, 0, 1);	
	villian_obj[1] = new villian(bgX + SCREEN_WIDTH + 400, bgY - 300, alien1, 3, 0, 0, 2);
	villian_obj[2] = new villian(bgX + SCREEN_WIDTH + 600, bgY + 400, alien1, 3, 0, 0, 3);
	villian_obj[3] = new villian(bgX + SCREEN_WIDTH + 800, bgY + 200, alien1, 3, 0, 0, 4);
	villian_obj[4] = new villian(bgX + SCREEN_WIDTH + 1300, bgY - 420, alien1, 3, 0, 0, 5);
	villian_obj[5] = new villian(bgX + 3 * SCREEN_WIDTH - 300, SCREEN_HEIGHT / 2 + cos(distance2 - 3) * SCREEN_HEIGHT / 2.5, alien2, 3, 0, 0, 6);
	villian_obj[6] = new villian(bgX + 3 * SCREEN_WIDTH, SCREEN_HEIGHT / 2 + cos(0.5 * distance2) * SCREEN_HEIGHT / 3, alien2, 3, 0, 0, 7);
	villian_obj[7] = new villian(bgX + 3 * SCREEN_WIDTH + 1000, SCREEN_HEIGHT / 2 + cos(1.5 * distance2) * SCREEN_HEIGHT / 3, alien2, 3, 0, 0, 8);
	villian_obj[8] = new villian(bgX + 3*SCREEN_WIDTH + sin(distance2 * 2) * SCREEN_HEIGHT / 3 + 500, bgY, alien3, 3, 0, 0, 8);
}

void game::handleEvent(SDL_Event event)
{	
	switch (event.type) {

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			this->isRunning=false;
		/*else if (event.key.keysym.sym == SDLK_w)
			heroSpeed += 5;
		else if (event.key.keysym.sym == SDLK_s)
			heroSpeed -= 5;*/
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			x -= heroSpeed;
			
			//bgX += heroSpeed;
			//if (bgX >= SCREEN_WIDTH-100)
				//bgX = SCREEN_WIDTH-100;
			if (x < 0)
				x = 0;
			isMoving = true;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			x += heroSpeed;			
			/*bgX -= heroSpeed;
			if (bgX <= -1380)
			{
				bgX = -1380;
			}*/
			if (x > SCREEN_WIDTH)
				x = SCREEN_WIDTH;
			isMoving = true;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			y -= heroSpeed;
			
			//bgY += heroSpeed;
			//if (bgY >= SCREEN_HEIGHT + 380)
				//bgY = SCREEN_HEIGHT+380;
			//if (y < 0)
			isMoving = true;
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			y += heroSpeed;
			//bgY -= heroSpeed;
			//if (bgY <= -380)
				//bgY = -380;
			
			if (y > SCREEN_HEIGHT)
				y = SCREEN_HEIGHT;
			isMoving = true;
			
		}
		else if (event.key.keysym.sym == SDLK_SPACE)
		{
			for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
			{
				if (bullets[bulletIndex] == NULL)
				{
					bulletx = x, bullety = y;
					bullets[bulletIndex] = new Bullet(bulletx, bullety, bullet_bmp, 10);
					break;
				}
			}
		}	
	break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_LEFT)
		{			
			isMoving = false;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			isMoving = false;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{			
			isMoving = false;
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{			
			isMoving = false;			
		}
		break;
	};	
}


void game::render()
{
	//linijki kopiowania
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);

}
void game::clean()
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("game cleaned\n");
}
void game::drawObjs()
{
	this->drawHero();
	this->drawBullets();
	this->createVillians();
	this->checkAndExecuteCollisions();
	this->checkAndExeciuteIfHeroWasShot();
	this->drawAsteroid();
	this->checkAndExeciuteAstronautCollision();
}
void game::drawBullets()
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
	{
		if (bullets[bulletIndex] != NULL)
		{
			bullets[bulletIndex]->drawBullet(screen);
		}
	}
}
void game::drawHero()
{
	if (heros != NULL)
	{
		heros->coordsH.hero_x = x;
		heros->coordsH.hero_y = y;
		heros->drawHeros(screen);
		if (isMoving)//make animation
		{
			heros->coords_ogien.hero_x = x;
			heros->coords_ogien.hero_y = y;
			for (int i = 0; i < 10; i++)
			{
				if (frames % 40 == 20 + i)
					heros->drawFire(screen, ogien1);

				if (frames % 40 == i)
					heros->drawFire(screen, ogien3);

				if (frames % 40 == 10 + i)
					heros->drawFire(screen, ogien2);

				if (frames % 40 == 30 + i)
					heros->drawFire(screen, ogien2);

			}
		}
		if(heros->health==1)
		DrawSurface(barHero1, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y-80);

		if (heros->health == 2)
			DrawSurface(barHero2, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 3)
			DrawSurface(barHero3, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 4)
			DrawSurface(barHero4, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 5)
			DrawSurface(barHero5, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 6)
			DrawSurface(barHero6, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 7)
			DrawSurface(barHero7, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 8)
			DrawSurface(barHero8, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 9)
			DrawSurface(barHero9, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);

		if (heros->health == 10)
			DrawSurface(barHero10, heros->coords_ogien.hero_x, heros->coords_ogien.hero_y - 80);
	}
}
void game::checkAndExeciuteIfHeroWasShot()
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
	{
		if (bullets[bulletIndex] != NULL)
		{
			if (heros != NULL)
			{
				if ((bullets[bulletIndex]->coords.pozycja_x <= heros->coordsH.hero_x - 20) && (bullets[bulletIndex]->coords.pozycja_x >= heros->coordsH.hero_x - 40))
				{
					if ((bullets[bulletIndex]->coords.pozycja_y < heros->coordsH.hero_y + 50) && (bullets[bulletIndex]->coords.pozycja_y > heros->coordsH.hero_y - 50))
					{
						printf("health hero przed %d\n", heros->health);
						heros->health = heros->health - 1;
						printf("health hero po %d\n", heros->health);
						delete bullets[bulletIndex];
						bullets[bulletIndex] = NULL;
					}
				}
			}
		}
	}
}
void game::cleanDeadHero()
{
	if (heros != NULL)
	{
		if (heros->health <= 0)
		{
			delete heros;
			heros = NULL;
			gameEnded = true;
		}
	}
}
void game::drawAsteroid()
{	
	if (Asteroid_obj!=NULL&& gameEnded==false)
	{
		if (worldTime > 20)
		{
			Asteroid_obj->coords.pozycja_x = bgX + 2 * SCREEN_WIDTH;
			Asteroid_obj->coords.pozycja_y = SCREEN_HEIGHT / 2 - 100;
			Asteroid_obj->drawAsteroid(screen);
			if (worldTime >= 55 && worldTime <= 56)
			{
				delete Asteroid_obj;
				Asteroid_obj = NULL;
			}
		}
		if (worldTime >= 70)
		{
			Asteroid_obj->coords.pozycja_x = bgX + 4 * SCREEN_WIDTH;
			Asteroid_obj->coords.pozycja_y = SCREEN_HEIGHT / 2 - 200;
			Asteroid_obj->drawAsteroid(screen);
			if (worldTime >= 70 && worldTime <= 71)
			{
				delete Asteroid_obj;
				Asteroid_obj = NULL;
			}
		}
	}
}
void game::cleanDeadObjects()
{
	this->cleanDeadBullet();
	this->cleanDeadvillian();
	this->cleanDeadHero();
	this->endOfGame();
}
void game::cleanDeadBullet()
{
	for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
	{
		if (bullets[bulletIndex] != NULL)
		{
			if (bullets[bulletIndex]->coords.pozycja_x > 1900|| bullets[bulletIndex]->coords.pozycja_x < 0)
			{
				delete bullets[bulletIndex];
				bullets[bulletIndex] = NULL;
			}
		}
	}
}
void game::CheckAndExecuteLoadError(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer)
{
	if (charset == NULL) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
};
int game::ReturnViolet()
{
	return SDL_MapRGB(screen->format, 107, 15, 133);
}

int game::ReturnWhite()
{
	return SDL_MapRGB(screen->format, 255, 255, 255);
}
int game::ReturnBlack()
{
	return SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
}

void game::DrawSurface(SDL_Surface* sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, this->screen, &dest);
};

void game::drawBackground()
{
	DrawSurface(background, bgX, bgY + bgY);
	//DrawSurface(background, bgX, bgY - 2*background->h);
	SDL_FillRect(screen, NULL, ReturnBlack());
	for (int i = 0; i < 10; i++)
	{		
		DrawSurface(background, bgX + i*background->w, bgY);	
	}	
}

void game::drawInformation()
{
	if (gameEnded == false)
	{
		Draw.DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 50, ReturnWhite(), ReturnViolet());
		//template for the second project, elapsed time = %.1lf s  %.0lf frames / s
		sprintf(text, "Survive 5 minutes, time left to victory = %.1lf sec  %.0lf frames / s", 300 - worldTime, fps);
		Draw.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		//Esc - exit, \030 - faster, \031 - slower
		sprintf(text, "Esc - exit, move: \030 - up \031 - down \032 - left, \033 - right and shoot with sapce");
		Draw.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
	}
}
void game::changeAndShowTime()
{
	t2 = SDL_GetTicks();
	// w tym momencie t2-t1 to czas w milisekundach
	// jaki uplyna³ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	delta = (t2 - t1) * 0.001;
	t1 = t2;
	worldTime += delta;
	//printf("worldTime %lf\n", worldTime);
	distance += heroSpeed * delta;
	distance2 += villianSpeed * delta;
}
void game::changeFpsTimer()
{
	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};
}
void game::printInformationAboutWave()
{
	if (gameEnded == false)
	{
		if (worldTime < 18 && worldTime>2)
		{
			Draw.DrawRectangle(screen, SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 10, 250, 50, ReturnWhite(), ReturnViolet());
			sprintf(text, "Wave 1");
			Draw.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 125, text, charset);
		}
		if (worldTime < 44 && worldTime>30)
		{
			Draw.DrawRectangle(screen, SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 10, 250, 50, ReturnWhite(), ReturnViolet());
			sprintf(text, "Wave 2");
			Draw.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 125, text, charset);
		}
		if (worldTime < 120 && worldTime>90)
		{
			Draw.DrawRectangle(screen, SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 10, 250, 50, ReturnWhite(), ReturnViolet());
			sprintf(text, "Wave 3");
			Draw.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 125, text, charset);
		}
	}
}
void game::villianWave1(int czas)
{
	if (villian_obj[0] != NULL)
	{
		villian_obj[0]->coords.pozycja_x = bgX + SCREEN_WIDTH + 100;
		villian_obj[0]->coords.pozycja_y = bgY;
	}
	if (villian_obj[1] != NULL)
	{
		villian_obj[1]->coords.pozycja_x = bgX + SCREEN_WIDTH + 400;
		villian_obj[1]->coords.pozycja_y = bgY - 300;
	}
	if (villian_obj[2] != NULL)
	{
		villian_obj[2]->coords.pozycja_x = bgX + SCREEN_WIDTH + 600;
		villian_obj[2]->coords.pozycja_y = bgY + 400;
	}
	if (villian_obj[3] != NULL)
	{
		villian_obj[3]->coords.pozycja_x = bgX + SCREEN_WIDTH + 800;
		villian_obj[3]->coords.pozycja_y = bgY + 200;
	}
	if (villian_obj[4] != NULL)
	{
		villian_obj[4]->coords.pozycja_x = bgX + SCREEN_WIDTH + 1300;
		villian_obj[4]->coords.pozycja_y = bgY - 420;
	}
	if (villian_obj[5] != NULL)
	{
		villian_obj[5]->coords.pozycja_x = bgX + 3 * SCREEN_WIDTH - 300;
		villian_obj[5]->coords.pozycja_y = SCREEN_HEIGHT / 2 + cos(distance2 - 3) * SCREEN_HEIGHT / 2.5;
	}
	if (villian_obj[6] != NULL)
	{
		villian_obj[6]->coords.pozycja_x = bgX + 3 * SCREEN_WIDTH;
		villian_obj[6]->coords.pozycja_y = SCREEN_HEIGHT / 2 + cos(0.5 * distance2) * SCREEN_HEIGHT / 3;
	}
	if (villian_obj[7] != NULL)
	{
		villian_obj[7]->coords.pozycja_x = bgX + 3 * SCREEN_WIDTH + 1000;
		villian_obj[7]->coords.pozycja_y = SCREEN_HEIGHT / 2 + cos(1.5 * distance2) * SCREEN_HEIGHT / 3;
	}
	if (villian_obj[8] != NULL)
	{
		villian_obj[8]->coords.pozycja_x = bgX + 3 * SCREEN_WIDTH + sin(distance2 * 2) * SCREEN_HEIGHT / 3 + 500;
		villian_obj[8]->coords.pozycja_y = bgY;
	}

	if (worldTime > czas)
	{
		for (int index = 0; index < MAX_VILLIANS; index++)
		{
			if (villian_obj[index] != NULL)
			{
				villian_obj[index]->drawVillians(screen);
				

				if (frames % czas == 0) //shooting
				{
					for (int bulletIndex = 0; bulletIndex < villian_obj[index]->numberOfBullets; bulletIndex++)
					{
						if (bullets[bulletIndex] == NULL)
						{
							bullets[bulletIndex] = new Bullet(villian_obj[index]->coords.pozycja_x, villian_obj[index]->coords.pozycja_y, bullet_bmp, -10);
							
						}
					}
				}
			}
		}
		
	}
}
void game::cleanDeadvillian()
{
	for (int index = 0; index < MAX_VILLIANS; index++)
	{
		if (villian_obj[index] != NULL)
		{
			if (villian_obj[index]->health <= 0)
			{
				delete villian_obj[index];
				villian_obj[index] = NULL;
			}
		}
	}
}
void game::createVillians()
{
	this->villianWave1(2);
	this->villianWave1(2);
	this->villianWave1(2);
	this->villianWave1(2);
	this->villianWave1(2);
	this->villianWave1(3);
	this->villianWave1(5);
	this->villianWave1(5);
	this->villianWave1(5);
}
int game::incremateFrames()
{
	if (gameEnded == false)
	{
		framesNotPerSecond++;
	}
	frames++;
	return frames;
}
void game::chcangeBackground()
{
	if (gameEnded==false)
	{
		bgX = bgX - 1;
	}
}
void game::checkAndExecuteCollisions()
{
	for (int index = 0; index < MAX_VILLIANS; index++)
	{
		if (villian_obj[index] != NULL)
		{
			if (villian_obj[index]->health == 3)
			{
				this->DrawSurface(barVillian3, villian_obj[index]->coords.pozycja_x, villian_obj[index]->coords.pozycja_y - 90);
			}
			if (villian_obj[index]->health == 2)
			{
				this->DrawSurface(barVillian2, villian_obj[index]->coords.pozycja_x, villian_obj[index]->coords.pozycja_y - 90);
			}
			if (villian_obj[index]->health == 1)
			{
				this->DrawSurface(barVillian1, villian_obj[index]->coords.pozycja_x, villian_obj[index]->coords.pozycja_y - 90);
			}
			for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
			{
				if (bullets[bulletIndex] != NULL)
				{
					if ((bullets[bulletIndex]->coords.pozycja_x >= villian_obj[index]->coords.pozycja_x + 20) && (bullets[bulletIndex]->coords.pozycja_x <= villian_obj[index]->coords.pozycja_x + 40))
					{
						if ((bullets[bulletIndex]->coords.pozycja_y < villian_obj[index]->coords.pozycja_y + 50) && (bullets[bulletIndex]->coords.pozycja_y > villian_obj[index]->coords.pozycja_y - 50))
						{
							printf("health przed %d\n", villian_obj[index]->health);
							villian_obj[index]->health = villian_obj[index]->health - 1;
							printf("health po %d\n", villian_obj[index]->health);
							delete bullets[bulletIndex];
							bullets[bulletIndex] = NULL;


						}
					}
				}
			}
		}
	}
}
void game::checkAndExeciuteAstronautCollision()
{
	for (int index = 0; index < MAX_VILLIANS; index++)
	{
		if (heros != NULL && Asteroid_obj!= NULL)
		{
			if ((heros->coordsH.hero_x >= Asteroid_obj->coords.pozycja_x -20 ) && (heros->coordsH.hero_x + 20 <= Asteroid_obj->coords.pozycja_x+20))
			{
				if ((heros->coordsH.hero_y <= Asteroid_obj->coords.pozycja_y + 20) && (heros->coordsH.hero_y>=Asteroid_obj->coords.pozycja_y - 20))
				{
					heros->health++;
					delete Asteroid_obj;
					Asteroid_obj = NULL;
				}
			}
		}
	}
}
void game::endOfGame()
{
	if (gameEnded)
	{
		for (int index = 0; index < MAX_VILLIANS; index++)
		{
			delete villian_obj[index];
			villian_obj[index] = NULL;
		}
		for (int bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
		{
			delete bullets[bulletIndex];
			bullets[bulletIndex] = NULL;
		}
			DrawSurface(endBackground, bgX+ framesNotPerSecond+620, bgY);
		
	}
}
