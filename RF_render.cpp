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
#ifdef RF_RENDER

//Includes for render part
#include "RF_main.h"
#include "RF_render.h"

//Render function definitions
bool RF_CreateWindow(const std::string caption /* = "RF" */, int width /* = 800 */, int height /* = 600 */, bool fullscreen /* = false */)
{
	//Set GL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

	//Set caption
	SDL_WM_SetCaption(caption.c_str(), NULL);

	//Create video mode
	if (!fullscreen)
	{
		if (SDL_SetVideoMode(width, height, 32, SDL_OPENGL) == NULL)
		{
			RF_Log(SDL_GetError());
			return false;
		}
	}
	else //Fullscreen
	{
		if (SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_FULLSCREEN) == NULL)
		{
			RF_Log(SDL_GetError());
			return false;
		}
	}

	//OpenGL specific functions
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);

	//GLEW init, the functions doesn't return false if GLEW fails
#ifdef RF_GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to start\n"; 
		RF_Log("GLEW failed to start");
	}
#endif //RF_GLEW

	return true;
}

#endif //RF_RENDER