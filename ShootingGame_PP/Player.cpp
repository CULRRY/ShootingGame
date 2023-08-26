#include "stdafx.h"
#include "Player.h"

#include "Render.h"
#include "Bullet.h"

Player gPlayer;

void InitPlayer()
{
	gPlayer.hp = 3;
	gPlayer.iVisible = true;

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

//--------------------------------------------------------------------
// Ű�����Է��� �޾Ƽ� �÷��̾ ó���Ѵ�.
//
// ESC �� ���� ��� false ����, (����ó��)
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// ��ũ�� ���ۿ� �÷��̾� �׸���
//--------------------------------------------------------------------
void DrawPlayer(void)
{
	if (gPlayer.iVisible)
		Sprite_Draw(gPlayer.x, gPlayer.y, '#');

}