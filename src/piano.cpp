//Includes
///////////////////////
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "SDL_image.h"
#include "SDL.h"
#include "PDL.h"
#include "key.hpp"
#include "Audio.cpp"
#include "SDL_mixer.h"
#include "Input.cpp"
#include "SDL_Renderer.cpp"
#include "OGL_Renderer.cpp"
#include <syslog.h>
//////////////////////

//Global variables
/////////////////////

key *Keys[12];
//////////////////////
int channel;
const char* version;
int quit = 1;
int tempX;
int touchX;
int prevX[5];
PDL_ScreenMetrics outMetrics;
int  x1, x2, d = 0;
int animate = 0;
Audio AudioManager; 
Input InputManager;
OGL_Renderer OGL_RendererManager;
SDL_Event tempEvent;
SDL_Event Event;
/////////////////////

//Function declarations
/////////////////////////
void redrawKey(int x);
void initKeys();
void touch(SDL_Event touchEvent, bool down);
void motion(SDL_Event touchEvent);
int FilterEvents (const SDL_Event *event);
void animateUp();
void animateDown();
////////////////////////

int main(int argc, char** argv)
{

	OGL_RendererManager.initOGL();

	OGL_RendererManager.clearScreen();
	OGL_RendererManager.drawImage(-192,480 , 4);
	OGL_RendererManager.updateScreen(); 
	SDL_SetEventFilter(FilterEvents);
	SDL_PumpEvents();
	AudioManager.initAudio();
	AudioManager.loadResources();
	
	
	
	PDL_GetScreenMetrics(&outMetrics);   
	
	if (outMetrics.verticalPixels == 480)
	{
		version = "pre";
	}
	else if (outMetrics.verticalPixels == 400)
	{
		version = "pixi";
	}

    
	initKeys();
	redrawKey(0);
	OGL_RendererManager.updateScreen();

    do {
	SDL_PumpEvents();
		SDL_Delay(10);
		OGL_RendererManager.clearScreen();
		redrawKey(0);
		OGL_RendererManager.updateScreen();
		
    } while (quit != 0);
	AudioManager.cleanupAudio();
	PDL_Quit();
    SDL_Quit();

    return 0;
}

void initKeys()
{
	
	//Loop for all 14 keys on the piano
	int x;
	for(x = 0; x<12; x++)
	{
		key *temp = new key;
		//Set whether the key is white or black 
		//////////////////////////////////////
		if (x<7)
		{
			temp->setColor(0);
		}
		else 
		{
			temp->setColor(1);
		}
		//////////////////////////////////////
		
		
		//Set whether key is pressed
		//Default to no
		//////////////////////////////
		temp->setPressed(false);
		////////////////////////////////////
		
		//Set what key this is
		//Used when playing the sound
		///////////////////////////////////
		temp->setNote(x);
		///////////////////////////////////
		
		//Add key to the array of all keys 
		//assign a pointer
		////////////////////////////////////
		Keys[x] = temp;
	}
	
}


int FilterEvents(const SDL_Event *event) {
	
    /* This quit event signals the closing of the window */
    switch (event->type) {
			// List of keys that have been pressed
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
					// Escape forces us to quit the app
				case PDLK_GESTURE_BACK:
					if (AudioManager.getOctave() > 0) {
						animate = 2;
						x1 = 0, x2 = 480;
					}
					AudioManager.octaveDown();
					
					break;
				case PDLK_GESTURE_FORWARD:
					if (AudioManager.getOctave() < 5) {
						animate = 1;
						x1 = 480, x2 = 960;
					}
					AudioManager.octaveUp();
					
					break;
					
				default:
					break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			tempEvent = *event;
			touch(tempEvent, true);
			return 0;
		case SDL_MOUSEMOTION:
			tempEvent = *event;
			motion(tempEvent);
			return 0;
			
		case SDL_QUIT:
			quit = 0;
			return 0;

		default:
			break;
			return 1;
	}
}

