/*
 *  SDL_Renderer.cpp
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SDL_Renderer.h"
#include <syslog.h>

void SDL_Renderer::initSDL()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode(480,320,0,SDL_SWSURFACE);
}

void SDL_Renderer::loadResources()
{
	//Need to change this, they aren't bmp's anymore
	key_white = SDL_LoadBMP("./images/key.bmp");
	if (key_white == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());}

	key_black = SDL_LoadBMP("./images/key_black.bmp");
	if (key_black == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}

	key_black_pressed = SDL_LoadBMP("./images/key_black_pressed.bmp");
	if (key_black == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}
	

	key_white_pressed = SDL_LoadBMP("./images/key_pressed.bmp");
	if (key_black == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}
	
	/*keyboard_temp = SDL_LoadBMP("./images/animate.bmp");
	 if (key_black == NULL) {
	 printf("Unable to load bitmap: %s\n", SDL_GetError());
	 }
	 keyboard = SDL_DisplayFormat(keyboard_temp);
	 */
}

void SDL_Renderer::updateSurface()
{
	SDL_Flip(screen);
}

void SDL_Renderer::blitImage(int sourceX, int sourceY, SDL_Surface* image, int sourceW, int sourceH)
{
	
	source.x = sourceX;
	source.y = sourceY;
	source.w = sourceW;
	source.h = sourceH;
	
	SDL_BlitSurface(image, NULL, screen, &source);
}
