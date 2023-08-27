#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Bullet.h"

Player gPlayer;

void InitPlayer()
{
	gPlayer.hp = 5;

	gPlayer.x = 39;
	gPlayer.y = 19;

	gPlayer.frameCount = 0;
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