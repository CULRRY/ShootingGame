#pragma once

#define MAX_GRAPHIC_SIZE 3

struct EnemyInfo
{
	char		graphic[3][6];
	int32		hp;
	int32		movementId;
	int32		attackFrequency;
	int32		bulletSpeed;
};

struct MovementInfo
{
	int32	size;
	int32	dy[100];
	int32	dx[100];
};

extern EnemyInfo* gEnemyInfos;
extern MovementInfo* gMovementInfos;
extern char	gStageFileList[100][100];