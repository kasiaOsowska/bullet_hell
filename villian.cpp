#include "villian.h"
#include "draw.h"
villian::villian(int x, int y, SDL_Surface* alien, int health, int velocityX, int velocityY, int numberOfBullets)
{
	this->coords.pozycja_x = x;
	this->coords.pozycja_y = y;
	this->alien = alien;
	this->health = health;
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	this->velocityY = velocityY;
	this->numberOfBullets = numberOfBullets;

};
void villian::drawVillians(SDL_Surface* screen)
{

	Draw.DrawSurfaceBullet(screen, this->alien, coords.pozycja_x, coords.pozycja_y);
	coords.pozycja_x += velocityX;
	coords.pozycja_y += velocityY;
	if (coords.pozycja_x >= SCREEN_WIDTH)
	{
		velocityX = 0 - velocityX;
	}
	if (coords.pozycja_x <= 0)
	{
		velocityX = 0 - velocityX;
	}
	if (coords.pozycja_y <= SCREEN_HEIGHT)
	{
		velocityY = 0 - velocityY;
	}
	if (coords.pozycja_y >=0)
	{
		velocityY = 0 - velocityY;
	}
}

//void villian::drawBar()
//{
//Draw.DrawSurfaceBullet(screen, this->alien, coords.pozycja_x, coords.pozycja_y);
//}
