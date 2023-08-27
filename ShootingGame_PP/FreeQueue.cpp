#include "stdafx.h"
#include "FreeQueue.h"

void InitFreeQueue(FreeQueue& freeQueue, uint32 capacity)
{
	freeQueue.data = (int32*)malloc(capacity * sizeof(int32));
	freeQueue.head = 0;
	freeQueue.tail = 0;
	freeQueue.size = 0;
	freeQueue.capacity = capacity;
}

bool Push(FreeQueue& freeQueue, const int32 index)
{
	// queue�� ������ ���̻� �߰��� �� ������ false ����
	if (freeQueue.size == freeQueue.capacity)
	{
		return false;
	}

	freeQueue.data[freeQueue.tail] = index;
	freeQueue.tail = (freeQueue.tail + 1) % freeQueue.capacity;
	freeQueue.size++;

	return true;
}

int32 Pop(FreeQueue& freeQueue)
{
	// queue�� ����ִµ� pop�� �ϸ� QUEUE_EMPTY ����.
	if (freeQueue.size == 0)
		return QUEUE_EMPTY;

	const int32 ret = freeQueue.data[freeQueue.head];

	freeQueue.head = (freeQueue.head + 1) % freeQueue.capacity;
	freeQueue.size--;

	return ret;
}
