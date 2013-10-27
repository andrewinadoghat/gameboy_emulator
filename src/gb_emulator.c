/*
	GameBoy Emulator
	Andrew Olson
	2013
*/

#include "SDL.h"
#include <stdio.h>
#include <stdint.h>
#include "inc/gb_cpu.h"
#include "inc/gb_opcode.h"

#define MAXCYCLES 4194304/60

void updateCPU(void);

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	
	
	if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else 
    {
        FILE *fp = fopen( argv[1], "rb" );
        /* fopen returns 0, the NULL pointer, on failure */
        if ( fp == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
        	initializeGameBoy(fp);
            fclose(fp);
        }
    }
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    	printf("Unable to initialize SDL: %s\n",SDL_GetError());
    	return 1;
    }
    
    atexit(SDL_Quit);
    SDL_WM_SetCaption("GameBoy Emulator", "GameBoy Emulator");
    screen = SDL_SetVideoMode(160,144,0,0);
    if(screen == NULL)
    {
    	printf("Unable to set video mode: %s\n",SDL_GetError());
    }
    
	while()
	{
		// call at 60 hz
		updateCPU();
		//drawScreen();
	}
	
	return 0;
}

void updateCPU(void)
{
	uint32_t cycles=0;
	
	while(cycles < MAXCYCLES)
	{
		cycles += executeOpcode();
		interrupts();
		updateVideo(cycles);
		updateTimers(cycles);
		//updateSound(cycles);	
	}		
}

void updateVideo(uint32_t cycles)
{
	switch(mode)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define BACKGROUND_WIDTH 256
#define BACKGROUND_HEIGHT 256
#define NUM_SPRITES 40

void renderScanLine()
{
	if(tiles)
		renderTiles()
		
	if(sprites)
		renderSprites();
}

void renderTiles()
{
	uint32_t i;
	uint32_t pixel;
	
	for(pixel=0;pixel<SCREEN_WIDTH;pixel++)
	{
	
	}
}

void renderSprites()
{
	uint8_t ;
	uint32_t i;
	
	for(i=0;i<NUM_SPRITES;i++)
	{
	
	}
}

int x,y;
	SDL_Rect pixel;
	SDL_LockSurface(surf);
	SDL_FillRect(surf,NULL,0);
	pixel.w = 10;
	pixel.h = 10;
	for(y=0;y<32;y++)
	{
		pixel.y = y*10;
		for(x=0;x<64;x++)
		{
			pixel.x=x*10;
			if(c8->scrn[x+(y*64)]==1)
				SDL_FillRect(surf,&pixel,SDL_MapRGB(surf->format, 0, 255, 0));
			else
				SDL_FillRect(surf,&pixel,SDL_MapRGB(surf->format, 0, 0, 0));
		}
	}
	
	SDL_UnlockSurface(surf);
	
	SDL_UpdateRect(surf,0,0,0,0);

checkKeys(void)
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			/* Close button was clicked */
			case SDL_QUIT:
				running = 0;
				break;
			/* Hnadle the keyboard */
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						running = 0;
						break;
					
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					
				}
				break;
		}
	}
}
