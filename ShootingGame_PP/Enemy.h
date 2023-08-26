#pragma once

constexpr int32 MAX_ENEMY_CAPACITY = 30;

struct Enemy
{
	bool isUse;				///< 배열에서 현재 해당 칸이 사용 중인지에 대한 플래그

	int32 id;				///< 적군의 enemyInfo에서의 ID

	int32 hp;				///< 적군의 체력

	int32 y;				///< y좌표
	int32 x;				///< x좌표

	int32 movementCount;	///< 이동 패턴을 구현하기 위해 계산되는 카운트
	int32 frameCount;		/// 공격속도를 위해 계산되는 생성이후로 진행된 프레임 수
};

//-------------------------------------------------------------------
/// @brief 전역으로 관리되는 Enemy 배열을 초기화한다.
//-------------------------------------------------------------------
void InitEnemy();

//-------------------------------------------------------------------
/// @brief Enemy의 로직(이동, 피격)을 업데이트한다.
//-------------------------------------------------------------------
void UpdateEnemy();

//-------------------------------------------------------------------
/// @brief Enemy를 삭제한다.
/// @param idx 삭제할 Enemy의 gEnemyArray에서의 인덱스
//-------------------------------------------------------------------
void DeleteEnemy(const int32 idx);

//-------------------------------------------------------------------
/// @brief Enemy를 생성한다.
/// @param enemyId 추가할 적군의 ID
/// @param y 생성할 y좌표
/// @param x 생성할 x좌표
//-------------------------------------------------------------------
void CreateEnemy(const int32 enemyId, const int32 y, const int32 x);

//-------------------------------------------------------------------
/// @brief Enemy를 버퍼에 그린다.
//-------------------------------------------------------------------
void DrawEnemy();


