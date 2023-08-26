#include "stdafx.h"
#include "LoadData.h"

#include "Info.h"

EnemyInfo* gEnemyInfos = nullptr;
MovementInfo* gMovementInfos = nullptr;
char gStageList[100][100] = { "", };

void LoadMovementData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, MOVEMENT_LIST_PATH, "r") != 0)
	{
		__debugbreak();
	}

	char fileList[100][100] = {"", };

	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/movement/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(fileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		__debugbreak();
	}

	gMovementInfos = (MovementInfo*)malloc(sizeof(MovementInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			__debugbreak();
		}

		MovementInfo& info = gMovementInfos[i];
		int32 movementCount = 0;
		while (::fscanf_s(file, "%d %d", &info.dy[movementCount], &info.dx[movementCount]) != EOF)
		{
			movementCount++;
		}
		info.size = movementCount;

		if (::fclose(file) != 0)
		{
			__debugbreak();
		}
	}
}

void LoadEnemyData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, ENEMY_LIST_PATH, "r") != 0)
	{
		__debugbreak();
	}

	char fileList[100][100] = { "", };

	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/enemy/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(fileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		__debugbreak();
	}

	gEnemyInfos = (EnemyInfo*)malloc(sizeof(EnemyInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			__debugbreak();
		}

		EnemyInfo& info = gEnemyInfos[i];

		for (int32 y = 0; y < MAX_GRAPHIC_SIZE; y++)
		{
			::fscanf_s(file, "%s", info.graphic[y], (uint32)sizeof(info.graphic[y]));
		}

		::fscanf_s(file, "%d", &gEnemyInfos[i].hp);
		::fscanf_s(file, "%d", &gEnemyInfos[i].movementId);
		::fscanf_s(file, "%d", &gEnemyInfos[i].attackFrequency);
		::fscanf_s(file, "%d", &gEnemyInfos[i].bulletSpeed);

		if (::fclose(file) != 0)
		{
			__debugbreak();
		}
	}
}

void LoadStageList()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, STAGE_LIST_PATH, "r") != 0)
	{
		__debugbreak();
	}

	char fileList[100][100] = { "", };

	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/stage/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(fileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		__debugbreak();
	}
}

void LoadStageData()
{
}