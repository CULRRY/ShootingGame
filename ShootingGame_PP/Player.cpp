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
// 키보드입력을 받아서 플레이어를 처리한다.
//
// ESC 를 누를 경우 false 리턴, (종료처리)
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// 스크린 버퍼에 플레이어 그리기
//--------------------------------------------------------------------
void Draw_Player(void)
{
	if (gPlayer.iVisible)
		Sprite_Draw(gPlayer.x, gPlayer.y, '#');

}