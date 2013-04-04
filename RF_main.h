/*
* Copyright (c) 2012-2012 Luka Horvat (redreaper132@gmail.com) http://www.redgamedevblog.blogspot.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

//Configuration file
#include "RF_config.h"
#ifdef RF_MAIN

//This file is the main of the framework and has to always be included for it to work
#ifndef RF_MAIN_H
#define RF_MAIN_H

//Cross-platform default libraries
#include <string>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

//Linker setting for libraries
#if defined( _MSC_VER )
#	pragma comment( lib, "SDLmain.lib" )
#	pragma comment( lib, "SDL.lib" )
#else
//TODO
#endif

//Libraries needed for RF_main
#if defined( _MSC_VER )
#	include <SDL.h>
#else
//TODO 
#endif

//Objects, definitions, etc.
extern SDL_Event event; //Event handler
extern float fpsTimer; //For framerate cap
#define RF_EventType event.type
#define RF_EventKey event.key.keysym.sym
#define RF_EventMouse event.button.button
#define PI 3.141592654f


//Main function declarations

//Initialize SDL
bool RF_Initialize();

//Log string, text is appended
bool RF_Log( const std::string text, const std::string file = "Log.txt" );

//Clear log
bool RF_ClearLog( const std::string file = "Log.txt" );

//Begin loop functions for timer
void RF_BeginLoop();

//Framerate cap/delay
void RF_HandleFps();

//Inline functions for event check
inline int RF_CheckEvent()
{
	return SDL_PollEvent( &event );
}

//Inline function to calculate angle between the line from point(0,0) to passed coordinates, relative to X axis, angle increases counter-clockwise
inline float RF_CalculateAngle( const float xPosition, const float yPosition )
{
	return atan2f( yPosition, xPosition ) * 180 / PI;
}

#endif // RF_MAIN_H
#endif //RF_MAIN