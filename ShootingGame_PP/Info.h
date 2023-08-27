#pragma once

#define MAX_GRAPHIC_SIZE 3


struct MovementInfo
{
	int32	size;		///< 한 주기의 움직임의 총 횟수
	int32	dy[100];	///< y좌표 변화량
	int32	dx[100];	///< x좌표 변화량
};

struct EnemyInfo
{
	char			graphic[3][6];		///< 적군의 그래픽 디자인(최대크기 3 x 5)
	int32			hp;					///< 적군의 채력
	int32			attackFrequency;	///< 공격 속도
	int32			bulletSpeed;		///< 총알 속도
	MovementInfo	movement;			///< 이동 패턴
	int32			moveSpeed;			///< 이동 속도
	int32			moveDistance;		///< 이동 거리
	int32			BulletCount;		///< 한번에 발사하는 총알 갯수
	int32			BulletXPosition[3];	///< 총알 발사되는 상대 x좌표(최대 3개)
	int32			BulletDirection[3];	///< 총알의 방향(최대 3개)
};



extern EnemyInfo* gEnemyInfos;
extern MovementInfo* gMovementInfos;
extern char	gStageFileList[100][100];