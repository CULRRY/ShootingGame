#include "stdafx.h"
#include "Player.h"

#include "Render.h"
#include "Bullet.h"

Player gPlayer;

//--------------------------------------------------------------------
// Ű�����Է��� �޾Ƽ� �÷��̾ ó���Ѵ�.
//
// ESC �� ���� ��� false ����, (����ó��)
//--------------------------------------------------------------------
bool KeyProcess(void)
{
	// ���� ����Ű.
	if (GetAsyncKeyState(VK_LEFT))
	{
		gPlayer.x -= 1;
	}
	// ������ ����Ű.
	if (GetAsyncKeyState(VK_RIGHT))
	{
		gPlayer.x += 1;
	}
	// ���� ����Ű.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		gPlayer.y--;
	}
	// �Ʒ��� ����Ű.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		gPlayer.y++;
	}

	//-------------------------------------------------------------
	// �÷��̾� �̵� �ݰ� ����.
	// ���� ȭ�鿡�� �÷��̾ �̵� ������ ������ �����Ѵ�.
	//-------------------------------------------------------------

	gPlayer.x = max(gPlayer.x, 0);
	gPlayer.x = min(gPlayer.x, 79);
	gPlayer.y = max(gPlayer.y, 0);
	gPlayer.y = min(gPlayer.y, 23);







	// ��Ʈ�� Ű. (�̻��� Ű)
	if (GetAsyncKeyState(VK_CONTROL))
	{
		CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
	}

	// ESC Ű. (����)
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		// ���� ���
	}

	return true;
}

//--------------------------------------------------------------------
// ��ũ�� ���ۿ� �÷��̾� �׸���
//--------------------------------------------------------------------
void Draw_Player(void)
{
	if (gPlayer.iVisible)
		Sprite_Draw(gPlayer.x, gPlayer.y, '#');

}