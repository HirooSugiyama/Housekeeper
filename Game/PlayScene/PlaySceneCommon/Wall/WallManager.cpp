/*
��Q���Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include<pch.h>
#include "WallManager.h"


//�O���錾
//�����蔻��p
#include"../Player/Player.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../Enemy/DetectNormalEnemy.h"
#include"../Enemy/DetectSubordinateEnemy.h"
#include"../Enemy/DetectBossEnemy.h"

//�����蔻��œ����{���̂��ߎg�p
#include"../ObjectModel/BoxModel.h"
//�ړ����x�̎擾�Ŏg�p
#include"../ObjectMove.h"

#include"WallConstant.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
WallManager::WallManager()
	:
	mpWall{}
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		mpWall[i] = std::make_unique<Wall>();
	}
}

/*===================================
�f�X�g���N�^
===================================*/
WallManager::~WallManager()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void WallManager::Initialize()
{
	//�ϐ��̐錾
	DirectX::SimpleMath::Vector3 position,scale;

	//����
	position.x = WallConstant::WALL_LEFT_POSITION_X;
	position.y = WallConstant::WALL_LEFT_POSITION_Y;
	position.z = WallConstant::WALL_LEFT_POSITION_Z;

	scale.x = WallConstant::WALL_LEFT_SCALE_X;
	scale.y = WallConstant::WALL_LEFT_SCALE_Y;
	scale.z = WallConstant::WALL_LEFT_SCALE_Z;

	mpWall[static_cast<int>(eWallPosition::LEFT_WALL)]->Initialize(position, scale);

	//�E��
	position.x = WallConstant::WALL_RIGHT_POSITION_X;
	position.y = WallConstant::WALL_RIGHT_POSITION_Y;
	position.z = WallConstant::WALL_RIGHT_POSITION_Z;

	scale.x = WallConstant::WALL_RIGHT_SCALE_X;
	scale.y = WallConstant::WALL_RIGHT_SCALE_Y;
	scale.z = WallConstant::WALL_RIGHT_SCALE_Z;
	mpWall[static_cast<int>(eWallPosition::RIGHT_WALL)]->Initialize(position, scale);

}
/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void WallManager::Draw()
{
	for (int i = 0; i < WALL_MAX_NUM; i++) 
	{
		mpWall[i]->Draw();
	}
}

/*===================================
�G�Ƃ̓����蔻����񂷏���
�����F�G�Ǘ��N���X�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================*/
void WallManager::RoolNormalEnemyChackHit(DetectNormalEnemy* pDetectNormalEnemy)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//�����蔻�����
		pDetectNormalEnemy->ChackHitWallNormalEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}

}
void WallManager::RoolBossEnemyChackHit(DetectBossEnemy* pDetectBossEnemy)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//�����蔻�����
		pDetectBossEnemy->ChackHitWallBossEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}

}
