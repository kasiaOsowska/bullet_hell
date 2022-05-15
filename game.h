#ifndef game_HEADER
#define game_HEADER
#define _USE_MATH_DEFINES
#define SCREEN_WIDTH 1867
#define SCREEN_HEIGHT 1050
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"draw.h"
#include"Types.h"
#include"bullet.h"
#include"hero.h"
#include"Asteroid.h"
#include"villian.h"

using namespace std;
class game{
private:
	bool isRunning;
	int t1, t2, quit, frames, framesNotPerSecond, rc, x, y;	
	SDL_Surface* background, * bullet_bmp, * hero_bmp, * hero2, *alien1, * alien2, * alien3, *ogien1, *ogien2, *ogien3, *barVillian3, *barVillian2, *barVillian1;
	SDL_Surface* barHero1, * barHero2, * barHero3, *barHero4, * barHero5, * barHero6, * barHero7, * barHero8, * barHero9, * barHero10, *astronaut_bmp, *endBackground;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;
	Bullet* bullets[MAX_BULLETS];
	Hero* heros;
	villian* villian_obj[MAX_VILLIANS];
	Asteroid* Asteroid_obj;
	bool gameEnded;
	void drawBullets();
	bool aPressed;
	int bgX, bgY;
	int bulletx = x;
	int bullety = y;
	bool isMoving;
public:
	char text[128];
	double fpsTimer, fps, worldTime, distance, distance2, delta, heroSpeed, villianSpeed;
	game();
	void handleEvent(SDL_Event event);
	void CheckAndExecuteLoadError(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);
	void render();
	int incremateFrames();
	void checkAndExecuteCollisions();
	void endOfGame();
	
	void clean();
	bool running()
	{
		return isRunning;
	}
	void drawObjs();
	void cleanDeadObjects();
	void cleanDeadBullet();
	int ReturnViolet();
	int ReturnWhite();
	int ReturnBlack();
	void DrawSurface(SDL_Surface* sprite, int x, int y);
	void drawBackground();
	void drawHero();
	void drawInformation();
	void changeAndShowTime();
	void changeFpsTimer();
	void printInformationAboutWave();
	void villianWave1(int czas);
	void villianWave2(SDL_Surface* hero, double distance2, double worldTime, int czas);
	void villianWave3(SDL_Surface* hero, double distance2, double worldTime, int czas);
	void createVillians(/*int VillianX, int VillianY, int index, int bullets, int apperenceTime*/);
	void drawAsteroid();
	void cleanDeadvillian();
	void initializeVillians();
	void checkAndExeciuteIfHeroWasShot();
	void cleanDeadHero();
	void checkAndExeciuteAstronautCollision();
	void chcangeBackground();
};
#endif



