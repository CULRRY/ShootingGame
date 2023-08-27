#include "stdafx.h"
#include "Scene.h"

#include "Render.h"

SceneType gScene = SceneType::START;
Cursor gCursor;
int32 gStageLevel = 0;
bool gExit = false;


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
