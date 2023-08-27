#include "stdafx.h"
#include "Scene.h"
#include "Render.h"

SceneType gScene = SceneType::START;
Cursor gCursor;
int32 gStageLevel = 0;



void InitCursor()
{
	gCursor = { 8, 4 };
}

void DrawCursor()
{
	DrawSprite(gCursor.x, gCursor.y, '>');
}

void DrawStartScene()
{
	static const char* title = "Shooting!";
	static const char* menuStartGame = "New Game";
	static const char* menuExit = "Exit";

	DrawString(4, 6, title);
	DrawString(8, 6, menuStartGame);
	DrawString(10, 6, menuExit);
}

void DrawPauseScene()
{
	static const char* title = "Pause";
	static const char* menuContinue = "Continue";
	static const char* menuGoToStart = "Go to start menu";

	DrawString(4, 6, title);
	DrawString(8, 6, menuContinue);
	DrawString(10, 6, menuGoToStart);
}

void DrawGameOverScene()
{
	static const char* title = "Game Over!";
	static const char* menuGoToStart = "Go to start menu";

	DrawString(4, 6, title);
	DrawString(8, 6, menuGoToStart);
}

void DrawGameClearScene()
{
	static const char* title = "Game Clear!";
	static const char* menuGoToStart = "Go to start menu";

	DrawString(4, 6, title);
	DrawString(8, 6, menuGoToStart);
}
