#pragma once


struct Player
{
	int32 hp;				///< 플레이어 HP

	int32 x;				///< 플레이어 x좌표
	int32 y;				///< 플레이어 y좌표

	int32 moveSpeed;		///< 이동 속도
	int32 attackFrequency;	///< 공격 속도
	int32 bulletSpeed;		///< 총알속도

};

extern Player gPlayer;


//-------------------------------------------------------------------
/// @brief 플레이어의 초기 정보를 세팅한다.
//-------------------------------------------------------------------
void InitPlayer();

//-------------------------------------------------------------------
/// @brief 플레이어의 관련된 로직을 처리한다.(피격 판정)
//-------------------------------------------------------------------
void UpdatePlayer();

//-------------------------------------------------------------------
/// @brief 플레이어를 버퍼에 그린다.
//-------------------------------------------------------------------
void DrawPlayer();