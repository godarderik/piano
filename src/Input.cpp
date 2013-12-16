/*
 *  Input.cpp
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input.h"
#include <syslog.h>
#include "PDL.h"

int Input::findWhichKeyPressed(int xCoordinate, int yCoordinate)
{
	
	int temp = xCoordinate;
	xCoordinate = yCoordinate;
	yCoordinate = temp;
	yCoordinate = 320 - yCoordinate;
	//version = "pixi";
	syslog(LOG_ERR, "Before: %i", xCoordinate);
	syslog(LOG_ERR, "Device: %s", version);
	if (version == "pixi")
	{		xCoordinate = xCoordinate * 1.2;
	}
	syslog(LOG_ERR, "After After: %i", xCoordinate);
	
	int keyNumber;
		//we need separate testing for pre and pixi
		if (yCoordinate > 180) //300 is the total- the length of the black key
		{
			keyNumber = xCoordinate/68;
			//Divide the x of the touch event by 68, which is the width of a key
		}
	else if (yCoordinate <= 180){
		//Touch could potentially be on a black key
		//Find which white key it is on, and then see if there is a black key on top of it
		int tempX = xCoordinate/68;
		if (tempX == 0)
		{
			if (xCoordinate % 68 < 43)
			{
				keyNumber = 0;
			}
			else {
				keyNumber = 7;
			}
		}
		else if (tempX == 1)
		{
			if (xCoordinate % 68 < 25 )
			{
				keyNumber = 7;
			}
			else if (xCoordinate % 68 > 43)
			{
				keyNumber =8;
			}
			else {
				keyNumber = 1;
			}
		}
		else if (tempX == 2)
		{
			if (xCoordinate % 68 < 25 )
			{
				keyNumber = 8;
			}
			else {
				keyNumber = 2;
			}
		}
		else if (tempX == 3)
		{
			if (xCoordinate % 68 > 43)
			{
				keyNumber = 9;
			}
			else {
				keyNumber = 3;
			}
		}
		else if(tempX == 4) {
			if (xCoordinate % 68 < 25 )
			{
				keyNumber = 9;
				
			}
			else if (xCoordinate % 68 > 43)
			{
				keyNumber = 10;
			}
			else {
				keyNumber = 4;
			}
		}
		else if (tempX == 5)
		{
			if (xCoordinate % 68 < 25 )
			{
				keyNumber = 10;
				
			}
			else if (xCoordinate % 68 > 43)
			{
				keyNumber = 11;
			}
			else {
				keyNumber = 5;
			}
		}
		else if (tempX == 6){
			if (xCoordinate % 68 < 25 )
			{
				keyNumber = 11;
				
			}
			else {
				keyNumber = 6;
			}
		}
	}
		syslog(LOG_ERR, "%i", keyNumber);
	
	return keyNumber;
}
Input::Input()
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
}