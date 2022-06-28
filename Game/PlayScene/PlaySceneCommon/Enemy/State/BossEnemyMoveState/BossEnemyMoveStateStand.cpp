/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateStand.h"

//�֐��̎g�p
#include"../../IEnemy.h"
#include"../BossEnemyMainStateMove.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMoveStateStand::BossEnemyMoveStateStand()
	:
	BossEnemyMoveStateBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMoveStateStand::~BossEnemyMoveStateStand()
{
}

/*=============================================
����������
�����F�G�̃|�C���^�A�{�X�G�̍s���p�^�[��
============================================*/
void BossEnemyMoveStateStand::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
{
	//�|�C���^�ۑ�����
	BossEnemyMoveStateBase::SetBossEnemy(pBossEnemy);
	BossEnemyMoveStateBase::SetMoveState(pMoveState);
}

/*===================================
�����ݒ菈��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMoveStateStand::SetAngle()
{
	//�������Z�o
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//�Ȃ��p�����f���̊p�x�ɂ���
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}