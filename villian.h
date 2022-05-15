#pragma once
#include"Types.h"
class villian
{
private:

	SDL_Surface* alien, *bar3, *bar2;

public:
	coords_T coords;
	int health;
	int velocityX;
	int velocityY;
	int numberOfBullets;
	villian(int x, int y, SDL_Surface* alien, int health, int velocityX, int velocityY, int numberOfBullets);
	void drawVillians(SDL_Surface* screen);
	//void villian::drawBar();
};

