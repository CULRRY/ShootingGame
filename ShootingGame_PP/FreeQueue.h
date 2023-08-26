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

//--------------------------------------------------------------------
/// @brief FreeQueue를 초기화한다.
///
/// @param freeQueue 초기화할 FreeQueue 구조체
/// @param capacity 최대 수용량
//--------------------------------------------------------------------
void InitFreeQueue(FreeQueue& freeQueue, uint32 capacity);

//--------------------------------------------------------------------
/// @brief FreeQueue에 인덱스를 집어넣는다.
///
/// @param freeQueue 집어넣을 FreeQueue 구조체
/// @param index 집어넣을 인덱스
/// @return queue가 꽉차있을 경우 false 반환
//--------------------------------------------------------------------
bool Push(FreeQueue& freeQueue, const int32 index);

//--------------------------------------------------------------------
/// @brief FreeQueue에서 빈 인덱스를 받아온다.
///
/// @param freeQueue 받아올 FreeQueue 구조체
/// @return queue가 비어있을 경우 -1(QUEUE_EMPTY) 리턴\n
///			정상적인 경우 큐의 제일 앞에있는 값 반환
//--------------------------------------------------------------------
int32 Pop(FreeQueue& freeQueue);

