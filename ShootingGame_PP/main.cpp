#include "stdafx.h"

#include "Game.h"
#include "LoadData.h"


int main(void)
{

	LoadMovementData();
	LoadEnemyData();
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
