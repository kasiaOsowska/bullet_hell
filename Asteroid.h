#pragma once
#include"Types.h"
class Asteroid
{
private:
	SDL_Surface* asteroid;

public:
	coords_T coords;
	int velocity;
	void drawAsteroid(SDL_Surface* screen);
	Asteroid(int x, int y, SDL_Surface* asteroid, int velocity);

};

