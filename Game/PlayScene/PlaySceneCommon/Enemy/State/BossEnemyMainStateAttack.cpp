/*
�{�Xs�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateAttack.h"

//�O���錾
#include"EnemyMoveState/EnemyMoveStateBase.h"

//�֐��̎g�p
#include"../Enemy.h"


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMainStateAttack::BossEnemyMainStateAttack()
	:EnemyMainStateBase()
	, mpEnemyMoveStateBase()
	, mState(EnemyMoveState::WALK)
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMainStateAttack::~BossEnemyMainStateAttack()
{
}

/*===================================
����������
�����F�ʏ�G�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateAttack::Initialize(IEnemy* pEnemy)
{
	//�|�C���^��ۑ�
	EnemyMainStateBase::SetEnemy(pEnemy);
}

/*==================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateAttack::Update()
{

}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateAttack::Draw()
{
	//���f���̕`��
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}
