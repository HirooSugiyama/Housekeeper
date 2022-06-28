/*
�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/07
*/
#include"pch.h"
#include"SubordinateEnemyMainStateMove.h"

//�O���錾
#include"EnemyMoveState/EnemyMoveStateBase.h"
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateBase.h"

//�֐��̎g�p
#include"../IEnemy.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
SubordinateEnemyMainStateMove::SubordinateEnemyMainStateMove()
	:
	EnemyMainStateBase(),
	mpMoveStateBase(),
	mState(),
	mpStand(),
	mpWalk()
{	
	mpStand = std::make_unique<SubordinateEnemyMoveStateStand>();
	mpWalk = std::make_unique<SubordinateEnemyMoveStateWalk>();
}

/*===================================
�f�X�g���N�^
===================================*/
SubordinateEnemyMainStateMove::~SubordinateEnemyMainStateMove()
{
}

/*===================================
����������
�����F�G�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMainStateMove::Initialize(IEnemy* pEnemy)
{
	//�|�C���^�ۑ�
	EnemyMainStateBase::SetEnemy(pEnemy);

	//��Ԃ̏���������
	mpStand->Initialize(pEnemy,this);
	mpWalk->Initialize(pEnemy,this);

	//�ŏ��̏�Ԃ͕��s���
	this->ChangeStateWalk();
}

/*==================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMainStateMove::Update()
{
	//���݂̏�Ԃ̍X�V����
	mpMoveStateBase->Update();
}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMainStateMove::Draw()
{
	//���f���̕`��
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

