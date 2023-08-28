#include "stdafx.h"
#include <timeapi.h>
#include "Game.h"
#include "Render.h"

#define FPS_MS 20


int main(void)
{
	Init();


	DWORD startTime = timeGetTime();
	DWORD timeForFPS = startTime;
	DWORD idealTime = startTime;
	int32 frame = 0;
	DWORD overTime = 0;
	while (true)
	{

		frame++;

		// 초당 프레임 계산
		if (timeGetTime() - timeForFPS >= 1000)
		{
			printf("FPS: %d", frame);
			frame = 0;
			timeForFPS += 1000;
		}


		KeyProcess();

		Update();


		if (gExit == true)
		{
			return 0;
		}

		Render();

		// 50프레임 고정
		Sleep(FPS_MS - overTime);

		idealTime += FPS_MS;
		overTime = timeGetTime() - idealTime;

		if (overTime <= 0)
			overTime = 0;
		




	}
}
