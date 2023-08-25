#pragma once

constexpr int32 QUEUE_EMPTY = -1;


struct FreeQueue
{
	int32* data;

	uint32 head;
	uint32 tail;
	uint32 size;
	uint32 capacity;
};


void InitFreeQueue(FreeQueue& freeQueue, uint32 capacity);

bool Push(FreeQueue& freeQueue, const int32 index);

int32 Pop(FreeQueue& freeQueue);

