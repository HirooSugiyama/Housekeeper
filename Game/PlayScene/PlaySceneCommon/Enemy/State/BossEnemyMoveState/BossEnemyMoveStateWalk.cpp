/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateWalk.h"

//�֐��̎g�p
#include"../../IEnemy.h"
#include"../BossEnemyMainStateMove.h"

//�ړ����x
const float BossEnemyMoveStateWalk::ENEMY_WALK_SPEED = 0.03f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMoveStateWalk::BossEnemyMoveStateWalk()
	:
	BossEnemyMoveStateBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMoveStateWalk::~BossEnemyMoveStateWalk()
{
}

/*===================================
����������
�����F�G�̃|�C���^�A�{�X�G�̍s��State
===================================*/
void BossEnemyMoveStateWalk::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
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
void BossEnemyMoveStateWalk::SetAngle()
{
	//�������Z�o
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//�Ȃ��p�����f���̊p�x�ɂ���
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}

/*===================================
�ړ����x�ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�ړ����x�x�N�g��
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMoveStateWalk::GetMoveVelocity()
{
	//�ړ��x�N�g���擾
	DirectX::SimpleMath::Vector3 moveVelocity = 
		BossEnemyMoveStateBase::GetMoveState()->CreateMoveVector(ENEMY_WALK_SPEED);

	return moveVelocity;
}
