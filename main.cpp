#include"game.h"
#include"draw.h"
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"bullet.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

/*#ifdef __cplusplus
extern "C"
#endif*/

game *Game = nullptr;

int main(int argc, char** argv) 
{
	SDL_Event event;	
	
	Game = new game();

	while (Game->running()) 
	{
		/* Initial calculation */
		Game->changeAndShowTime();

		/* 2D drawing - put all 2D elements to draw HERE - START */

		Game->drawBackground();

		Game->cleanDeadObjects();

		Game->drawObjs();	

		Game->drawInformation();

		Game->printInformationAboutWave();

		/* 2D drawing - put all 2D elements to draw HERE - END */

		/* Rendering */
		Game->render();

		/* Post calculations */
		Game->createVillians();

		Game->changeFpsTimer();		
		
		/* Events handling */
		while (SDL_PollEvent(&event))
		{
			Game->handleEvent(event);			
		}

		Game->incremateFrames();

		Game->chcangeBackground();
	}

	// zwolnienie powierzchni	
	Game->clean();
	return 0;
};
