/*
�z���G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/14
*/
#include"pch.h"

#include"SubordinateEnemyMoveStateWalk.h"

//�֐��̎g�p
#include"../../IEnemy.h"
#include"../SubordinateEnemyMainStateMove.h"

//�ړ����x
const float SubordinateEnemyMoveStateWalk::SUBORDINATE_ENEMY_MOVE_VELOCITY = 0.05f;

//���������W��
const int SubordinateEnemyMoveStateWalk::ANGLE_SHIFT = 1;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
SubordinateEnemyMoveStateWalk::SubordinateEnemyMoveStateWalk()
	:
	SubordinateEnemyMoveStateBase(),
	mChaseVelocity(),
	mpSavePlayerPointer()
{
}

/*===================================
�f�X�g���N�^
===================================*/
SubordinateEnemyMoveStateWalk::~SubordinateEnemyMoveStateWalk()
{
}

/*===================================
����������
�����F�G�̃|�C���^�A�G�̍s��State
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateWalk::Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)
{
	//�A�h���X�ۑ�
	SubordinateEnemyMoveStateBase::SetEnemy(pEnemy);
	SubordinateEnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateWalk::Update()
{
	//�ړ�����
	this->Move();

	//�������ߏ���
	this->CalculationModelAngle();
}


/*===================================
�ړ�����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateWalk::Move()
{
	//�ΏۂƂ̋����𑪒�
	DirectX::SimpleMath::Vector3 distance;
	distance = *mpSavePlayerPointer -
		SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	distance.Normalize();		//���K��

	//�X�P�[�����O
	mChaseVelocity.x = distance.x * SUBORDINATE_ENEMY_MOVE_VELOCITY;
	mChaseVelocity.z = distance.z * SUBORDINATE_ENEMY_MOVE_VELOCITY;

	//�ړ�����
	SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->Move(mChaseVelocity);
}

/*===================================
�������ߏ���:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateWalk::CalculationModelAngle()
{
	//���S�_
	DirectX::SimpleMath::Vector3 position = *mpSavePlayerPointer;
	//���S�_���獡�̂���ʒu�̃x�N�g��
	DirectX::SimpleMath::Vector3 vector =
		position - SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	//�@���x�N�g��
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;

	int juge = Utility::EXCEPTION_NUM;
	if (vector.z > 0)
	{
		juge = ANGLE_SHIFT;
	}


	//�Ȃ��p
	float angle = std::acosf(vector.Dot(vel) / (vector.Length() * vel.Length()));

	//�ϊ�
	angle = DirectX::XMConvertToDegrees(angle * juge);

	angle += Utility::RIGHT_ANGLE;

	//�ړ�����
	SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle);
}