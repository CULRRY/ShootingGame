#include "stdafx.h"
#include "Game.h"
#include "LoadData.h"
#include "Bullet.h"
#include "Console.h"
#include "Enemy.h"
#include "Player.h"
#include "Render.h"
#include "Scene.h"

bool gExit = false;

void Init()
{
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
		break;
	case SceneType::STAGE: 
		DrawBullet();
		DrawEnemy();
		DrawPlayer();
		printf("STAGE %d", gStageLevel);
		printf("\nHP : %d\n", gPlayer.hp);
		break;
	case SceneType::LOAD: 
		break;
	case SceneType::GAME_OVER:
		DrawCursor();
		DrawGameOverScene();
		break;
	case SceneType::GAME_CLEAR:
		DrawCursor();
		DrawGameClearScene();
		break;
	case SceneType::PAUSE:
		DrawCursor();
		DrawPauseScene();
		break;
	}


	FlipBuffer();

}

bool KeyProcess()
{
	switch(gScene)
	{
	case SceneType::START:
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
		if (GetAsyncKeyState(VK_RETURN) & 0x8001)
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
