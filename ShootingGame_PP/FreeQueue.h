#pragma once

constexpr int32 QUEUE_EMPTY = -1;


struct FreeQueue
{
	int32* data;		///< Queue�� �����Ͱ� ����Ǵ� ����

	uint32 head;
	uint32 tail;
	uint32 size;		///< ���� ����ִ� ������ ����
	uint32 capacity;	///< �ִ� ���� ����
};

//--------------------------------------------------------------------
/// @brief FreeQueue�� �ʱ�ȭ�Ѵ�.
///
/// @param freeQueue �ʱ�ȭ�� FreeQueue ����ü
/// @param capacity �ִ� ���뷮
//--------------------------------------------------------------------
void InitFreeQueue(FreeQueue& freeQueue, uint32 capacity);

//--------------------------------------------------------------------
/// @brief FreeQueue�� �ε����� ����ִ´�.
///
/// @param freeQueue ������� FreeQueue ����ü
/// @param index ������� �ε���
/// @return queue�� �������� ��� false ��ȯ
//--------------------------------------------------------------------
bool Push(FreeQueue& freeQueue, const int32 index);

//--------------------------------------------------------------------
/// @brief FreeQueue���� �� �ε����� �޾ƿ´�.
///
/// @param freeQueue �޾ƿ� FreeQueue ����ü
/// @return queue�� ������� ��� -1(QUEUE_EMPTY) ����\n
///			�������� ��� ť�� ���� �տ��ִ� �� ��ȯ
//--------------------------------------------------------------------
int32 Pop(FreeQueue& freeQueue);

