/*
��Q���Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once



//�萔�̎g�p
#include"WallConstant.h"

//����
#include"Wall.h"

//�����蔻��p
class Player;
class PreparingBlock;
class DetectNormalEnemy;
class DetectSubordinateEnemy;
class DetectBossEnemy;

class WallManager
{
private:

	enum class eWallPosition
	{
		LEFT_WALL,
		RIGHT_WALL,
	};

	//�萔
		//�ǂ̐�
	static const int WALL_MAX_NUM = 2;

	//�ϐ�
		//��
	std::unique_ptr<Wall> mpWall[WALL_MAX_NUM];

public:
	//�֐�
		//�R���X�g���N�^
	WallManager();
	//�f�X�g���N�^
	~WallManager();
	//������
	void Initialize();
	//�`��
	void Draw();

	//�G�Ƃ̓����蔻����񂷏���
	void RoolNormalEnemyChackHit(DetectNormalEnemy* pDetectNormalEnemy);
	void RoolBossEnemyChackHit(DetectBossEnemy* pDetectBossEnemy);

};