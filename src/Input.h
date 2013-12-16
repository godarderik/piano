/*
 *  Input.h
 *  Piano
 *
 *  Created by Erik Godard on 8/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

class Input
{
public:
	int findWhichKeyPressed(int xCoordinate, int yCoordinate);
	
	Input();
	
private:
	const char* version;
	int versionNum;
	PDL_ScreenMetrics outMetrics;
};