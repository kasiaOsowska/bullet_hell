#ifndef _TYPES_H_
#define _TYPES_H_

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#define SCREEN_WIDTH 1867
#define SCREEN_HEIGHT 1050
#define MAX_BULLETS 100
#define MAX_VILLIANS 15

typedef struct
{
	int pozycja_x;
	int pozycja_y;
}coords_T;

typedef struct
{
	int hero_x;
	int hero_y;
}coords_H;

#endif