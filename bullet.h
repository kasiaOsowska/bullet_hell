#pragma once
#include "Types.h"
class Bullet {

private:

	SDL_Surface* bullet;

public:
	coords_T coords;
	int velocity;
	Bullet(int x, int y, SDL_Surface* bullet, int velocity);
	void drawBullet(SDL_Surface* screen);
	int returnBulletY();

};