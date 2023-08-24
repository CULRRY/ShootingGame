#pragma once

/// @brief �Ѿ��� Ÿ���� �����ϴ� ������
enum class BulletType
{
	PLAYER,
	ENEMY,
};

struct Bullet
{
	BulletType	type;

	int32		y;
	int32		x;

	Bullet*		prev;
	Bullet*		next;
};

extern Bullet* gBulletListHead;
extern Bullet* gBulletListTail;

void InitBulletList();
void UpdateBullet();
void DeleteBulletNode(Bullet* node);
void PushBackBulletNode(const BulletType type, const int32 y, const int32 x);