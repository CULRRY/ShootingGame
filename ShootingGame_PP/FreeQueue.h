#pragma once

constexpr int32 QUEUE_EMPTY = -1;


struct FreeQueue
{
	int32* data;		///< Queue의 데이터가 저장되는 공간

	uint32 head;
	uint32 tail;
	uint32 size;		///< 현재 들어있는 원소의 갯수
	uint32 capacity;	///< 최대 저장 공간
};


void InitFreeQueue(FreeQueue& freeQueue, uint32 capacity);

bool Push(FreeQueue& freeQueue, const int32 index);

int32 Pop(FreeQueue& freeQueue);