void touch (SDL_Event touchEvent, bool down)
{
	
	int x = InputManager.findWhichKeyPressed(touchEvent.motion.x, touchEvent.motion.y);
	
	Keys[x]->setPressed(false);
	
	//Update the screen
	//OGL_RendererManager.clearScreen();
	//redrawKey(x);
	// OGL_RendererManager.updateScreen();
	
}

void motion(SDL_Event touchEvent)
{
//Find which key the press was on	
int x = InputManager.findWhichKeyPressed(touchEvent.motion.x, touchEvent.motion.y);
	
if (x != prevX[touchEvent.motion.which])
{	
	//Stop the sound of the previous key touched, so that a new one cane be played
	AudioManager.stopSound(prevX[touchEvent.motion.which]);
	
	//Play the sound of the new key
	Keys[x]->channel = AudioManager.playSound(AudioManager.getSoundFile(x));
	
	//Set the pressed key to true in the key array
	Keys[x]->setPressed(true);
	
	//Set the previously pressed key to false in the key array
	Keys[prevX[touchEvent.motion.which]]->setPressed(false);
	//OGL_RendererManager.clearScreen();
	//Update the screen
	//redrawKey(x);
	//redrawKey(prevX[touchEvent.motion.which]);
	// OGL_RendererManager.updateScreen();
	
	//Set the array of previous touches to where it was just touched
	prevX[touchEvent.motion.which] = x;
	
	
}
else if (Keys[prevX[touchEvent.motion.which]]->getPressed() == false)
{
	//Stop the sound of the previous key touched, so that a new one can be played
	AudioManager.stopSound(x);
	
	//Play the sound of the new key
	Keys[x]->channel = AudioManager.playSound(AudioManager.getSoundFile(x));
	
	//Set the pressed key to true in the key array
	Keys[x]->setPressed(true);
	
	//Set the array of previous touches to where it was just touched
	prevX[touchEvent.motion.which] = x;
	//OGL_RendererManager.clearScreen();
	//redrawKey(x);
	// OGL_RendererManager.updateScreen();
}
}
void redrawKey(int y)
{
	/*
	 I am not storing the location values in the key object array.
	 The positions of the keys are static and can be defined in this function. 
	 The only information stored will be whether it is pressed or not, so that
	 the correct image to use can be determined. 
	 */
	//OGL_RendererManager.clearScreen();
	if (animate == 0)
	{
	for (int x = 0; x<12; x++) {
		
	
		bool pressed = Keys[x]->getPressed();
		if (x<7)
		{
			//The first 7 keys are the white keys
			//Drawing is fairly straightforward
			//Simply incrementing x axis
			//
			if (pressed == false)
			{
				//Key is not pressed
				//Use default image
			
				OGL_RendererManager.drawImage(0, 2 + ((x + 1) * 68), 3);
				// SDL_RendererManager.blitImage(2 + (x * 68),  0, // SDL_RendererManager.key_white, // SDL_RendererManager.key_white->w, // SDL_RendererManager.key_white->h);
			}
			else if(pressed == true)
			{
				//Key is pressed
				//Use use the white key pressed image
				 OGL_RendererManager.drawImage(0, ( 2 + ((x + 1) * 68)), 2);
				//syslog(LOG_ERR, "pressed");
				// SDL_RendererManager.blitImage(2 + (x * 68), 0, // SDL_RendererManager.key_white_pressed, // SDL_RendererManager.key_white_pressed->w, // SDL_RendererManager.key_white_pressed->h);
			}
			
		}
		else if (x > 6)
		{
			if (x < 9)
			{
				if (pressed == false)
				{
					//Key is not pressed
					//Use default image
					 OGL_RendererManager.drawImage(140 , 43 + ((x - 6)*68), 1);
					// SDL_RendererManager.blitImage(43 + ((x - 7)*68), 0, // SDL_RendererManager.key_black, // SDL_RendererManager.key_black->w, // SDL_RendererManager.key_black->h);
				}
				else if(pressed == true)
				{
					//Key is pressed
					//Use use the black key pressed image
					 OGL_RendererManager.drawImage(140 , 43 + ((x - 6)*68), 0);
					//syslog(LOG_ERR, "pressed");
					// SDL_RendererManager.blitImage(43 + ((x - 7)*68), 0, // SDL_RendererManager.key_black_pressed, // SDL_RendererManager.key_black_pressed->w, // SDL_RendererManager.key_black_pressed->h);
				}
				
				
			}
			else {
				
				if (pressed == false)
				{
					
					//Key is not pressed
					//Use default image
					 OGL_RendererManager.drawImage(140,43 + ((1 +(x - 6))*68), 1);
					// // OGL// SDL_RendererManager.blitImage(43 + ((1 +(x - 7))*68), 0, // SDL_RendererManager.key_black, // SDL_RendererManager.key_black->w, // SDL_RendererManager.key_black->h);
				}
				else if(pressed == true)
				{
					//Key is pressed
					//Use use the black key pressed image
					//syslog(LOG_ERR, "pressed");
					OGL_RendererManager.drawImage(140, 43 + ((1 +(x - 6))*68),  0);
					// SDL_RendererManager.blitImage(43 + ((1 +(x - 7))*68), 0, // SDL_RendererManager.key_black_pressed, // SDL_RendererManager.key_black_pressed->w, // SDL_RendererManager.key_black_pressed->h);
				}
			}
			
			
			
		}
	}
	}
	else if (animate == 1)
	{
		if (version == "pre")
		{
			//animate up
			if (d < 480)
			{
				OGL_RendererManager.drawImage(0, x1, 5);
			
				OGL_RendererManager.drawImage(0, x2, 5);
			
				x1-= 15;
				x2-= 15;
				d += 15;
			}
			else 
			{
				animate = 0;
				d = 0;
				SDL_Delay(20);
			}
		}
		else if (version == "pixi")
		{
			if (d < 480)
			{
				OGL_RendererManager.drawImage(0, x1, 5);
				
				OGL_RendererManager.drawImage(0, x2, 5);
				
				x1-= 15;
				x2-= 15;
				d += 15;
			}
			else {
				animate = 0;
				d = 0;
				SDL_Delay(20);
			}
		}
	}
	
	else if (animate == 2) {
		//animate down
		if (version == "pre")
		{
			//animate up
			if (d < 480)
			{
				OGL_RendererManager.drawImage(0, x1, 5);
				
				OGL_RendererManager.drawImage(0, x2, 5);
				
				x1+= 15;
				x2+= 15;
				d += 15;
			}
			else 
			{
				animate = 0;
				d = 0;
				SDL_Delay(20);
			}
		}
		else if (version == "pixi")
		{
			if (d < 480)
			{
				OGL_RendererManager.drawImage(0, x1, 5);
				
				OGL_RendererManager.drawImage(0, x2, 5);
				
				x1+= 15;
				x2+= 15;
				d += 15;
			}
			else {
				animate = 0;
				d = 0;
				SDL_Delay(20);
			}
		}

	}

	
}



void animateUp()
{
	int  x1 = 0, x2 = 480;
	for(int d = 0; d<480; d+=12)
	{
		
		OGL_RendererManager.clearScreen();
		OGL_RendererManager.drawImage(0, x1, 5);
		
		
		OGL_RendererManager.updateScreen();

		
		x1-= 12;
		x2-= 12;
	}
	//The user has raised the octave, so show the keys slidinging to the left
}

void animateDown()
{
	//The user has lowered the octave, so show the keys sliding to the right
	int  x1 = -480, x2 = 0;
	for(int d = 0; d<480; d+=12)
	{
		
		OGL_RendererManager.clearScreen();
		OGL_RendererManager.drawImage(0, x1, 5);
		
		OGL_RendererManager.drawImage(0, x2, 5);
		OGL_RendererManager.updateScreen();
		SDL_Delay(10);
		
		
	}
}