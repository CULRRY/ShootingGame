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

	// FreeQueue에 총알 배열의 모든 인덱스를 넣어놓는다.
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		Push(gFreeEnemyQueue, i);
	}
}

void ResetEnemy()
{
	for (int32 i = 0; i < MAX_ENEMY_CAPACITY; i++)
	{
		if (gEnemyArray[i].isUse == false)
		{
			continue;
		}

		DeleteEnemy(i);
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
		const EnemyInfo& enemyInfo = gEnemyInfos[gEnemyArray[i].id];

		// attackFrequency마다 총알 발사
		if (gEnemyArray[i].frameCount % gEnemyInfos[gEnemyArray[i].id].attackFrequency == 0)
		{
			for (int32 bulletIdx = 0; bulletIdx < enemyInfo.BulletCount; bulletIdx++)
			{
				CreateBullet(
					BulletType::ENEMY, 
					gEnemyArray[i].y + 2, 
					gEnemyArray[i].x + enemyInfo.BulletXPosition[bulletIdx], 
					gEnemyInfos[gEnemyArray[i].id].bulletSpeed,
					(BulletDirection)enemyInfo.BulletDirection[bulletIdx]
				);
			}
		}


		const MovementInfo& movement = gEnemyInfos[gEnemyArray[i].id].movement;

		// 위치 업데이트
		if (gEnemyArray[i].frameCount % gEnemyInfos[gEnemyArray[i].id].moveSpeed == 0)
		{
			gEnemyArray[i].y += movement.dy[gEnemyArray[i].movementCount % movement.size];
			gEnemyArray[i].x += movement.dx[gEnemyArray[i].movementCount % movement.size];

			gEnemyArray[i].x = max(gEnemyArray[i].x, 0);
			gEnemyArray[i].x = min(gEnemyArray[i].x, 79);
			gEnemyArray[i].y = max(gEnemyArray[i].y, 0);
			gEnemyArray[i].y = min(gEnemyArray[i].y, 23);
			gEnemyArray[i].movementCount++;
		}


		// 피격 판정
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

				if (gBulletPosition[y][x][(int32)BulletType::PLAYER] != -1)
				{
					gEnemyArray[i].hp--;
					DeleteBullet(gBulletPosition[y][x][(int32)BulletType::PLAYER]);
				}
			}
		}

		if (gEnemyArray[i].hp <= 0)
		{
			DeleteEnemy(i);
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
	// 한계치 초과시 생성제한
	if (idx == QUEUE_EMPTY)
	{
		return;
	}
	gEnemyArray[idx].isUse = true;
	gEnemyArray[idx].id = enemyId;
	gEnemyArray[idx].hp = gEnemyInfos[enemyId].hp;
	gEnemyArray[idx].y = y;
	gEnemyArray[idx].x = x;
	gEnemyArray[idx].movementCount = 0;
	gEnemyArray[idx].frameCount = 0;
}

int32 GetLeftEnemy()
{
	return MAX_ENEMY_CAPACITY - gFreeEnemyQueue.size;
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
				DrawSprite(x, y, dot);
			}
		}
	}
}
