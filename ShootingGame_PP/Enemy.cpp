#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "FreeQueue.h"
#include "Info.h"
#include "Render.h"
#include "UnitPosition.h"

Enemy gEnemyArray[MAX_ENEMY_CAPACITY];
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

		gEnemyArray[i].frameCount++;

		if (gEnemyArray[i].frameCount % gEnemyInfos[gEnemyArray[i].id].attackFrequency == 0)
		{
			CreateBullet(BulletType::ENEMY, gEnemyArray[i].y + 2, gEnemyArray[i].x, gEnemyInfos[gEnemyArray[i].id].bulletSpeed);
		}


		const MovementInfo& movement = gMovementInfos[gEnemyInfos[gEnemyArray[i].id].movementId];
		//TODO �� ��ġ ������Ʈ
		gEnemyArray[i].y += movement.dy[gEnemyArray[i].movementCount % movement.size];
		gEnemyArray[i].x += movement.dx[gEnemyArray[i].movementCount % movement.size];

		gEnemyArray[i].x = max(gEnemyArray[i].x, 0);
		gEnemyArray[i].x = min(gEnemyArray[i].x, 79);
		gEnemyArray[i].y = max(gEnemyArray[i].y, 0);
		gEnemyArray[i].y = min(gEnemyArray[i].y, 23);
		gEnemyArray[i].movementCount++;

		for (int32 y = gEnemyArray[i].y - 1; y <= gEnemyArray[i].y + 1; y++)
		{
			for (int32 x = gEnemyArray[i].x - 2; x <= gEnemyArray[i].x + 2; x++)
			{
				if (y < 0 || y >= dfSCREEN_HEIGHT || x < 0 || x >= dfSCREEN_WIDTH)
				{
					continue;
				}

				
			}
		}
	}
}

void DeleteEnemy(const int32 idx)
{
	gEnemyArray[idx].isUse = false;
	Push(gFreeEnemyQueue, idx);
}

void CreateEnemy(const int32 enemyId, const int32 y, const int32 x)
{
	const int32 idx = Pop(gFreeEnemyQueue);

	gEnemyArray[idx].isUse = true;
	gEnemyArray[idx].id = enemyId;
	gEnemyArray[idx].hp = gEnemyInfos[enemyId].hp;
	gEnemyArray[idx].y = y;
	gEnemyArray[idx].x = x;
	gEnemyArray[idx].movementCount = 0;
	gEnemyArray[idx].frameCount = 0;
}

void DrawEnemy()
{
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (gEnemyArray[i].isUse == false)
		{
			continue;
		}

		const EnemyInfo& enemyInfo = gEnemyInfos[gEnemyArray[i].id];
		for (int32 y = gEnemyArray[i].y - 1; y <= gEnemyArray[i].y + 1; y++)
		{
			for (int32 x = gEnemyArray[i].x - 2; x <= gEnemyArray[i].x + 2; x++)
			{
				if (y < 0 || y >= dfSCREEN_HEIGHT || x < 0 || x >= dfSCREEN_WIDTH)
				{
					continue;
				}

				const char dot = enemyInfo.graphic[y - (gEnemyArray[i].y - 1)][x - (gEnemyArray[i].x - 2)];

				if (dot == '-')
				{
					continue;
				}
				Sprite_Draw(x, y, dot);
			}
		}
	}
}
