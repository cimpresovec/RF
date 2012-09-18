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

//This file is the rendering part of the framework
#ifndef RF_RENDER_H
#define RF_RENDER_H

//Linker setting for libraries
#if defined(_MSC_VER)
#	pragma comment(lib, "SDL_image.lib")
#	pragma comment(lib, "OpenGL32.lib")
#	ifdef RF_GLEW
#		pragma comment(lib, "glew32.lib")
#	endif
#	ifdef RF_FTGL
#		pragma comment(lib, "freetype.lib")
#		pragma comment(lib, "ftgl.lib")
#	endif
#else
//TODO
#endif

//Libraries needed for RF_main
#if defined(_MSC_VER)
#	ifdef RF_GLEW
#		define NO_SDL_GLEXT
#		include <GL\glew.h>
#	endif
#	include <SDL_image.h>
#	include <SDL_opengl.h>
#	ifdef RF_FTGL
#		include <FTGL\ftgl.h>
#	endif
#else
//TODO 
#endif

//Definitions, etc.

//Structures/classes
//Simple color structure
struct RF_Color
{
	float r, g, b, a;
	RF_Color(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
};

//Render function declarations
//Create a window
bool RF_CreateWindow(const std::string caption = "RF", int width = 800, int height = 600, bool fullscreen = false);

//Load image/texture
unsigned int RF_LoadTexture(const std::string);

//Destroy texture
void RF_DeleteTexture(unsigned int texture);

//Shape rendering functions
//Rectangle drawing function; r = rotation in degrees, col is color, x/yScale is for scaling the render, x/yRotOffset is for changing the pivot/origin for rotation
void RF_DrawRectangle(float x, float y, float w, float h, float r = 0.f, RF_Color col = RF_Color(), UINT texture = 0, float xScale = 1.f, float yScale = 1.f);

//Draw a triangle, works line a triangle in a rectangle
void RF_DrawTriangle(float x, float y, float w, float h, float r = 0.f, RF_Color col = RF_Color(), float xScale = 1.f, float yScale = 1.f);

//Draw a circle; r = radius
void RF_DrawCircle(float x, float y, float r, RF_Color col = RF_Color());

//Draw a line; w = line width
void RF_DrawLine(float x1, float y1, float x2, float y2, float w = 1.f, RF_Color col = RF_Color());

//Inline functions for clear and swap
inline void RF_ClearWindow()
{
	return glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void RF_SwapBuffer()
{
	return SDL_GL_SwapBuffers();
}

#endif //RF_RENDER_H
#endif //RF_RENDER