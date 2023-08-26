#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "FreeQueue.h"
#include "Info.h"
#include "Render.h"

static Enemy gEnemyArray[MAX_ENEMY_CAPACITY];
static FreeQueue gFreeEnemyQueue;

void InitEnemy()
{
	InitFreeQueue(gFreeEnemyQueue, MAX_ENEMY_CAPACITY);

	// FreeQueue�� �Ѿ� �迭�� ��� �ε����� �־���´�.
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		Push(gFreeEnemyQueue, i);
	}
}

void UpdateEnemy()
{
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (gEnemyArray[i].isUse == false)
		{
			continue;
		}

		if (gEnemyArray[i].frameCount % gEnemyInfos[gEnemyArray[i].id].attackFrequency == 0)
		{
			CreateBullet(BulletType::ENEMY, gEnemyArray[i].y + 1, gEnemyArray[i].x, gEnemyInfos[gEnemyArray[i].id].bulletSpeed);
		}

		gEnemyArray[i].frameCount = (gEnemyArray[i].frameCount + 1) % FRAME;

		//TODO �� ��ġ ������Ʈ
	}
}

void DeleteEnemy(const int32 idx)
{
	gEnemyArray[idx].isUse = false;
	Push(gFreeEnemyQueue, idx);
}

void CreateEnemy(const Enemy& enemy)
{

}

void DrawEnemy()
{
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (gEnemyArray[i].isUse == false)
		{
			continue;
		}

		Sprite_Draw(gEnemyArray[i].x, gEnemyArray[i].y, 'O');
	}
}
