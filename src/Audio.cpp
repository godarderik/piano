/*
 *  Audio.cpp
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Audio.h"

Audio::Audio ()
{
	octave = 3;
}
void Audio::initAudio()
{
	//Parameter for the open audio call
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 724;
	
	//Open the audio
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		printf("Unable to init audio");
		exit(1);
	}
	//We need 12 channels because of 12 keys
	Mix_AllocateChannels(12);
}

void Audio::cleanupAudio()
{
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave0[x]);
	}
	
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave1[x]);
	}
	
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave2[x]);
	}
	
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave3[x]);
	}
	
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave4[x]);
	}
	
	for (int x = 0; x < 12; x++) {
		Mix_FreeChunk(octave5[x]);
	}
	

	Mix_CloseAudio();
}

void Audio::printSpecs()
{
	int frequency, storedChannels,tempFormat;
	Uint16 format;
	
	Mix_QuerySpec(&frequency, &format, &storedChannels);
	tempFormat = format;
	printf("Frequency: %d \n Channels: %d \n Format: %u", frequency, storedChannels, tempFormat);
}

void Audio::loadResources()
{
	//Load the Sounds//
	//Maybe there is a better way to do this
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 0
	
	octave0[5] = Mix_LoadWAV("./sounds/0/a0.wav");
	
	octave0[11] = Mix_LoadWAV("./sounds/0/asharp0.wav");
	
	octave0[6] = Mix_LoadWAV("./sounds/0/b0.wav");
	
	
	octave0[0] = Mix_LoadWAV("./sounds/0/c0.wav");
	
	octave0[7] = Mix_LoadWAV("./sounds/0/csharp0.wav");
	
	octave0[1] = Mix_LoadWAV("./sounds/0/d0.wav");
	
	octave0[8] = Mix_LoadWAV("./sounds/0/dsharp0.wav");
	
	octave0[2] = Mix_LoadWAV("./sounds/0/e0.wav");
	
	octave0[3] = Mix_LoadWAV("./sounds/0/f0.wav");
	
	octave0[9] = Mix_LoadWAV("./sounds/0/fsharp0.wav");
	
	octave0[4] = Mix_LoadWAV("./sounds/0/g0.wav");
	
	octave0[10] = Mix_LoadWAV("./sounds/0/gsharp0.wav");
	
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 1
	
	octave1[5] = Mix_LoadWAV("./sounds/1/a1.wav");
	
	octave1[11] = Mix_LoadWAV("./sounds/1/asharp1.wav");
	
	octave1[6] = Mix_LoadWAV("./sounds/1/b1.wav");
	
	
	octave1[0] = Mix_LoadWAV("./sounds/1/c1.wav");
	
	octave1[7] = Mix_LoadWAV("./sounds/1/csharp1.wav");
	
	octave1[1] = Mix_LoadWAV("./sounds/1/d1.wav");
	
	octave1[8] = Mix_LoadWAV("./sounds/1/dsharp1.wav");
	
	octave1[2] = Mix_LoadWAV("./sounds/1/e1.wav");
	
	octave1[3] = Mix_LoadWAV("./sounds/1/f1.wav");
	
	octave1[9] = Mix_LoadWAV("./sounds/1/fsharp1.wav");
	
	octave1[4] = Mix_LoadWAV("./sounds/1/g1.wav");
	
	octave1[10] = Mix_LoadWAV("./sounds/1/gsharp1.wav");
	
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 2
	
	octave2[5] = Mix_LoadWAV("./sounds/2/a2.wav");
	
	octave2[11] = Mix_LoadWAV("./sounds/2/asharp2.wav");
	
	octave2[6] = Mix_LoadWAV("./sounds/2/b2.wav");
	
	
	octave2[0] = Mix_LoadWAV("./sounds/2/c2.wav");
	
	octave2[7] = Mix_LoadWAV("./sounds/2/csharp2.wav");
	
	octave2[1] = Mix_LoadWAV("./sounds/2/d2.wav");
	
	octave2[8] = Mix_LoadWAV("./sounds/2/dsharp2.wav");
	
	octave2[2] = Mix_LoadWAV("./sounds/2/e2.wav");
	
	octave2[3] = Mix_LoadWAV("./sounds/2/f2.wav");
	
	octave2[9] = Mix_LoadWAV("./sounds/2/fsharp2.wav");
	
	octave2[4] = Mix_LoadWAV("./sounds/2/g2.wav");
	
	octave2[10] = Mix_LoadWAV("./sounds/2/gsharp2.wav");
	
	
	
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 3
	
	octave3[5] = Mix_LoadWAV("./sounds/3/a3.wav");
	
	octave3[11] = Mix_LoadWAV("./sounds/3/asharp3.wav");
	
	octave3[6] = Mix_LoadWAV("./sounds/3/b3.wav");
	
	
	octave3[0] = Mix_LoadWAV("./sounds/3/c3.wav");
	
	octave3[7] = Mix_LoadWAV("./sounds/3/csharp3.wav");
	
	octave3[1] = Mix_LoadWAV("./sounds/3/d3.wav");
	
	octave3[8] = Mix_LoadWAV("./sounds/3/dsharp3.wav");
	
	octave3[2] = Mix_LoadWAV("./sounds/3/e3.wav");
	
	octave3[3] = Mix_LoadWAV("./sounds/3/f3.wav");
	
	octave3[9] = Mix_LoadWAV("./sounds/3/fsharp3.wav");
	
	octave3[4] = Mix_LoadWAV("./sounds/3/g3.wav");
	
	octave3[10] = Mix_LoadWAV("./sounds/3/gsharp3.wav");
	
	
	
	
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 4
	
	octave4[5] = Mix_LoadWAV("./sounds/4/a4.wav");
	
	octave4[11] = Mix_LoadWAV("./sounds/4/asharp4.wav");
	
	octave4[6] = Mix_LoadWAV("./sounds/4/b4.wav");
	
	
	octave4[0] = Mix_LoadWAV("./sounds/4/c4.wav");
	
	octave4[7] = Mix_LoadWAV("./sounds/4/csharp4.wav");
	
	octave4[1] = Mix_LoadWAV("./sounds/4/d4.wav");
	
	octave4[8] = Mix_LoadWAV("./sounds/4/dsharp4.wav");
	
	octave4[2] = Mix_LoadWAV("./sounds/4/e4.wav");
	
	octave4[3] = Mix_LoadWAV("./sounds/4/f4.wav");
	
	octave4[9] = Mix_LoadWAV("./sounds/4/fsharp4.wav");
	
	octave4[4] = Mix_LoadWAV("./sounds/4/g4.wav");
	
	octave4[10] = Mix_LoadWAV("./sounds/4/gsharp4.wav");
	
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	//////octave 5
	
	octave5[5] = Mix_LoadWAV("./sounds/5/a5.wav");
	
	octave5[11] = Mix_LoadWAV("./sounds/5/asharp5.wav");
	
	octave5[6] = Mix_LoadWAV("./sounds/5/b5.wav");
	
	
	octave5[0] = Mix_LoadWAV("./sounds/5/c5.wav");
	
	octave5[7] = Mix_LoadWAV("./sounds/5/csharp5.wav");
	
	octave5[1] = Mix_LoadWAV("./sounds/5/d5.wav");
	
	octave5[8] = Mix_LoadWAV("./sounds/5/dsharp5.wav");
	
	octave5[2] = Mix_LoadWAV("./sounds/5/e5.wav");
	
	octave5[3] = Mix_LoadWAV("./sounds/5/f5.wav");
	
	octave5[9] = Mix_LoadWAV("./sounds/5/fsharp5.wav");
	
	octave5[4] = Mix_LoadWAV("./sounds/5/g5.wav");
	
	octave5[10] = Mix_LoadWAV("./sounds/5/gsharp5.wav");
	
	
	
	///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
}

int Audio::playSound(Mix_Chunk* soundFilePointer)
{
	int tempChannel;
		tempChannel = Mix_PlayChannel(-1, soundFilePointer, 0);
	return tempChannel;
	
	//	if( == -1)
	////	{
		//	printf("unable to play sound");
		//} 
}

void Audio::setOctave(int octaveNumber)
{
	octave = octaveNumber;
}

int Audio::getOctave()
{
	return octave;
}

void Audio::octaveDown()
{
	
	if (getOctave() > 0 )
	{
		setOctave(getOctave() - 1);
		
	}
	
	
}
void Audio::octaveUp()
{
	if (getOctave() < 5 )
	{
		setOctave(getOctave() + 1);
		
	}
	
}

void Audio::stopSound(int note)
{
	Mix_HaltChannel(note);
}

Mix_Chunk * Audio::getSoundFile(int note)
{
	switch (octave)
	{
		case 0:
			which = octave0[note];
			break;
		case 1:
			which = octave1[note];
			break;
		case 2:
			which = octave2[note];
			break;
		case 3:
			which = octave3[note];
			break;
		case 4:
			which = octave4[note];
			break;
		case 5:
			which = octave5[note];
			break;
		case 6:
			which = octave6[note];
			break;
		case 7:
			which = octave7[note];
			break;
	}

	return which;
}

