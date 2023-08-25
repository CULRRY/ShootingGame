#include "stdafx.h"
#include "Player.h"

#include "Render.h"
#include "Bullet.h"

Player gPlayer;

//--------------------------------------------------------------------
// 키보드입력을 받아서 플레이어를 처리한다.
//
// ESC 를 누를 경우 false 리턴, (종료처리)
//--------------------------------------------------------------------
bool KeyProcess(void)
{
	// 왼쪽 방향키.
	if (GetAsyncKeyState(VK_LEFT))
	{
		gPlayer.x -= 1;
	}
	// 오른쪽 방향키.
	if (GetAsyncKeyState(VK_RIGHT))
	{
		gPlayer.x += 1;
	}
	// 위쪽 방향키.
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		gPlayer.y--;
	}
	// 아래쪽 방향키.
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		gPlayer.y++;
	}

	//-------------------------------------------------------------
	// 플레이어 이동 반경 제한.
	// 게임 화면에서 플레이어가 이동 가능한 구역을 제한한다.
	//-------------------------------------------------------------

	gPlayer.x = max(gPlayer.x, 0);
	gPlayer.x = min(gPlayer.x, 79);
	gPlayer.y = max(gPlayer.y, 0);
	gPlayer.y = min(gPlayer.y, 23);







	// 콘트롤 키. (미사일 키)
	if (GetAsyncKeyState(VK_CONTROL))
	{
		CreateBullet(BulletType::PLAYER, gPlayer.y, gPlayer.x, 1);
	}

	// ESC 키. (종료)
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		// 종료 방법
	}

	return true;
}

//--------------------------------------------------------------------
// 스크린 버퍼에 플레이어 그리기
//--------------------------------------------------------------------
void Draw_Player(void)
{
	if (gPlayer.iVisible)
		Sprite_Draw(gPlayer.x, gPlayer.y, '#');

}