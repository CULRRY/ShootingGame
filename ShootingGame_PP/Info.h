#pragma once

#define MAX_GRAPHIC_SIZE 3


struct MovementInfo
{
	int32	size;		///< �� �ֱ��� �������� �� Ƚ��
	int32	dy[100];	///< y��ǥ ��ȭ��
	int32	dx[100];	///< x��ǥ ��ȭ��
};

struct EnemyInfo
{
	char			graphic[3][6];		///< ������ �׷��� ������(�ִ�ũ�� 3 x 5)
	int32			hp;					///< ������ ä��
	int32			attackFrequency;	///< ���� �ӵ�
	int32			bulletSpeed;		///< �Ѿ� �ӵ�
	MovementInfo	movement;			///< �̵� ����
	int32			moveSpeed;			///< �̵� �ӵ�
	int32			moveDistance;		///< �̵� �Ÿ�
	int32			BulletCount;		///< �ѹ��� �߻��ϴ� �Ѿ� ����
	int32			BulletXPosition[3];	///< �Ѿ� �߻�Ǵ� ��� x��ǥ(�ִ� 3��)
	int32			BulletDirection[3];	///< �Ѿ��� ����(�ִ� 3��)
};



extern EnemyInfo* gEnemyInfos;
extern MovementInfo* gMovementInfos;
extern char	gStageFileList[100][100];