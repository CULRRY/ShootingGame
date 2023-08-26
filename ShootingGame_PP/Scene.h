#pragma once
enum class SceneType
{
	START,
	STAGE,
	LOAD,
	GAME_OVER,
	PAUSE,
};

extern SceneType gScene;