/*
�{�X�G�ړ�State���N���X
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateBase.h"

//�O���錾
#include"../../BossEnemy.h"
#include"../BossEnemyMainStateMove.h"


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMoveStateBase::BossEnemyMoveStateBase()
	:
	mpMoveState(),
	mpEnemy()
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMoveStateBase::~BossEnemyMoveStateBase()
{
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMoveStateBase::Update()
{
	//�ړ��x�N�g���擾
	DirectX::SimpleMath::Vector3 moveVelocity = this->GetMoveVelocity();

	//���̂܂ܐݒ�
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->Move(moveVelocity);

	//�������ߏ���
	this->SetAngle();

	//������Ԑ�p�X�V����
	this->EscapeUpdate();
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMoveStateBase::Draw()
{
	//���f���`��
	mpEnemy->GetEnemyModel()->Draw();

	//�e�̕`��
	BossEnemyMoveStateBase::GetBossEnemy()->GetShadow()->Draw
	(
		BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->GetPosition()
	);

}
