#include "stdafx.h"
#include <timeapi.h>
#include "Game.h"
#include "LoadData.h"
#include "Bullet.h"
#include "Console.h"
#include "Enemy.h"
#include "Player.h"
#include "Render.h"
#include "Scene.h"

bool gExit = false;
int32 gFrame = 0;

void Init()
{
	::timeBeginPeriod(1);
	cs_Initial();
	// dat파일을 불러와 게임 정보를 세팅
	LoadStageList();
	LoadMovementData();
	LoadEnemyData();
	InitCursor();
	InitBulletArray();
	InitEnemy();
	InitPlayer();
}

void Update()
{
	switch (gScene)
	{
	case SceneType::START: 
		break;
	case SceneType::STAGE:
		ResetBulletPosition();
		UpdateBullet();
		UpdateEnemy();
		UpdatePlayer();

		if (GetLeftEnemy() == 0)
		{
			gStageLevel++;
			if (gStageLevel > MAX_STAGE_LEVEL)
			{
				gScene = SceneType::GAME_CLEAR;
			}
			else
			{
				gScene = SceneType::LOAD;
			}
		}

		if (gPlayer.hp <= 0)
		{
			gScene = SceneType::GAME_OVER;
		}
		break;
	case SceneType::LOAD:
		InitPlayer();
		ResetBulletArray();
		ResetEnemy();
		LoadStageData();
		gScene = SceneType::STAGE;
		break;
	case SceneType::GAME_OVER: 
	case SceneType::GAME_CLEAR:
		gCursor.y = 8;
		break;
	case SceneType::PAUSE: 
		break;
	}
}

void Render()
{
	ClearBuffer();
	switch(gScene)
	{
	case SceneType::START:
		DrawCursor();
		DrawStartScene();
		printf("\n             ");
		printf("\n             ");
		break;
	case SceneType::STAGE: 
		DrawBullet();
		DrawEnemy();
		DrawPlayer();
		printf("\nSTAGE %d\n", gStageLevel);
		printf("HP : %d\n", gPlayer.hp);
		break;
	case SceneType::LOAD:
		printf("\n             ");
		printf("\n             ");
		break;
	case SceneType::GAME_OVER:
		printf("\n             ");
		printf("\n             ");
		DrawCursor();
		DrawGameOverScene();
		break;
	case SceneType::GAME_CLEAR:
		printf("\n             ");
		printf("\n             ");
		DrawCursor();
		DrawGameClearScene();
		break;
	case SceneType::PAUSE:
		printf("\nSTAGE %d\n", gStageLevel);
		printf("HP : %d\n", gPlayer.hp);
		DrawCursor();
		DrawPauseScene();
		break;
	}


	FlipBuffer();

}

bool KeyProcess()
{
	gFrame++;
	switch(gScene)
	{
	case SceneType::START:
		// 메뉴화면에서는 프레임 조정
		if (gFrame % 4 != 0)
		{
			return false;
		}
		// 위쪽 방향키.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gCursor.y -= 2;
		}
		// 아래쪽 방향키.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gCursor.y += 2;
		}

		gCursor.y = max(gCursor.y, 8);
		gCursor.y = min(gCursor.y, 10);

		// 엔터키
		if (GetAsyncKeyState(VK_RETURN) & 0x8001)
		{
			if (gCursor.y == 8)
			{
				gScene = SceneType::LOAD;
				InitCursor();
			}
			else
			{
				gExit = true;
			}
		}
		break;

	case SceneType::PAUSE:
		// 메뉴화면에서는 프레임 조정
		if (gFrame % 4 != 0)
		{
			return false;
		}
		// 위쪽 방향키.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gCursor.y -= 2;
		}
		// 아래쪽 방향키.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gCursor.y += 2;
		}

		gCursor.y = max(gCursor.y, 8);
		gCursor.y = min(gCursor.y, 10);

		// 엔터키
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (gCursor.y == 8)
			{
				gScene = SceneType::STAGE;
				InitCursor();
			}
			else
			{
				gStageLevel = 0;
				gScene = SceneType::START;
				InitCursor();
			}
		}
		break;
	case SceneType::STAGE:

		gPlayer.frameCount++;


		// 위쪽 방향키.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gPlayer.y -= 1;
		}
		// 아래쪽 방향키.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gPlayer.y += 1;
		}
		// 왼쪽 방향키.
		if (GetAsyncKeyState(VK_LEFT))
		{
			gPlayer.x -= 1;
		}
		// 오른쪽 방향키.
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gPlayer.x += 1;
		}


		// 플레이어 이동 반경 제한.
		gPlayer.x = max(gPlayer.x, 0);
		gPlayer.x = min(gPlayer.x, 79);
		gPlayer.y = max(gPlayer.y, 0);
		gPlayer.y = min(gPlayer.y, 23);

		// 콘트롤 키. (미사일 키)
		if (GetAsyncKeyState(VK_CONTROL))
		{
			if (gPlayer.frameCount % 2 == 0)
				CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
		}

		// ESC 키. (일시정지)
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		{
			gScene = SceneType::PAUSE;
		}
		break;
	case SceneType::GAME_OVER: 
	case SceneType::GAME_CLEAR:
		// 메뉴화면에서는 프레임 조정
		if (gFrame % 4 != 0)
		{
			return false;
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (gCursor.y == 8)
			{
				gStageLevel = 0;
				gScene = SceneType::START;
				InitCursor();
			}
		}
		break;
	case SceneType::LOAD: break;
	}
	

	return true;
}
