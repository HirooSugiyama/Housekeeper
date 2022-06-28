/*
�z���G�N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#pragma once

//���N���X
#include"IEnemy.h"

//���State
#include"State/SubordinateEnemyMainStateMove.h"
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateDisappearance.h"

#include"State/SubordinateEnemyState.h"

//�O���錾
//���N���X
class EnemyMainStateBase;	//��ԕ������N���X

class SubordinateEnemy :public IEnemy
{
private:

	//�z���G��HP
	static const int SUBORDINATE_ENEMY_HP;

	//���݂̏��
	EnemyMainStateBase* mpState;
	SubordinateEnemyMainState mState;

	//���State
	std::unique_ptr<EnemyMainStateCreateBefore> mpCrateBefore;
	std::unique_ptr<SubordinateEnemyMainStateMove> mpMove;
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;

public:

	//�R���X�g���N�^
	SubordinateEnemy();
	//�f�X�g���N�^
	~SubordinateEnemy()override;
	//����������
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;

	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

	//�g�p�t���O�̎擾
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }


	//��ԕύX����
	void ChangeStateCreateBefore()override
	{
		mState = SubordinateEnemyMainState::CREATE_BEFORE;
		mpState = static_cast<EnemyMainStateBase*>(mpCrateBefore.get());
	}
	void ChangeStateMove()override
	{
		mState = SubordinateEnemyMainState::MOVE;
		mpState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}
	void ChangeStateDisappearance()override
	{
		mState = SubordinateEnemyMainState::DISAPPEARANCE;
		mpState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}


	//��ԏ����̃A�N�Z�T
	SubordinateEnemyMainState GetState() const { return mState; }
	EnemyMainStateCreateBefore* GetStateCrateBefore()const { return mpCrateBefore.get(); }
	SubordinateEnemyMainStateMove* GetStateMove()const { return mpMove.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance()const { return mpDisappearance.get(); }


	//�G��HP�̃A�N�Z�T
	int GetEnemyHP() override{ return SUBORDINATE_ENEMY_HP; }

private:
	//�����蔻��ݒ�
	void SetCollider();
};
