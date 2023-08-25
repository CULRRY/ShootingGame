#pragma once

struct Enemy
{
	bool isUse;

	int32 hp;

	int32 y;
	int32 x;

	uint8 attackFrequency;
	uint8 bulletSpeed;
	uint8 frameCount;
};