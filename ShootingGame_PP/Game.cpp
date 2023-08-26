#include "stdafx.h"
#include "Game.h"

#include "LoadData.h"
#include "Bullet.h"
#include "Console.h"
#include "Enemy.h"
#include "Player.h"
#include "Render.h"
#include "Scene.h"

void Init()
{
	cs_Initial();
	LoadStageList();
	LoadMovementData();
	LoadEnemyData();
	InitBulletArray();
	InitEnemy();
	InitPlayer();



	CreateEnemy(2, 5, 10);
	CreateEnemy(3, 5, 40);
}

void Update()
{
	switch (gScene)
	{
	case SceneType::START: 
		
		break;
	case SceneType::STAGE:
		ResetBulletPostion();
		UpdateBullet();
		UpdateEnemy();
		UpdatePlayer();
		break;
	case SceneType::LOAD:
		LoadStageData();
		gScene = SceneType::STAGE;
		break;
	case SceneType::GAME_OVER: 
		break;
	case SceneType::PAUSE: 
		break;
	}
}

void Render()
{
	Buffer_Clear();
	DrawBullet();
	DrawEnemy();
	DrawPlayer();
	Buffer_Flip();
	printf("\nHP : %d", gPlayer.hp);
}

bool KeyProcess()
{
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
	// 위쪽 방향키.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		gPlayer.y--;
	}
	// 아래쪽 방향키.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		gPlayer.y++;
	}

	//-------------------------------------------------------------
	// 플레이어 이동 반경 제한.
	// 게임 화면에서 플레이어가 이동 가능한 구역을 제한한다.
	//-------------------------------------------------------------

	gPlayer.x = max(gPlayer.x, 0);
	gPlayer.x = min(gPlayer.x, 79);
	gPlayer.y = max(gPlayer.y, 0);
	gPlayer.y = min(gPlayer.y, 23);

	// 콘트롤 키. (미사일 키)
	if (GetAsyncKeyState(VK_CONTROL))
	{
		CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
	}

	// ESC 키. (종료)
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		gScene = SceneType::PAUSE;
	}

	return true;
}
