#pragma once
#include "Console.h"
constexpr int32 MAX_BULLET_CAPACITY = 1000;

/// @brief �Ѿ��� �߻��� ��ü�� �����ϴ� ������
enum class BulletType
{
	PLAYER,
	ENEMY,
};

struct Bullet
{
	bool		isUse;			///< �迭���� ���� �ش� ĭ�� ��� �������� ���� �÷���

	BulletType	type;			///< �Ѿ��� �߻��� ��ü

	int32		y;				///< �Ѿ��� y��ǥ
	int32		x;				///< �Ѿ��� x��ǥ
	int32		speed;			///< �Ѿ��� �ӵ� (������Ʈ�Ǵ� ������ ����)
	int32		frameCount;		///< �ӵ��� ����ϱ� ���� �������� ī���� �Ѵ�.
};

extern int32 gBulletPosition[dfSCREEN_HEIGHT][dfSCREEN_WIDTH][2];

/// @brief �������� �����Ǵ� �Ѿ˵��� ������ ���� �迭�� �ʱ�ȭ �Ѵ�.
void InitBulletArray();

/// @brief ���� �Ѿ��� ��ġ�� ����ִ� �迭�� �����Ѵ�.
void ResetBulletPostion();

/// @brief �Ѿ� �迭�� ��ȸ�ϸ� �Ѿ��� ���� ������ ������Ʈ�Ѵ�.
void UpdateBullet();

/// @brief �Ѿ� �迭���� �ش� �Ѿ��� �����Ѵ�.
/// @param idx �����ϰ����ϴ� �Ѿ��� �ε���
void DeleteBullet(int32 idx);

/// @brief �Ѿ��� �����Ͽ� �迭�� �߰��Ѵ�.
/// @param type �Ѿ��� Type(ENEMY, PLAYER)
/// @param y �Ѿ��� y��ǥ
/// @param x �Ѿ��� x��ǥ
/// @param speed �Ѿ��� �ӵ�
void CreateBullet(const BulletType type, const int32 y, const int32 x, const int32 speed);

/// @brief �Ѿ��� ȭ�鿡 �׸���.
void DrawBullet();

