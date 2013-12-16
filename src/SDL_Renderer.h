/*
 *  SDL_Renderer.h
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "SDL.h"

class SDL_Renderer
{
public:
	void initSDL();
	void loadResources();
	void blitImage(int sourceX, int sourceY, SDL_Surface* image, int sourceW, int sourceH);
	void updateSurface();
	
	
	//////////////////////
	SDL_Surface *key_white;
	SDL_Surface *key_black;
	SDL_Surface *key_black_pressed;
	SDL_Surface *key_white_pressed;
	
	
private:
	 
	SDL_Surface *screen;
	SDL_Rect source;
	SDL_Surface *keyboard_temp;
	SDL_Surface *keyboard;

};