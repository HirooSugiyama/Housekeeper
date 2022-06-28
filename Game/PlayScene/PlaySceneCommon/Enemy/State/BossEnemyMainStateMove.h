/*
�{�X�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"EnemyMainStateBase.h"

//��ԕ���
#include"BossEnemyMoveState/BossEnemyMoveStateWalk.h"
#include"BossEnemyMoveState/BossEnemyMoveStateEscape.h"
#include"BossEnemyMoveState/BossEnemyMoveStateStand.h"

//�񋓌^�̎g�p
#include"BossEnemyState.h"


//�O���錾
class BossEnemyMoveStateBase;	//���State

class BossEnemyMainStateMove : public EnemyMainStateBase
{
private:

	//���݂̏��
	BossEnemyMoveStateBase* mpState;
	BossEnemyMoveState mState;

	//��ԕ���
	std::unique_ptr<BossEnemyMoveStateWalk> mpWalk;
	std::unique_ptr<BossEnemyMoveStateEscape> mpEscape;
	std::unique_ptr<BossEnemyMoveStateStand> mpStand;

	//�ǂ������p�ړ����x�ۑ��ϐ�
	DirectX::SimpleMath::Vector3 mChaseVelocity;

	//�v���C���[���W�|�C���^�ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3* mpSavePlayerPointer;

public:

	//�R���X�g���N�^
	BossEnemyMainStateMove();
	//�f�X�g���N�^
	~BossEnemyMainStateMove();
	//����������
	void Initialize(IEnemy* pEnemy)override;
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;


	//��ԕύX
	void ChangeStateWalk()
	{
		mState = BossEnemyMoveState::WALK;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpWalk.get());
	}
	void ChangeStateEscape()
	{
		mState = BossEnemyMoveState::ESCAPE;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpEscape.get());
	}
	void ChangeStateStand()
	{
		mState = BossEnemyMoveState::STAND;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpStand.get());
	}

	//���݂̏��
	BossEnemyMoveState GetMoveState()const { return mState; }

	//�v���C���[���W�|�C���^�ۑ��p�ϐ��̃A�N�Z�T
	void SetSavePlayerPointer(DirectX::SimpleMath::Vector3* position)
	{
		mpSavePlayerPointer = position;
	}
	DirectX::SimpleMath::Vector3* GetSavePlayerPointer()const { return mpSavePlayerPointer; }

	//�ړ��x�N�g���̐���
	DirectX::SimpleMath::Vector3 CreateMoveVector(const float& moveVelocity);

	//�������ߏ���
	float CalculationModelAngle();

};
