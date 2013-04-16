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
#if defined( _MSC_VER )
#	pragma comment( lib, "SDL_image.lib" )
#	pragma comment( lib, "OpenGL32.lib" )
#	ifdef RF_GLEW
#		pragma comment( lib, "glew32.lib" )
#	endif
#	ifdef RF_FTGL
#		pragma comment( lib, "freetype.lib" )
#		pragma comment( lib, "ftgl.lib" )
#	endif
#else
//TODO
#endif

//Libraries needed for RF_main
#if defined( _MSC_VER )
#	ifdef RF_GLEW
#		define NO_SDL_GLEXT
#		include <GL\glew.h>
#	endif
#	include <SDL_image.h>
#	include <SDL_opengl.h>
#	ifdef RF_FTGL
#		include <ftgl\ftgl.h>
#	endif
#else
//TODO 
#endif

namespace rf
{
	//Definitions, etc.

	//Structures/classes
	//Simple color structure
	struct Color
	{
		float r, g, b, a;
		Color( float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f );
	};

	//Some window globals
	extern unsigned int windowWidth_;
	extern unsigned int windowHeight_;

	//Render function declarations
	//Create a window
	bool createWindow( const std::string caption = "RF", const int width = 800, const int height = 600, const bool fullscreen = false);

	//Load image/texture
	unsigned int loadTexture( const std::string );

	//Destroy texture
	void deleteTexture( unsigned int texture );

	//Shape rendering functions
	//Rectangle drawing function; r = rotation in degrees, col is color, x/yScale is for scaling the render, x/yRotOffset is for changing the pivot/origin for rotation
	void drawRectangle( const float x, const float y, const float w, const float h, const float r = 0.f, const Color& col = Color(), const UINT texture = 0, const float xScale = 1.f, const float yScale = 1.f );

	//Draw a triangle, works line a triangle in a rectangle
	void drawTriangle( const float x, const float y, const float w, const float h, const float r = 0.f, const Color& col = Color(), const float xScale = 1.f, const float yScale = 1.f );

	//Draw a circle; r = radius
	void drawCircle( const float x, const float y, const float r, const Color& col = Color() );

	//Draw a line; w = line width
	void drawLine( const float x1, const float y1, const float x2, const float y2, const float w = 1.f, const Color& col = Color() );

	//Text rendering function
	#ifdef RF_FTGL

	//Definitions
	typedef FTGLTextureFont* Font;

	//Inline function to load a font
	inline FTGLTextureFont* loadFont( const std::string fontPath )
	{
		return new FTGLTextureFont( fontPath.c_str() );
	}

	//Draw text using a font, at position x,y with size and color. Changing SIZE is a performance hog!
	void drawText( FTGLTextureFont* font, const std::string text, const float x, const float y, const int size = 25, const Color& col = Color(), const float scaleFactor = 400.f );
	#endif

	//Inline functions for clear and swap
	inline void clearWindow()
	{
		return glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	inline void swapBuffer()
	{
		return SDL_GL_SwapBuffers();
	}

	//Get mouse position in passed variables to get mouse position, dependent on window size
	void getMousePosition( float& x, float& y );
}

#endif //RF_RENDER_H
#endif //RF_RENDER