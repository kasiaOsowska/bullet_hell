#pragma once
#include"types.h"
class Hero{

private:
	
	SDL_Surface* hero;	

public:
	coords_H coordsH;
	int health;
	coords_H coords_ogien;
	Hero(int x, int y, SDL_Surface* hero);
	void drawHeros(SDL_Surface* screen);
	void drawFire(SDL_Surface* screen, SDL_Surface* fire);

};