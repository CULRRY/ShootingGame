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
	// ���� ����Ű.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		gPlayer.y--;
	}
	// �Ʒ��� ����Ű.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		gPlayer.y++;
	}

	//-------------------------------------------------------------
	// �÷��̾� �̵� �ݰ� ����.
	// ���� ȭ�鿡�� �÷��̾ �̵� ������ ������ �����Ѵ�.
	//-------------------------------------------------------------

	gPlayer.x = max(gPlayer.x, 0);
	gPlayer.x = min(gPlayer.x, 79);
	gPlayer.y = max(gPlayer.y, 0);
	gPlayer.y = min(gPlayer.y, 23);

	// ��Ʈ�� Ű. (�̻��� Ű)
	if (GetAsyncKeyState(VK_CONTROL))
	{
		CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
	}

	// ESC Ű. (����)
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		gScene = SceneType::PAUSE;
	}

	return true;
}
