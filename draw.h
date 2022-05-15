#pragma once

#include "Types.h"
#include "game.h"

class draw
{
public:
	void DrawString(SDL_Surface* screen, int x, int y, const char* text,
		SDL_Surface* charset);
	void DrawSurfaceBullet(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

};


extern draw Draw;