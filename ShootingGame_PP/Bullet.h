#pragma once

/// @brief �Ѿ��� �߻��� ��ü�� �����ϴ� ������
enum class BulletType
{
	PLAYER,
	ENEMY,
};

struct Bullet
{
	BulletType type;	///< �Ѿ��� �߻��� ��ü

	int32		y;		///< �Ѿ��� ����ǥ
	int32		x;		///< �Ѿ��� x��ǥ

	Bullet*		prev;	///< �Ѿ� ����Ʈ���� ���� �Ѿ��� �޸� ��ġ
	Bullet*		next;	///< �Ѿ� ����Ʈ���� ���� �Ѿ��� �޸� ��ġ
};

extern Bullet* gBulletListHead;
extern Bullet* gBulletListTail;


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