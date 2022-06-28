/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateEscape.h"
#include"../BossEnemyMainStateMove.h"

#include"../../BossEnemy.h"

//�ړ����x
const float BossEnemyMoveStateEscape::ENEMY_ESCAPE_SPEED = -0.25f;

//�v���C���[�Ƃ̑��苗��
const float BossEnemyMoveStateEscape::PLAYER_DISTANCE = 6.f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMoveStateEscape::BossEnemyMoveStateEscape()
	:
	BossEnemyMoveStateBase()
	//()
{
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMoveStateEscape::~BossEnemyMoveStateEscape()
{

}

/*===================================
����������
�����F�G�̃|�C���^�A�{�X�G�̍s��State
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMoveStateEscape::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
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
void BossEnemyMoveStateEscape::SetAngle()
{
	//�������Z�o
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//�Ȃ��p�����f���̊p�x�ɂ���
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}

/*===================================
������Ԑ�p�X�V����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMoveStateEscape::EscapeUpdate()
{
	//�v���C���[�Ƃ̒������������߂�
	DirectX::SimpleMath::Vector3 playerPosition =
		*BossEnemyMoveStateBase::GetMoveState()->GetSavePlayerPointer();

	DirectX::SimpleMath::Vector3 enemyPosition =
		BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->GetPosition();

	float distance{ 0.f };
	//�������v������
	distance = std::sqrtf((std::abs(playerPosition.x - enemyPosition.x)) * 2 +
		(std::abs(playerPosition.z - enemyPosition.z)) * 2);

	//�w��̋������ꂽ��
	//��苗���ɂ��炸�A�ǂ�������ԂȂ�
	if (distance > PLAYER_DISTANCE)
	{
		//������Ԃɂ���
		BossEnemyMoveStateBase::GetMoveState()->ChangeStateWalk();
		dynamic_cast<BossEnemy*>(BossEnemyMoveStateBase::GetBossEnemy())->ChangeStateCreate();
	}
}

/*===================================
�ړ����x�ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�ړ��x�N�g��
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMoveStateEscape::GetMoveVelocity()
{

	//�ړ��x�N�g���擾
	DirectX::SimpleMath::Vector3 moveVelocity =
		BossEnemyMoveStateBase::GetMoveState()->CreateMoveVector(ENEMY_ESCAPE_SPEED);

	return moveVelocity;
}

