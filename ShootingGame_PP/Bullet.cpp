#include "stdafx.h"
#include "Bullet.h"
#include "FreeQueue.h"
#include "Render.h"


static Bullet gBulletArray[MAX_BULLET_CAPACITY];
static FreeQueue gFreeBulletQueue;
int32 gBulletPosition[dfSCREEN_HEIGHT][dfSCREEN_WIDTH][2];

void InitBulletArray()
{
	InitFreeQueue(gFreeBulletQueue, MAX_BULLET_CAPACITY);

	// FreeQueue�� �Ѿ� �迭�� ��� �ε����� �־���´�.
	for (int32 i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		Push(gFreeBulletQueue, i);
	}
}

void ResetBulletArray()
{
	for (int32 i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		if (gBulletArray[i].isUse == false)
		{
			continue;
		}

		DeleteBullet(i);
	}
}

void ResetBulletPosition()
{
	for (int32 y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		for (int32 x = 0; x < dfSCREEN_WIDTH; x++)
		{
			for (int32 type = 0; type < 2; type++)
			{
				gBulletPosition[y][x][type] = -1;
			}
		}
	}
}

void UpdateBullet()
{
	for (int32 idx = 0; idx < MAX_BULLET_CAPACITY; idx++)
	{
		if (gBulletArray[idx].isUse == false)
		{
			continue;
		}

		gBulletArray[idx].frameCount = (gBulletArray[idx].frameCount + 1) % FRAME;

		// �Ѿ��� �ӵ� ó��
		if (gBulletArray[idx].frameCount % gBulletArray[idx].speed != 0)
		{
			continue;
		}

		// �Ѿ��� ��ġ ������Ʈ
		switch (gBulletArray[idx].type)
		{
		case BulletType::PLAYER:
			gBulletArray[idx].y--;
			break;

		case BulletType::ENEMY:
			if (gBulletArray[idx].direction == BulletDirection::CENTER)
			{
				gBulletArray[idx].y++;
			}

			if (gBulletArray[idx].direction == BulletDirection::LEFT)
			{
				gBulletArray[idx].y++;
				gBulletArray[idx].x--;
			}

			if (gBulletArray[idx].direction == BulletDirection::RIGHT)
			{
				gBulletArray[idx].y++;
				gBulletArray[idx].x++;
			}
			break;
		}

		// �Ѿ��� ���� �Ѿ�� ����
		if (gBulletArray[idx].y < 0 || gBulletArray[idx].y >= dfSCREEN_HEIGHT 
			|| gBulletArray[idx].x < 0 || gBulletArray[idx].x >= dfSCREEN_WIDTH)
		{
			DeleteBullet(idx);
		}
		else
		{
			gBulletPosition[gBulletArray[idx].y][gBulletArray[idx].x][(int32)gBulletArray[idx].type] = idx;
		}
	}

}

void DeleteBullet(int32 idx)
{
	gBulletArray[idx].isUse = false;
	Push(gFreeBulletQueue, idx);
}

void CreateBullet(const BulletType type, const int32 y, const int32 x, const int32 speed, BulletDirection dir)
{
	const int32 idx = Pop(gFreeBulletQueue);

	// �Ѱ�ġ �ʰ��� ��������
	if (idx == QUEUE_EMPTY)
	{
		return;
	}
	gBulletArray[idx].isUse = true;
	gBulletArray[idx].type = type;
	gBulletArray[idx].direction = dir;
	gBulletArray[idx].y = y;
	gBulletArray[idx].x = x;
	gBulletArray[idx].speed = speed;
	gBulletArray[idx].frameCount = speed;
}


void DrawBullet(void)
{
	for (int32 idx = 0; idx < MAX_BULLET_CAPACITY; idx++)
	{
		if (gBulletArray[idx].isUse == false)
		{
			continue;
		}

		switch (gBulletArray[idx].type)
		{
		case BulletType::PLAYER:
			DrawSprite(gBulletArray[idx].x, gBulletArray[idx].y, '^');
			break;
		case BulletType::ENEMY:
			DrawSprite(gBulletArray[idx].x, gBulletArray[idx].y, '*');
			break;
		}
		
	}
}
