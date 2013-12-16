/*
 *  OGL_Renderer.cpp
 *  Piano
 *
 *  Created by Erik Godard on 8/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "OGL_Renderer.h"
#include "SDL.h"
#include <syslog.h>
GLfloat g_coordinates[] = 
{  
	0.0, 480.0,
	320.0, 480.0,
	0.0, 0.0,
	320.0, 0.0 
};

void OGL_Renderer::initOGL()
{
	PDL_GetScreenMetrics(&outMetrics);   
	
	if (outMetrics.verticalPixels == 480)
	{
		version = "pre";
	}
	else if (outMetrics.verticalPixels == 400)
	{
		version = "pixi";
	}
	
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);  
	if (version == "pre")
	{
	SDL_SetVideoMode(480, 320, 0, SDL_OPENGL); 
	}
	if (version == "pixi")
	{
		SDL_SetVideoMode(400, 320, 0, SDL_OPENGL); 
	}
	glMatrixMode(GL_PROJECTION);
	glOrthof((GLfloat)0, (GLfloat)320, (GLfloat)0, (GLfloat)480, (GLfloat)-1, (GLfloat)1);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_BLEND);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glTexCoordPointer(2, GL_FLOAT, 0, g_coordinates); 
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	
	const char* piano = "piano";
	openlog(piano, 0, LOG_USER);
	
	loadImage("./images/key_black_pressed.png", 0);
	loadImage("./images/key_black.png", 1);
	loadImage("./images/key_pressed.png", 2);
	loadImage("./images/key.png", 3);
	loadImage("./images/splash.png", 4);
	loadImage("./images/animate.png", 5);
	loadImage("./images/animate_pixi.png", 6);
	
	
}

void OGL_Renderer::updateScreen()
{
	//glFlush();
   
	SDL_GL_SwapBuffers();
}

void OGL_Renderer::loadImage(const char *fileName, int which)
{
	surface = IMG_Load(fileName);
	
	if(!surface)
	{
		syslog(LOG_ERR, "load failed");
	}
	
	//Store the dimensions of
	imageW[which] = surface->w;
	imageH[which] = surface->h;
	
	int pow2W = power_of_two(surface->w);
	int pow2H = power_of_two(surface->h);
	
	actualImageW[which] = (GLfloat)imageW[which] / (GLfloat)pow2W;
	actualImageH[which] = (GLfloat) imageH[which] / (GLfloat)pow2H;

						   SDL_Surface *image = SDL_CreateRGBSurface(
																	 SDL_SWSURFACE,
																	 pow2W, pow2H,
																	 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
																	 0x000000FF, 
																	 0x0000FF00, 
																	 0x00FF0000, 
																	 0xFF000000
#else
																	 0xFF000000,
																	 0x00FF0000, 
																	 0x0000FF00, 
																	 0x000000FF
#endif
																	 );					   
	Uint32 saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	Uint8 saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) 
	{
		SDL_SetAlpha(surface, 0, 0);
	}
	

	SDL_Rect area;
	area.x = 0;
	area.y = 0;
	area.w = (Uint16)imageW[which];
	area.h = (Uint16)imageH[which];
	SDL_BlitSurface(surface, &area, image, &area);
	
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) 
	{
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}
	
	
	glGenTextures( 1, &texture[which] );
	glBindTexture( GL_TEXTURE_2D, texture[which] );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,
				 surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	

}

void OGL_Renderer::drawImage(int x, int y, int which)
{
	
		y = 480 - y;
	
	GLfloat fX = (GLfloat)x;
	GLfloat fY = (GLfloat)y;
		
	
	GLfloat	coordinates[] = { 0, actualImageH[which], actualImageW[which],actualImageH[which], 0, 0, actualImageW[which], 0 };
	GLfloat		vertices[] = 
	{ 
		fX, fY, 0.0,
		imageW[which] +fX, fY, 0.0,
		fX, imageH[which] + fY , 0.0,
		imageW[which] +fX , imageH[which] + fY, 0.0 
	};	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor4f(0.0, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texture[which]);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
	
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	
	
	
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		SDL_Quit();
	}
	
	
}

void OGL_Renderer::translateCoordinates(int* x, int *y, int h)
{
	*y = *x;
	*x = 320 - h;
}

int OGL_Renderer::power_of_two(int input)
{
	int value = 1;
	while ( value < input ) 
	{
		value <<= 1;
	}
	return value;
}

void OGL_Renderer::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
}