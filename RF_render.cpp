/*
* Copyright (c)2012-2012 Luka Horvat (redreaper132@gmail.com)http://www.redgamedevblog.blogspot.com
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
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

namespace rf
{
	//Structures/classes
	//Color structure
	Color::Color( float r /* = 1.f */, float g /* = 1.f */, float b /* = 1.f */, float a /* = 1.f */ )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	//Global window variables
	unsigned int windowWidth_ = 0;
	unsigned int windowHeight_ = 0;

	//Render function definitions
	bool createWindow( const std::string caption /* = "RF" */, const int width /* = 800 */, const int height /* = 600 */, const bool fullscreen /* = false */ )
	{
		//Set GL attributes
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		//Set caption
		SDL_WM_SetCaption( caption.c_str (), NULL );

		//Create video mode
		if ( !fullscreen )
		{
			if ( SDL_SetVideoMode( width, height, 32, SDL_OPENGL ) == NULL )
			{
				log( SDL_GetError() );
				return false;
			}
		}
		else //Fullscreen
		{
			if ( SDL_SetVideoMode( width, height, 32, SDL_OPENGL | SDL_FULLSCREEN ) == NULL )
			{
				log ( SDL_GetError() );
				return false;
			}
		}

		//Set globals
		windowWidth_ = width;
		windowHeight_ = height;

		//OpenGL specific functions
		glClearColor( 0, 0, 0, 1 );
		glShadeModel( GL_SMOOTH );
		glViewport( 0, 0, width, height );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_LIGHTING );

		//glHint ( GL_LINE_SMOOTH_HINT, GL_NICEST );
		//glHint ( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		//glEnable ( GL_LINE_SMOOTH );
		//glEnable ( GL_POLYGON_SMOOTH );

		//GLEW init, the functions doesn't return false if GLEW fails
		#ifdef RF_GLEW
		if ( glewInit() != GLEW_OK )
		{
			std::cout << "GLEW failed to start\n"; 
			log( "GLEW failed to start" );
		}
		#endif //RF_GLEW

		return true;
	}

	unsigned int loadTexture( const std::string fileName )
	{
		SDL_Surface* image = IMG_Load( fileName.c_str() );

		if ( !image )
		{
			std::string errMsg = "Problem loading image " + fileName;
			std::cout << errMsg << "\n";
			log( errMsg );
			return 0;
		}

		//Display format
		SDL_DisplayFormatAlpha( image );

		//Generating the texture
		unsigned int texture = 0;

		glGenTextures( 1, &texture );

		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture );

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels );

		SDL_FreeSurface( image );

		glDisable( GL_TEXTURE_2D );

		return texture;
	}

	void deleteTexture( unsigned int texture )
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	//Shape rendering functions
	void drawRectangle( const float x, const float y, const float w, const float h, const float r /*= 0.f*/, const Color& col /*= Color()*/, const UINT texture /*= 0*/, const float xScale /*= 1.f*/, const float yScale /*= 1.f*/ )
	{
		if ( r != 0.f || xScale != 1.f || yScale != 1.f )
		{
			glPushMatrix();
			glTranslatef( x, y, 0.f );
			glRotatef( r, 0.f, 0.f, 1.f );
			glScalef( xScale, yScale, 1.f );
			glTranslatef( -x, -y, 0.f );
		}

		if ( texture != 0 )
		{
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, texture );

			glColor4f( col.r, col.g, col.b, col.a );
			glBegin( GL_TRIANGLE_STRIP );
			glTexCoord2f( 1, 1 ); glVertex2f( x+w/2, y-h/2 );
			glTexCoord2f( 1, 0 ); glVertex2f( x+w/2, y+h/2 );
			glTexCoord2f( 0, 1 ); glVertex2f( x-w/2, y-h/2 );
			glTexCoord2f( 0, 0 ); glVertex2f( x-w/2, y+h/2 );
			glEnd();

			glDisable( GL_TEXTURE_2D );
		}
		else
		{
			glColor4f( col.r, col.g, col.b, col.a );
			glBegin( GL_TRIANGLE_STRIP );
			glVertex2f( x+w/2, y-h/2 );
			glVertex2f( x+w/2, y+h/2 );
			glVertex2f( x-w/2, y-h/2 );
			glVertex2f( x-w/2, y+h/2 );
			glEnd();
		}

		if ( r != 0.f || xScale != 1.f || yScale != 1.f )
		{
			glPopMatrix();
		}
	}

	void drawTriangle( const float x, const float y, const float w, const float h, const float r /*= 0.f*/, const Color& col /*= Color()*/, const float xScale /*= 1.f*/, const float yScale /*= 1.f */ )
	{
		if ( r != 0.f || xScale != 1.f || yScale != 1.f )
		{
			glPushMatrix();
			glTranslatef( x, y, 0.f );
			glRotatef( r, 0.f, 0.f, 1.f );
			glScalef( xScale, yScale, 1.f );
			glTranslatef( -x, -y, 0.f );
		}

		glColor4f( col.r, col.g, col.b, col.a );
		glBegin( GL_TRIANGLES );
		glVertex2f( x+w/2, y-h/2 );
		glVertex2f( x, y+h/2 );
		glVertex2f( x-w/2, y-h/2 );
		glEnd();

		if ( r != 0.f || xScale != 1.f || yScale != 1.f )
		{
			glPopMatrix();
		}
	}

	void drawCircle( const float x, const float y, const float r, const Color& col /*= Color()*/ )
	{
		glColor4f( col.r, col.g, col.b, col.a );

		glBegin( GL_TRIANGLE_FAN );
		glVertex2f( x, y );
		for ( float angle = 0; angle <= 2*PI+.2f; angle += .2f )
		{
			glVertex2f (x + sin( angle )* r, y + cos( angle )* r );
		}
		glEnd();
	}

	void drawLine( const float x1, const float y1, const float x2, const float y2, const float w /*= 1.f*/, const Color& col /*= Color()*/ )
	{
		glColor4f( col.r, col.g, col.b, col.a );

		glLineWidth( w );
		glBegin( GL_LINES );
		glVertex2f( x1, y1 );
		glVertex2f( x2, y2 );
		glEnd();
	}

	void getMousePosition( float& x, float& y )
	{
		int x_, y_;
		SDL_GetMouseState( &x_, &y_ );
		x = (x / (windowWidth_ / 2.f)) - 1.0f;
		y = -((y / (windowHeight_ / 2.f)) - 1.0f);
	}

	//Text rendering function
	#ifdef RF_FTGL
	void drawText( FTGLTextureFont* font, const std::string text, const float x, const float y, const int size /*= 20*/, const Color& col /*= Color()*/, const float scaleFactor /*= 400.f*/ )
	{
		//Check if the font size is the same, try to AVOID CHANGING SIZE
		if ( font->FaceSize()!= size )
		{
			font->FaceSize( size );
		}

		glColor4f( col.r, col.g, col.b, col.a );

		glPushMatrix();

		glScalef( 1.f/scaleFactor, 1.f/scaleFactor, 1.f );

		font->Render( text.c_str() );

		glPopMatrix();
	}

	#endif
}

#endif //RF_RENDER