/*
 *  OGL_Renderer.h
 *  Piano
 *
 *  Created by Erik Godard on 8/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <GLES/gl.h>
#include "SDL_image.h"
#include "SOIL.h"
class OGL_Renderer
{
public:
	
	void initOGL();
	void updateScreen();
	void loadImage(const char *fileName, int which);
	void initResources();
	void drawImage(int x, int y, int which);
	void translateCoordinates(int* x, int *y, int h);
	void clearScreen();
	int power_of_two(int input);

private:
	SDL_Surface *surface;
	GLuint      texture[7];
	int imageW [7];
	int imageH [7];
	int actualImageW [7];
	int actualImageH [7];
	PDL_ScreenMetrics outMetrics;
	const char* version;
};
