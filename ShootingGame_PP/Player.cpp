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

//--------------------------------------------------------------------
// Ű�����Է��� �޾Ƽ� �÷��̾ ó���Ѵ�.
//
// ESC �� ���� ��� false ����, (����ó��)
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// ��ũ�� ���ۿ� �÷��̾� �׸���
//--------------------------------------------------------------------
void Draw_Player(void)
{
	if (gPlayer.iVisible)
		Sprite_Draw(gPlayer.x, gPlayer.y, '#');

}