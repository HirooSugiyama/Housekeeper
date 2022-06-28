/*
�{�X�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateMove.h"

//�O���錾
#include"EnemyMoveState/EnemyMoveStateBase.h"

//�֐��̎g�p
#include"../Enemy.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemyMainStateMove::BossEnemyMainStateMove()
	:
	EnemyMainStateBase(),
	mpState(),
	mState(),
	mpWalk(),
	mpEscape(),
	mpStand()
{
	mpWalk = std::make_unique<BossEnemyMoveStateWalk>();
	mpEscape = std::make_unique<BossEnemyMoveStateEscape>();
	mpStand = std::make_unique<BossEnemyMoveStateStand>();
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemyMainStateMove::~BossEnemyMainStateMove()
{
}

/*===================================
����������
�����F�ʏ�G�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateMove::Initialize(IEnemy* pEnemy)
{
	//�|�C���^��ۑ�
	EnemyMainStateBase::SetEnemy(pEnemy);

	//�e��Ԃ̏���������
	mpWalk->Initialize(pEnemy, this);
	mpEscape->Initialize(pEnemy, this);
	mpStand->Initialize(pEnemy, this);


	//������Ԃ�ݒ�
	this->ChangeStateWalk();
}

/*==================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateMove::Update()
{
	//���݂̏�Ԃ̍X�V����
	mpState->Update();
}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemyMainStateMove::Draw()
{
	//���݂̏�Ԃ̕`�揈��
	mpState->Draw();
}

/*===================================
�������ߏ���
�����F�Ȃ�
�Ԃ�l�F�����x�N�g��
===================================*/
float BossEnemyMainStateMove::CalculationModelAngle()
{
	//���S�_
	DirectX::SimpleMath::Vector3 position = *mpSavePlayerPointer;
	//���S�_���獡�̂���ʒu�̃x�N�g��
	DirectX::SimpleMath::Vector3 vector =
		position - EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetPosition();
	int juge = -1;
	if (vector.z > 0)
	{
		juge = 1;
	}
	//�@���x�N�g��
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;

	//�Ȃ��p
	float angle = std::acosf(vector.Dot(vel) / (vector.Length() * vel.Length()));

	//�ϊ�
	angle = DirectX::XMConvertToDegrees(angle* juge);

	angle += Utility::RIGHT_ANGLE;

	return angle;
}

/*===================================
�ړ��x�N�g����������
�����F���x
�Ԃ�l�F���ۂ̈ړ����x�x�N�g��
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMainStateMove::CreateMoveVector(const float& moveVelocity)
{
	//�ΏۂƂ̋����𑪒�
	DirectX::SimpleMath::Vector3 distance;
	distance = *mpSavePlayerPointer -
		EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	distance.Normalize();		//���K��

	//�X�P�[�����O
	mChaseVelocity.x = distance.x * moveVelocity;
	mChaseVelocity.z = distance.z * moveVelocity;

	return mChaseVelocity;
}