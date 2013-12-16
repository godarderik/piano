/*
 *  Audio.h
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "SDL_mixer.h"
class Audio
{
public:
	
	void initAudio();
	void cleanupAudio();
	void printSpecs();
	
	void loadResources();
	int playSound(Mix_Chunk* soundFilePointer);
	void stopSound(int note);
	
	Mix_Chunk * getSoundFile(int note);
	
	void octaveUp();
	void octaveDown();
	int getOctave();
	void setOctave(int octaveNumber);
	//constructor
	Audio();
private:
	//Arrays of piano sounds
	Mix_Chunk *octave0[12];
	Mix_Chunk *octave1[12];
	Mix_Chunk *octave2[12];
	Mix_Chunk *octave3[12];
	Mix_Chunk *octave4[12];
	Mix_Chunk *octave5[12];
	Mix_Chunk *octave6[12];
	Mix_Chunk *octave7[12];
	//////////////////////
	
	int octave;
	Mix_Chunk *which;
};
