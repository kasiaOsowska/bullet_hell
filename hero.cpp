#include "hero.h"
#include "draw.h"
Hero::Hero(int x, int y, SDL_Surface* hero)
{
	this->coordsH.hero_x = x;
	this->coordsH.hero_y = y;
	this->coords_ogien.hero_y = y;
	this->coords_ogien.hero_x = x;
	this->hero = hero;
	this->health = 10;
};
void Hero::drawHeros(SDL_Surface* screen)
{
	Draw.DrawSurfaceBullet(screen, hero, coordsH.hero_x, coordsH.hero_y);
};
void Hero::drawFire(SDL_Surface* screen, SDL_Surface* fire)
{
	Draw.DrawSurfaceBullet(screen, fire, coords_ogien.hero_x-290, coords_ogien.hero_y);
};


