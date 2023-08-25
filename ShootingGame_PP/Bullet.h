#pragma once

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
	uint8		speed;			///< �Ѿ��� �ӵ� (������Ʈ�Ǵ� ������ ����)
	uint8		frameCount;		///< �ӵ��� ����ϱ� ���� �������� ī���� �Ѵ�.
};

extern Bullet gBulletArray[MAX_BULLET_CAPACITY];

/// @brief �������� �����Ǵ� �Ѿ˵��� ������ ���� Linked-List�� �ʱ�ȭ �Ѵ�.
void InitBulletList();

/// @brief �Ѿ� ����Ʈ�� ��ȸ�ϸ� �Ѿ��� ���� ������ ������Ʈ�Ѵ�.
void UpdateBullet();

/// @brief �Ѿ� ����Ʈ���� �ش� �Ѿ��� �����Ѵ�.
/// @param node �����ϰ����ϴ� �Ѿ��� ������
void DeleteBullet(Bullet* node);

/// @brief �Ѿ��� �����Ͽ� ����Ʈ�� �߰��Ѵ�. ����Ʈ�� �ǵڿ� �߰��ȴ�.
/// @param type �Ѿ��� Type(ENEMY, PLAYER)
/// @param y �Ѿ��� y��ǥ
/// @param x �Ѿ��� x��ǥ
void CreateBullet(const BulletType type, const int32 y, const int32 x);