#include "RF.h"

int main(int argc, char* args[])
{
	if (!RF_Initialize())
	{
		return 1;
	}

	if (!RF_CreateWindow()) return false;

	bool play = true;

	RF_LoadTexture("tile0000.png");

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

		RF_DrawRectangle(0.5,0.5,.5,.5, angle, RF_Color(), 1, 1.f);
		RF_DrawCircle(-0.5, -0.5, .2f, RF_Color(1.f, 0.f, 0.f));
		//RF_DrawRectangle(-0.5,-.5,.5,.5, 0, RF_Color(0.f,0.f));
		RF_DrawLine(0,0,1,1);
		RF_DrawTriangle(-.5, .5, .5, .7f, -angle*2);
		
		RF_SwapBuffer();

		RF_HandleFps();
	}

	return 0;
}