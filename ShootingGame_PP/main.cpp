#include "stdafx.h"
#include <timeapi.h>
#include "Game.h"
#include "Render.h"

#define FPS_MS 50


int main(void)
{


	Init();

	DWORD start = timeGetTime();
	int32 frame = 0;

	DWORD startTime = timeGetTime();
	DWORD prevTime = startTime;
	int delayTime = 20;
	char fpsStr[15];
	while (true)
	{

		frame++;
		if (timeGetTime() - start >= 1000)
		{
			printf("FPS: %lld", frame);
			frame = 0;
			start = timeGetTime();
		}


		KeyProcess();

		Update();


		if (gExit == true)
		{
			return 0;
		}

		Render();

		// 20프레임 고정
		Sleep(delayTime);

		prevTime = startTime;
		startTime = timeGetTime();
		DWORD elapsedTime = startTime - prevTime;
		if (elapsedTime <= FPS_MS)
		{
			delayTime = FPS_MS;
		}
		else
		{
			delayTime = FPS_MS - (elapsedTime - FPS_MS);
		}




	}
}
