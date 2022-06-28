/*
�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/07
*/
#pragma once

//���N���X
#include"EnemyMainStateBase.h"

//�񋓌^�̎g�p
#include"SubordinateEnemyState.h"

//��ԕ���
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateStand.h"
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateWalk.h"

//�񋓌^�̎g�p
#include"SubordinateEnemyState.h"

//�O���錾
class SubordinateEnemyMoveStateBase;	//���State���N���X
class IEnemy;

class SubordinateEnemyMainStateMove : public EnemyMainStateBase
{

private:

	////���݂̏��
	SubordinateEnemyMoveStateBase* mpMoveStateBase;
	SubordinateEnemyMoveState mState;
	
	//��ԕ���
	std::unique_ptr<SubordinateEnemyMoveStateStand> mpStand;
	std::unique_ptr<SubordinateEnemyMoveStateWalk> mpWalk;
	

public:

	//�R���X�g���N�^
	SubordinateEnemyMainStateMove();
	//�f�X�g���N�^
	~SubordinateEnemyMainStateMove();
	//����������
	void Initialize(IEnemy* pEnemy)override;
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;


	//��ԕ���
	void ChangeStateStand()
	{
		mState = SubordinateEnemyMoveState::STAND;
		mpMoveStateBase = static_cast<SubordinateEnemyMoveStateBase*>(mpStand.get());
	}
	void ChangeStateWalk()
	{
		mState = SubordinateEnemyMoveState::WALK;
		mpMoveStateBase = static_cast<SubordinateEnemyMoveStateBase*>(mpWalk.get());
	}
	
	//�A�N�Z�T

	SubordinateEnemyMoveState GetState()const { return mState; }
	SubordinateEnemyMoveStateStand* GetStand()const { return mpStand.get(); }
	SubordinateEnemyMoveStateWalk* GetWalk()const { return mpWalk.get(); }

};
