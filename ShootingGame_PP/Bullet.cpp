#include "stdafx.h"
#include "Bullet.h"


Bullet* gBulletListHead = nullptr;
Bullet* gBulletListTail = nullptr;

void InitBulletList()
{
	gBulletListHead = (Bullet*)malloc(sizeof(Bullet));
	gBulletListTail = (Bullet*)malloc(sizeof(Bullet));

	gBulletListHead->prev = nullptr;
	gBulletListHead->next = gBulletListTail;

	gBulletListTail->prev = gBulletListHead;
	gBulletListTail->next = nullptr;

}

void UpdateBullet()
{
	Bullet* curNode = gBulletListHead->next;

	//TODO ������Ʈ ���� ����
	while (curNode != gBulletListTail)
	{
		//TODO BulletType���� �б��Ͽ�, �Ѿ� ��ġ ������Ʈ.
		switch (curNode->type)
		{
		case BulletType::PLAYER:
			curNode->y--;
			break;

		case BulletType::ENEMY:
			curNode->y++;
			break;
		}

		//TODO �Ѿ��� ��ġ�� �� ���� ��� �ش� �Ѿ� ���� ����
		if (curNode->x <= 0 || curNode->x > 78)
		{
			Bullet* tmp = curNode->next;
			DeleteBullet(curNode);
			curNode = tmp;
			continue;
		}

		//TODO �Ѿ��� ��ġ�� �÷��̾ �������� ������ ����ó�� �� ����


		curNode = curNode->next;
	}
}

void DeleteBullet(Bullet* node)
{
	Bullet* prevNode = node->prev;
	Bullet* nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	free(node);
}

void CreateBullet(const BulletType type, const int32 y, const int32 x)
{
	Bullet* addNode = (Bullet*)malloc(sizeof(Bullet));
	addNode->type = type;
	addNode->y = y;
	addNode->x = x;

	Bullet* lastNode = gBulletListTail->prev;

	addNode->prev = lastNode;
	addNode->next = gBulletListTail;
	gBulletListTail->prev = addNode;
	lastNode->next = addNode;
}
