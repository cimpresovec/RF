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

//Includes for main
#include "RF_main.h"

//Objects, definitions, etc.
SDL_Event event;
float fpsTimer = 0;

//Main function definitions
bool RF_Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		RF_Log(SDL_GetError());
		return false;
	}
	return true;
}

bool RF_Log(const std::string text, const std::string file /* = "Log.txt" */)
{
	std::ofstream logFile;

	logFile.open(file, std::ios::out | std::ios::app);
	
	if (!logFile.is_open())
	{
		std::cout << "Can't open " << file << "!\n";
		return false;
	}

	//Get DateTime
	time_t rawtime;
	time (&rawtime);
	char time[100];
	ctime_s(time, 100, &rawtime);

	//Log
	logFile << time << text << "\n\n";

	logFile.close();

	return true;
}

bool RF_ClearLog(const std::string file /* = "Log.txt" */)
{
	std::ofstream logFile;

	logFile.open(file);

	if(!logFile.is_open())
	{
		std::cout << "Can't open " << file << "!\n";
		return false;
	}

	logFile.close();

	return true;
}

#endif //RF_MAIN
