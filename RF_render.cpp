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

//Structures/classes
//Color structure
RF_Color::RF_Color(float r /* = 1.f */, float g /* = 1.f */, float b /* = 1.f */, float a /* = 1.f */)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

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
	glClearColor(0, 0, 0, 1);
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

unsigned int RF_LoadTexture(const std::string fileName)
{
	SDL_Surface* image = IMG_Load(fileName.c_str());

	if (!image)
	{
		std::string errMsg = "Problem loading image " + fileName;
		std::cout << errMsg << "\n";
		RF_Log(errMsg);
		return 0;
	}

	//Display format
	SDL_DisplayFormatAlpha(image);

	//Generating the texture
	unsigned int texture = 0;

	glGenTextures(1, &texture);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	SDL_FreeSurface(image);

	glDisable(GL_TEXTURE_2D);

	return texture;
}

void RF_DeleteTexture(unsigned int texture)
{
	glDeleteTextures(1, &texture);
	texture = 0;
}

//Shape rendering functions
void RF_DrawRectangle(float x, float y, float w, float h, float r /* = 0 */, RF_Color col /* = RF_Color */, UINT texture /* = 0 */, float xScale /* = 1.f */, float yScale /* = 1.f */)
{
	if (r != 0.f || xScale != 1.f || yScale != 1.f)
	{
		glPushMatrix();
		glTranslatef(x, y, 0.f);
		glRotatef(r, 0.f, 0.f, 1.f);
		glScalef(xScale, yScale, 1.f);
		glTranslatef(-x, -y, 0.f);
	}

	if (texture != 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		glColor4f(col.r, col.g, col.b, col.a);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1, 1); glVertex2f(x+w/2, y-h/2);
		glTexCoord2f(1, 0); glVertex2f(x+w/2, y+h/2);
		glTexCoord2f(0, 1); glVertex2f(x-w/2, y-h/2);
		glTexCoord2f(0, 0); glVertex2f(x-w/2, y+h/2);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glColor4f(col.r, col.g, col.b, col.a);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(x+w/2, y-h/2);
		glVertex2f(x+w/2, y+h/2);
		glVertex2f(x-w/2, y-h/2);
		glVertex2f(x-w/2, y+h/2);
		glEnd();
	}

	if (r != 0.f || xScale != 1.f || yScale != 1.f)
	{
		glPopMatrix();
	}
}

void RF_DrawTriangle(float x, float y, float w, float h, float r /* = 0 */, RF_Color col /* = RF_Color */, float xScale /* = 1.f */, float yScale /* = 1.f */)
{
	if (r != 0.f || xScale != 1.f || yScale != 1.f)
	{
		glPushMatrix();
		glTranslatef(x, y, 0.f);
		glRotatef(r, 0.f, 0.f, 1.f);
		glScalef(xScale, yScale, 1.f);
		glTranslatef(-x, -y, 0.f);
	}

	glColor4f(col.r, col.g, col.b, col.a);
	glBegin(GL_TRIANGLES);
	glVertex2f(x+w/2, y-h/2);
	glVertex2f(x, y+h/2);
	glVertex2f(x-w/2, y-h/2);
	glEnd();

	if (r != 0.f || xScale != 1.f || yScale != 1.f)
	{
		glPopMatrix();
	}
}

void RF_DrawCircle(float x, float y, float r, RF_Color col /* = RF_Color */)
{
	glColor4f(col.r, col.g, col.b, col.a);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (float angle = 0; angle <= 2*PI+.2f; angle += .2f)
	{
		glVertex2f(x + sin(angle) * r, y + cos(angle) * r);
	}
	glEnd();
}

void RF_DrawLine(float x1, float y1, float x2, float y2, float w /* = 1 */, RF_Color col /* = RF_Color */)
{
	glColor4f(col.r, col.g, col.b, col.a);

	glLineWidth(w);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

#endif //RF_RENDER