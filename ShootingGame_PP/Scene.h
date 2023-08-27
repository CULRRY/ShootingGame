#pragma once
enum class SceneType
{
	START,
	STAGE,
	LOAD,
	GAME_OVER,
	GAME_CLEAR,
	PAUSE,
};

struct Position
{
	int32 y;
	int32 x;
};

using Cursor = Position;

extern SceneType gScene;
extern Cursor gCursor;
extern int32 gStageLevel;
extern bool gExit;

//-------------------------------------------------------------------
/// @brief Ŀ�� ��ġ�� �ʱ�ȭ�Ѵ�.
//-------------------------------------------------------------------
void InitCursor();

void DrawCursor();

void DrawStartScene();
