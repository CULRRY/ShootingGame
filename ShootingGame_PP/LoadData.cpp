#include "stdafx.h"
#include "Macro.h"
#include "LoadData.h"
#include "Console.h"
#include "Enemy.h"
#include "Info.h"
#include "Scene.h"

void LoadMovementData()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, MOVEMENT_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
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
		CRASH("파일 닫기 에러");
	}

	gMovementInfos = (MovementInfo*)malloc(sizeof(MovementInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("파일 열기 에러");
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
			CRASH("파일 닫기 에러");
		}
	}
}

void LoadEnemyData()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, ENEMY_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
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
		CRASH("파일 닫기 에러");
	}

	gEnemyInfos = (EnemyInfo*)malloc(sizeof(EnemyInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("파일 열기 에러");
		}

		EnemyInfo& info = gEnemyInfos[i];

		// 유닛 그래픽 불러오기
		for (int32 y = 0; y < MAX_GRAPHIC_SIZE; y++)
		{
			::fscanf_s(file, "%s", info.graphic[y], (uint32)sizeof(info.graphic[y]));
		}

		int32 movementId = 0;
		::fscanf_s(file, "%d", &gEnemyInfos[i].hp);
		::fscanf_s(file, "%d", &gEnemyInfos[i].attackFrequency);
		::fscanf_s(file, "%d", &gEnemyInfos[i].bulletSpeed);
		::fscanf_s(file, "%d", &movementId);
		::fscanf_s(file, "%d", &gEnemyInfos[i].moveSpeed);
		::fscanf_s(file, "%d", &gEnemyInfos[i].moveDistance);

		gEnemyInfos[i].movement.size = gMovementInfos[movementId].size * gEnemyInfos[i].moveDistance;

		// 움직임 정보 불러오기
		for (int32 moveInfoIdx = 0; moveInfoIdx < gMovementInfos[movementId].size; moveInfoIdx++)
		{
			for (int32 iter = moveInfoIdx * gEnemyInfos[i].moveDistance; 
				iter < (moveInfoIdx + 1) * gEnemyInfos[i].moveDistance; 
				iter++)
			{
				gEnemyInfos[i].movement.dy[iter] = gMovementInfos[movementId].dy[moveInfoIdx];
				gEnemyInfos[i].movement.dx[iter] = gMovementInfos[movementId].dx[moveInfoIdx];
			}
		}

		// 총알 방향정보 불러오기
		int32 bulletIdx = 0;
		gEnemyInfos[i].BulletCount = 0;
		while (::fscanf_s(file, "%d %d", &gEnemyInfos[i].BulletXPosition[bulletIdx], &gEnemyInfos[i].BulletDirection[bulletIdx]) 
			!= EOF)
		{
			if (bulletIdx > 3)
			{
				CRASH("총알 정보가 3개 초과함");
			}
			bulletIdx++;
			gEnemyInfos[i].BulletCount++;
		}

		if (bulletIdx == 0)
		{
			CRASH("총알 정보 없음");
		}

		if (::fclose(file) != 0)
		{
			CRASH("파일 닫기 에러");
		}
	}
}

void LoadStageList()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, STAGE_LIST_PATH, "r") != 0)
	{
		CRASH("파일 열기 에러");
	}


	int32 fileCount = 0;
	char fileName[100] = "";

	while (::fscanf_s(file, "%s", &fileName, (uint32)sizeof(fileName)) != EOF)
	{
		char path[100] = "data/stage/";
		::strcat_s(path, sizeof(path), fileName);
		::strcpy_s(gStageFileList[fileCount], sizeof(path), path);
		fileCount++;
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}
}

void LoadStageData()
{
	FILE* file = nullptr;
	// 데이터 파일 리스트 오픈
	if (::fopen_s(&file, gStageFileList[gStageLevel], "r") != 0)
	{
		CRASH("파일 열기 에러");
	}

	char stageFileBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {"", };

	// '=' '\n'넘기기
	fseek(file, dfSCREEN_WIDTH + 2, SEEK_SET);

	for (int32 y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		fread_s(&stageFileBuffer[y], dfSCREEN_WIDTH, 1, dfSCREEN_WIDTH, file);
		stageFileBuffer[y][dfSCREEN_WIDTH - 1] = 0;
		// '=' '\n'넘기기
		fseek(file, 2, SEEK_CUR);
	}

	if (::fclose(file) != 0)
	{
		CRASH("파일 닫기 에러");
	}

	for (int32 y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		for (int32 x = 0; x < dfSCREEN_WIDTH; x++)
		{
			if (stageFileBuffer[y][x] == ' ' || stageFileBuffer[y][x] == 0)
			{
				continue;
			}

			CreateEnemy(stageFileBuffer[y][x] - '0', y, x);
		}
	}
}
