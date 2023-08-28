#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Bullet.h"

Player gPlayer;

void InitPlayer()
{
	gPlayer.hp = 10;

	gPlayer.x = 39;
	gPlayer.y = 19;

	gPlayer.moveSpeed = 3;
	gPlayer.attackFrequency = 6;
	gPlayer.bulletSpeed = 3;
}

void UpdatePlayer()
{
	// 피격판정
	if (gBulletPosition[gPlayer.y][gPlayer.x][(int32)BulletType::ENEMY] != -1)
	{
		gPlayer.hp--;
		DeleteBullet(gBulletPosition[gPlayer.y][gPlayer.x][(int32)BulletType::ENEMY]);
	}
}


void DrawPlayer()
{
	DrawSprite(gPlayer.x, gPlayer.y, '#');
}