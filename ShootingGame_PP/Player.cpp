#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Bullet.h"

Player gPlayer;

void InitPlayer()
{
	gPlayer.hp = 3;

	gPlayer.x = 39;
	gPlayer.y = 19;
}

void UpdatePlayer()
{
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