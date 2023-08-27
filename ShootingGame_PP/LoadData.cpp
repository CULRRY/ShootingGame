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
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, MOVEMENT_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}

	gMovementInfos = (MovementInfo*)malloc(sizeof(MovementInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("���� ���� ����");
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
			CRASH("���� �ݱ� ����");
		}
	}
}

void LoadEnemyData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, ENEMY_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}

	gEnemyInfos = (EnemyInfo*)malloc(sizeof(EnemyInfo) * fileCount);

	for (int32 i = 0; i < fileCount; i++)
	{
		if (::fopen_s(&file, fileList[i], "r") != 0)
		{
			CRASH("���� ���� ����");
		}

		EnemyInfo& info = gEnemyInfos[i];

		// ���� �׷��� �ҷ�����
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

		// ������ ���� �ҷ�����
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

		// �Ѿ� �������� �ҷ�����
		int32 bulletIdx = 0;
		gEnemyInfos[i].BulletCount = 0;
		while (::fscanf_s(file, "%d %d", &gEnemyInfos[i].BulletXPosition[bulletIdx], &gEnemyInfos[i].BulletDirection[bulletIdx]) 
			!= EOF)
		{
			if (bulletIdx > 3)
			{
				CRASH("�Ѿ� ������ 3�� �ʰ���");
			}
			bulletIdx++;
			gEnemyInfos[i].BulletCount++;
		}

		if (bulletIdx == 0)
		{
			CRASH("�Ѿ� ���� ����");
		}

		if (::fclose(file) != 0)
		{
			CRASH("���� �ݱ� ����");
		}
	}
}

void LoadStageList()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, STAGE_LIST_PATH, "r") != 0)
	{
		CRASH("���� ���� ����");
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
		CRASH("���� �ݱ� ����");
	}
}

void LoadStageData()
{
	FILE* file = nullptr;
	// ������ ���� ����Ʈ ����
	if (::fopen_s(&file, gStageFileList[gStageLevel], "r") != 0)
	{
		CRASH("���� ���� ����");
	}

	char stageFileBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {"", };

	// '=' '\n'�ѱ��
	fseek(file, dfSCREEN_WIDTH + 2, SEEK_SET);

	for (int32 y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		fread_s(&stageFileBuffer[y], dfSCREEN_WIDTH, 1, dfSCREEN_WIDTH, file);
		stageFileBuffer[y][dfSCREEN_WIDTH - 1] = 0;
		// '=' '\n'�ѱ��
		fseek(file, 2, SEEK_CUR);
	}

	if (::fclose(file) != 0)
	{
		CRASH("���� �ݱ� ����");
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
