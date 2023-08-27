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
	// dat������ �ҷ��� ���� ������ ����
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
		// �޴�ȭ�鿡���� ������ ����
		if (gFrame % 4 != 0)
		{
			return false;
		}
		// ���� ����Ű.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gCursor.y -= 2;
		}
		// �Ʒ��� ����Ű.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gCursor.y += 2;
		}

		gCursor.y = max(gCursor.y, 8);
		gCursor.y = min(gCursor.y, 10);

		// ����Ű
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
		// �޴�ȭ�鿡���� ������ ����
		if (gFrame % 4 != 0)
		{
			return false;
		}
		// ���� ����Ű.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gCursor.y -= 2;
		}
		// �Ʒ��� ����Ű.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gCursor.y += 2;
		}

		gCursor.y = max(gCursor.y, 8);
		gCursor.y = min(gCursor.y, 10);

		// ����Ű
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


		// ���� ����Ű.
		if (GetAsyncKeyState(VK_UP) & 0x8001)
		{
			gPlayer.y -= 1;
		}
		// �Ʒ��� ����Ű.
		if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		{
			gPlayer.y += 1;
		}
		// ���� ����Ű.
		if (GetAsyncKeyState(VK_LEFT))
		{
			gPlayer.x -= 1;
		}
		// ������ ����Ű.
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gPlayer.x += 1;
		}


		// �÷��̾� �̵� �ݰ� ����.
		gPlayer.x = max(gPlayer.x, 0);
		gPlayer.x = min(gPlayer.x, 79);
		gPlayer.y = max(gPlayer.y, 0);
		gPlayer.y = min(gPlayer.y, 23);

		// ��Ʈ�� Ű. (�̻��� Ű)
		if (GetAsyncKeyState(VK_CONTROL))
		{
			if (gPlayer.frameCount % 2 == 0)
				CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
		}

		// ESC Ű. (�Ͻ�����)
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		{
			gScene = SceneType::PAUSE;
		}
		break;
	case SceneType::GAME_OVER: 
	case SceneType::GAME_CLEAR:
		// �޴�ȭ�鿡���� ������ ����
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
