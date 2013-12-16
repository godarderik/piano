/*
 *  key.h
 *  Piano
 *
 *  Created by Erik Godard on 5/29/10.
 *  Copyright 2010 Erik Godard Apps. All rights reserved.
 *
 */
class key
{
public:
	//getters
	int getColor();
	bool getPressed();
	char getNote();
	bool getPlaying();
	
	//setters
	void setColor(int);
	void setPressed(bool);
	void setNote(int);
	int channel;
	
	//constructor
	key();
private:
	int color;
	bool pressed;
	int note;
};
