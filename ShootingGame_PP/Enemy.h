#pragma once

constexpr int32 MAX_ENEMY_CAPACITY = 30;

struct Enemy
{
	bool isUse;

	int32 id;

	int32 hp;

	int32 y;
	int32 x;

	int32 movementCount;
	int32 frameCount;
};


void InitEnemy();

void UpdateEnemy();

void DeleteEnemy(const int32 idx);

void CreateEnemy(const int32 enemyId, const int32 y, const int32 x);

void DrawEnemy();


