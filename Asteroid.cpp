#include "Asteroid.h"
#include"Draw.h"
Asteroid::Asteroid(int x, int y, SDL_Surface* asteroid, int velocity)
{
	this->coords.pozycja_x = 9*x;
	this->coords.pozycja_y = y;
	this->asteroid = asteroid;
	this->velocity = velocity;
};
void Asteroid::drawAsteroid(SDL_Surface* screen)
{

	Draw.DrawSurfaceBullet(screen, asteroid, coords.pozycja_x, coords.pozycja_y);
	coords.pozycja_x = coords.pozycja_x + velocity;

}
