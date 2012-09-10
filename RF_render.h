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

//This file is the rednering part of the framework
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

//Render function declarations

#endif //RF_RENDER_H
#endif //RF_RENDER