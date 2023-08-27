#pragma once

#define MAX_GRAPHIC_SIZE 3


struct MovementInfo
{
	int32	size;		///< 한 주기의 움직임의 총 횟수
	int32	dy[100];	///< y좌표 변화량
	int32	dx[100];	///< x좌표 변화량
};


///////////////////////////////////////////////////////////////////////////////////
/// enemy 데이터파일을 정의할때는 반드시 다음 순서대로 작성해야함.\n
///
/// 1.그래픽 - 최대 지원 크기는 세로 3 x 가로 5까지 지원. '-'을 공백으로 인식함\n
/// 2.체력\n
/// 3.공격속도 - 공격속도를 n이라 하면 n프레임마다 총알을 시전함.\n
/// 4.총알속도 - 공격속도와 동일\n
/// 5.이동패턴 - movement폴더에 저장된 움직임 데이터 ID\n
/// 6.이동속도 - 공격속도와 동일\n
/// 7.이동거리 - movement파일은 모두 한칸씩만 움직이도록 정의되어있음. 실제 이동패턴은 이동거리 x movement파일\n
/// 8.총알발사되는 상대 x좌표 총알의 방향 (0: 왼쪽 대각선, 1: 가운대, 2: 오른쪽 대각선) 최대 3개까지 추가가능\n
///
///////////////////////////////////////////////////////////////////////////////////
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