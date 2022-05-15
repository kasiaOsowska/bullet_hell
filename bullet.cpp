#include "bullet.h"
#include "draw.h"
#include"Types.h"
Bullet::Bullet(int x, int y, SDL_Surface* bullet, int velocity)
{
	this->coords.pozycja_x=x;
	this->coords.pozycja_y=y;
	this->bullet=bullet;
	this->velocity=velocity;
};
void Bullet::drawBullet(SDL_Surface* screen)
{

	Draw.DrawSurfaceBullet(screen, this->bullet, coords.pozycja_x, coords.pozycja_y);
	coords.pozycja_x = coords.pozycja_x + velocity;

};
int Bullet::returnBulletY()
{
	return this->coords.pozycja_y;
};