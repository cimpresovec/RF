#include "RF.h"

int main(int argc, char* args[])
{
	if (!RF_Initialize())
	{
		return 1;
	}

	if (!RF_CreateWindow()) return false;

	RF_SoundEngine soundEngine = RF_CreateSoundEngine();
	RF_SoundSource music = RF_LoadSound(soundEngine, "music.mp3");
	soundEngine->play2D(music);

	bool play = true;

	RF_LoadTexture("tile0000.png");

	//Font
	RF_Font font = RF_LoadFont("cour.ttf");

	//Sound

	float angle = 0;

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
		}

		//Logic
		angle += 0.5;

		//Render
		RF_ClearWindow();

		RF_DrawRectangle(0.5,0.5,.5,.5, angle, RF_Color(), 1);
		RF_DrawCircle(-0.5, -0.5, .2f, RF_Color(1.f, 0.f, 0.f));

		RF_DrawLine(0,0,1,1);
		RF_DrawTriangle(-.5, .5, .5, .7f, -angle*2);
		RF_DrawText(font, "RF Framework by Luka", 0, -.8f);
		
		RF_SwapBuffer();

		RF_HandleFps();
	}

	return 0;
}