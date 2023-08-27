#include "stdafx.h"
#include <timeapi.h>
#include "Game.h"
#include "LoadData.h"
#include "Scene.h"

int main(void)
{


	Init();

	while (true)
	{

		KeyProcess();

		Update();

		if (gExit == true)
		{
			return 0;
		}

		Render();

		Sleep(200);
	}
}
