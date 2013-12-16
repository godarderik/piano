/*
 *  key.cpp
 *  Piano
 *
 *  Created by Erik Godard on 5/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "key.hpp"
#include <stdio.h>
//Getters
int key::getColor()
{
	return color;
}
bool key::getPressed()
{
	return pressed;
}
char key::getNote()
{
	return note;
}

//Setters
void key::setColor(int input)
{
	color = input;
}
void key::setPressed (bool input)
{
	pressed = input;
}
void key::setNote(int input)
{
	note = input;
}
key::key()
{
	channel = 0;
}


