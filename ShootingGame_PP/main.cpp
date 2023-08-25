#include "stdafx.h"

#include "Game.h"


int main(void)
{
	Init();

	while (true)
	{

		KeyProcess();

		Update();

		Render();

		Sleep(200);
	}


	return 0;
}