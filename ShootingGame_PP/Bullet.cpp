#include "stdafx.h"
#include "Bullet.h"


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

	while (curNode != gBulletListTail)
	{
		// TODO �Ѿ��� ��ġ�� �� ���� ��� �ش� �Ѿ� ���� ����
		if (curNode->x <= 0 || curNode->x > 78)
		{
			Bullet* tmp = curNode->next;
			DeleteBullet(curNode);
			curNode = tmp;
			continue;
		}

		//TODO ������Ʈ ���� ����


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
