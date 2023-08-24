#pragma once

/// @brief 총알을 발사한 주체를 구분하는 열거형
enum class BulletType
{
	PLAYER,
	ENEMY,
};

struct Bullet
{
	BulletType type;	///< 총알을 발사한 주체

	int32		y;		///< 총알의 ㅛ좌표
	int32		x;		///< 총알의 x좌표

	Bullet*		prev;	///< 총알 리스트에서 이전 총알의 메모리 위치
	Bullet*		next;	///< 총알 리스트에서 다음 총알의 메모리 위치
};

extern Bullet* gBulletListHead;
extern Bullet* gBulletListTail;


/// @brief 전역으로 관리되는 총알들의 정보를 담은 Linked-List를 초기화 한다.
void InitBulletList();

/// @brief 총알 리스트를 순회하며 총알의 대한 정보를 업데이트한다.
void UpdateBullet();

/// @brief 총알 리스트에서 해당 총알을 삭제한다.
/// @param node 삭제하고자하는 총알의 포인터
void DeleteBullet(Bullet* node);

/// @brief 총알을 생성하여 리스트에 추가한다. 리스트의 맨뒤에 추가된다.
/// @param type 총알의 Type(ENEMY, PLAYER)
/// @param y 총알의 y좌표
/// @param x 총알의 x좌표
void CreateBullet(const BulletType type, const int32 y, const int32 x);