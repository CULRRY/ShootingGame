#include "stdafx.h"
#include "Bullet.h"
#include "FreeQueue.h"
#include "Render.h"


static Bullet gBulletArray[MAX_BULLET_CAPACITY];
static FreeQueue gFreeBulletQueue;


void InitBulletArray()
{
	InitFreeQueue(gFreeBulletQueue, MAX_BULLET_CAPACITY);

	// FreeQueue�� �Ѿ� �迭�� ��� �ε����� �־���´�.
	for (int32 i = 0; i < MAX_BULLET_CAPACITY; i++)
	{
		Push(gFreeBulletQueue, i);
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

		// �Ѿ��� �ӵ� ó��
		if (gBulletArray[idx].frameCount % gBulletArray[idx].speed != 0)
		{
			continue;
		}

		gBulletArray[idx].frameCount = (gBulletArray[idx].frameCount + 1) % FRAME;

		// �Ѿ��� ��ġ ������Ʈ
		switch (gBulletArray[idx].type)
		{
		case BulletType::PLAYER:
			gBulletArray[idx].y--;
			break;

		case BulletType::ENEMY:
			gBulletArray[idx].y++;
			break;
		}

		// �Ѿ��� ���� �Ѿ�� ����
		if (gBulletArray[idx].y < 0 || gBulletArray[idx].y >= dfSCREEN_HEIGHT 
			|| gBulletArray[idx].x < 0 || gBulletArray[idx].x >= dfSCREEN_WIDTH)
		{
			DeleteBullet(idx);
		}
	}

}

void DeleteBullet(int32 idx)
{
	gBulletArray[idx].isUse = false;
	Push(gFreeBulletQueue, idx);
}

void CreateBullet(const BulletType type, const int32 y, const int32 x, const int32 speed)
{
	const int32 idx = Pop(gFreeBulletQueue);

	gBulletArray[idx].isUse = true;
	gBulletArray[idx].type = type;
	gBulletArray[idx].y = y;
	gBulletArray[idx].x = x;
	gBulletArray[idx].speed = speed;
}


void DrawBullet(void)
{
	
	for (int32 idx = 0; idx < MAX_BULLET_CAPACITY; idx++)
	{
		if (gBulletArray[idx].isUse == false)
		{
			continue;
		}

		Sprite_Draw(gBulletArray[idx].x, gBulletArray[idx].y, '^');
	}
}
