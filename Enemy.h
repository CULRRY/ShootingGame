#pragma once

constexpr int32 MAX_ENEMY_CAPACITY = 30;

struct Enemy
{
	bool isUse;					///< �迭���� ���� �ش� ĭ�� ��� �������� ���� �÷���

	int32 id;					///< ������ enemyInfo������ ID

	int32 hp;					///< ������ ü��

	int32 y;					///< y��ǥ
	int32 x;					///< x��ǥ

	int32 movementCount;		///< �̵� ������ �����ϱ� ���� ���Ǵ� ī��Ʈ
	int32 frameCount;			///< ���ݼӵ��� ���� ���Ǵ� �������ķ� ����� ������ ��
};

//-------------------------------------------------------------------
/// @brief �������� �����Ǵ� Enemy �迭�� �ʱ�ȭ�Ѵ�.
//-------------------------------------------------------------------
void InitEnemy();

//-------------------------------------------------------------------
/// @brief ���� Enemy �迭�� ����.
//-------------------------------------------------------------------
void ResetEnemy();

//-------------------------------------------------------------------
/// @brief Enemy�� ����(�̵�, �ǰ�)�� ������Ʈ�Ѵ�.
//-------------------------------------------------------------------
void UpdateEnemy();

//-------------------------------------------------------------------
/// @brief Enemy�� �����Ѵ�.
///
/// @param idx ������ Enemy�� gEnemyArray������ �ε���
//-------------------------------------------------------------------
void DeleteEnemy(const int32 idx);

//-------------------------------------------------------------------
/// @brief Enemy�� �����Ѵ�.
///
/// @param enemyId �߰��� ������ ID
/// @param y ������ y��ǥ
/// @param x ������ x��ǥ
//-------------------------------------------------------------------
void CreateEnemy(const int32 enemyId, const int32 y, const int32 x);

//-------------------------------------------------------------------
/// @brief ���� ���������� ���� ���� ���� ��ȯ�Ѵ�.
///
/// @return ���� ���������� ���� ���� ��
//-------------------------------------------------------------------
int32 GetLeftEnemy();

//-------------------------------------------------------------------
/// @brief Enemy�� ���ۿ� �׸���.
//-------------------------------------------------------------------
void DrawEnemy();

