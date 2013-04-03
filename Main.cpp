#include "RF.h"

bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1-w1/2 > x2+w2/2) return false;
	if (x1+w1/2 < x2-w2/2) return false;
	if (y1-h1/2 > y2+h2/2) return false;
	if (y1+h1/2 < y2-h2/2) return false;
	return true;
}

struct Ball
{
	float x, y, w, h, xVel, yVel;

	Ball(){
		x = y = 0.f;
		w = 20/800.f;
		h = 20/600.f;
		xVel = 0.01f;
		yVel = 0.02f;
	}

	void logic(){
		x += xVel;
		y += yVel;

		if (y > 1.f-h/2 || y < -1.f+h/2) yVel = -yVel;
		if (x > 1.f-w/2 || x < -1.f+w/2) {
			xVel = -xVel;
			if (xVel > 0.f) xVel = 0.01f;
			else xVel = -0.01f;
		}
	}

	void colide(float y)
	{
		yVel = (this->y - y)/3.f;
		if (xVel > 0.f) xVel += 0.002f;
		else xVel -= 0.002f;
		if (xVel > 0.1) xVel = 0.1;
		xVel = -xVel;
	}

	void render(){
		RF_DrawRectangle(x, y, w, h, x, RF_Color(0, 1, 0));
	}
};

class Player
{
	float x, y, w, h;
	bool left, right, up, down;
public:
	Player(){
		x = -0.9f;
		y = 0.f;
		w = 20/800.f;
		h = 100/600.f;
		left = right = up = down = false;
	}

	void events()
	{
		if (RF_EventType == SDL_KEYDOWN)
		{
			switch(RF_EventKey)
			{
			case SDLK_LEFT: left = true; break;
			case SDLK_RIGHT: right = true; break;
			case SDLK_UP: up = true; break;
			case SDLK_DOWN: down = true; break;
			default: break;
			}
		}

		else if (RF_EventType == SDL_KEYUP)
		{
			switch(RF_EventKey)
			{
			case SDLK_LEFT: left = false; break;
			case SDLK_RIGHT: right = false; break;
			case SDLK_UP: up = false; break;
			case SDLK_DOWN: down = false; break;
			default: break;
			}
		}
	}

	void logic(Ball* ball)
	{
		if (up)
		{
			y += 0.02f;
		}

		if (down)
		{
			y -= 0.02f;
		}

		if (y > 1.f-h/2) y = 1.f-h/2;
		else if (y < -1.f+h/2) y = -1.f+h/2;

		if (checkCollision(x, y, w, h, ball->x, ball->y, ball->w, ball->h))
		{
			ball->colide(y);
		}
	}

	void render(){
		RF_DrawRectangle(x, y, w, h, 0.f, RF_Color(1, 0, 0));
	}
};
class Player2
{
	float x, y, w, h;
	bool left, right, up, down;
public:
	Player2(){
		x = 0.9f;
		y = 0.f;
		w = 20/800.f;
		h = 100/600.f;
		left = right = up = down = false;
	}

	void events()
	{
		if (RF_EventType == SDL_KEYDOWN)
		{
			switch(RF_EventKey)
			{
			case SDLK_LEFT: left = true; break;
			case SDLK_RIGHT: right = true; break;
			case SDLK_w: up = true; break;
			case SDLK_s: down = true; break;
			default: break;
			}
		}

		else if (RF_EventType == SDL_KEYUP)
		{
			switch(RF_EventKey)
			{
			case SDLK_LEFT: left = false; break;
			case SDLK_RIGHT: right = false; break;
			case SDLK_w: up = false; break;
			case SDLK_s: down = false; break;
			default: break;
			}
		}
	}

	void logic(Ball* ball)
	{
		if (up)
		{
			y += 0.02f;
		}

		if (down)
		{
			y -= 0.02f;
		}

		if (y > 1.f-h/2) y = 1.f-h/2;
		else if (y < -1.f+h/2) y = -1.f+h/2;

		if (checkCollision(x, y, w, h, ball->x, ball->y, ball->w, ball->h))
		{
			ball->colide(y);
		}
	}

	void render(){
		RF_DrawRectangle(x, y, w, h, 0.f, RF_Color(1, 0, 0));
	}
};
int main(int argc, char* args[])
{
	if (!RF_Initialize())
	{
		return 1;
	}

	if (!RF_CreateWindow("RF", 800, 600, false)) return false;

	RF_SoundEngine soundEngine = RF_CreateSoundEngine();
	RF_SoundSource music = RF_LoadSound(soundEngine, "music.mp3");
	soundEngine->play2D(music);

	bool play = true;

	RF_LoadTexture("logo.png");

	//Font
	//RF_Font font = RF_LoadFont("cour.ttf");
	FTGLTextureFont* font = new FTGLTextureFont("cour.ttf");
	
	if (font->Error()	)
	{
		return -1;
	}
	font->FaceSize(20);

	//Sound

	float angle = 0;

	Player player;
	Player2 player2;
	Ball ball;

	while (play)
	{
		RF_BeginLoop();

		//Events
		if(RF_CheckEvent())
		{
			if (RF_EventType == SDL_KEYDOWN && RF_EventKey == SDLK_ESCAPE)
			{
				play = false;
			}

			player.events();
			player2.events();
		}

		//Logic
		player.logic(&ball);
		player2.logic(&ball);
		ball.logic();

		//Render
		RF_ClearWindow();

		player.render();
		player2.render();
		ball.render();
		//Fonti TODO 
		glPushMatrix();
		glScalef(1.f/400.,1./400.,1.);
		font->Render("Hello World. Danes je lep dan");
		glPopMatrix ();

		RF_SwapBuffer();

		RF_HandleFps();
	}

	return 0;
}