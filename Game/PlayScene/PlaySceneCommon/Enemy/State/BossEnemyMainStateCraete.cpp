/*
�{�X�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateCreate.h"

//�O���錾
#include"EnemyMoveState/EnemyMoveStateBase.h"

//�֐��̎g�p
#include"../Enemy.h"
#include "../BossEnemy.h"
#include "../SubordinateEnemy.h"


//��]���x
const float BossEnemyMainStateCreate::ROTATION_VELOCITY = 3.f;

//�z���\�ԍ�
const int BossEnemyMainStateCreate::ARRAY_REPRESENTATIVE_NUM = 0;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
BossEnemyMainStateCreate::BossEnemyMainStateCreate()
	:EnemyMainStateBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMainStateCreate::~BossEnemyMainStateCreate()
{
}

/*===================================
����������
�����F�ʏ�G�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateCreate::Initialize(IEnemy* pEnemy)
{
	//�|�C���^��ۑ�
	EnemyMainStateBase::SetEnemy(pEnemy);
}

/*==================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateCreate::Update()
{
	//��]������
	float angle = EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle + ROTATION_VELOCITY);

	//�Z�k��(��\����0�Ԃ̓��e���g�p)
	SubordinateEnemy* enemy = this->GetSubordinateEnemyAddress();
	if (enemy == nullptr)return;

	//��ԕύX����
	if (enemy->GetState() == SubordinateEnemyMainState::MOVE)
	{
		EnemyMainStateBase::GetEnemy()->ChangeStateMove();
		dynamic_cast<BossEnemy*>(EnemyMainStateBase::GetEnemy())->GetStateMove()->ChangeStateWalk();
	}
}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateCreate::Draw()
{
	//���f���̕`��
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�z���G�̃|�C���^
===================================*/
SubordinateEnemy* BossEnemyMainStateCreate::GetSubordinateEnemyAddress()
{
	//�ȗ���
	BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(EnemyMainStateBase::GetEnemy());

	for (int i = 0; i < static_cast<int>(bossEnemy->GetSaveSubordinateEnemy().size()); i++)
	{
		//���e�������Ă�����
		if (bossEnemy->GetSaveSubordinateEnemy().at(i) != nullptr)
		{
			return bossEnemy->GetSaveSubordinateEnemy().at(i);
		}
	}
	return nullptr;
}
