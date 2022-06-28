/*
�G�N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#pragma once


//�p����
#include"IEnemy.h"

//�񋓌^�̎g�p
#include"StateEnemy.h"
#include"AngleEnemy.h"

//����
#include"../ObjectModel/BoxModel.h"
//���State
#include"State/EnemyMainStateMove.h"
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateMove.h"
#include"State/EnemyMainStateDamage.h"
#include"State/EnemyMainStateDisappearance.h"

//�񋓌^�̎g�p
#include"State/EnemyMainState.h"
//�O���錾
class EnemyMainStateBase;	//��ԕ������N���X

struct AABB;				//�֐��̕Ԃ�l�Ŏg�p

class CameraBase;			//����
class Enemy :public IEnemy
{
private:
	//�萔
	//�ړ����x
	static const float ENEMY_MOVE_SPEED;

	//���f���`��͈͎w��
	static const float ENEMY_MDEL_DROW_AREA;

	//�u���b�N�ԍ��ۑ���
	static const int ENEMY_SAVE_BLOCKNUMBER_MAX_NUM = 3;
	//�u���b�N�ԍ���O����
	static const int ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM;

	//�G���f���������I�ɉ��Ɍ�����(�������]����ۂɎg�p)
	static const float ENEMY_MODEL_FORCED_BESIDE;

	//�G��HP
	static const int ENEMY_HP;

	//���]��
	static const int REVERSE_NUM;

	//�G�̍U����
	static const int ENEMY_ATTACK_NUM;


	//�����n�߂�t�F�[�Y�ԍ�
	int mMovePhaseNumber;

	//���
	//���݂̏��
	EnemyMainStateBase* mpMainState;
	std::unique_ptr<EnemyMainStateCreateBefore> mpCreateBefore;
	std::unique_ptr<EnemyMainStateMove> mpMove;
	std::unique_ptr<EnemyMainStateDamage> mpDamage;
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;
	//��ԊǗ��񋓌^
	EnemyMainState mState;


	//���݂̃��f���̌�����\��
	eAngleEnemy mEnemyModelAngle;

public:
	//�֐�
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;
	//�X�V
	void Update()override;
	//�`��
	void Draw()override;

	//�u���b�N�U������
	void AttackBlock(Block* pBlock);

	//�ǉ������
	void AvoidanceBlock(Block* pBlock);

	//�g�p�t���O��Ԃ�
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }
	
	//�A�N�Z�T�֘A
	//��ԕ���
	void ChangeStateCreateBefore() override
	{ 
		mState = EnemyMainState::CREATE_BEFORE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreateBefore.get());
	}
	void ChangeStateMove()override
	{
		mState = EnemyMainState::MOVE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}
	void ChangeStateDamage()
	{
		mState = EnemyMainState::DAMAGE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDamage.get());
		//�_���[�W��Ԃ̍ŏ��̏�Ԃ͕K���������
		mpDamage->ChangeStateKnockBack();

	}
	void ChangeStateDisappearance()override
	{
		mState = EnemyMainState::DISAPPEARANCE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}

	//��Ԃ��擾
	EnemyMainState GetEnemyMainState()const { return mState; }


	EnemyMainStateCreateBefore* GetStateCreateBefore() const { return mpCreateBefore.get(); }
	EnemyMainStateMove* GetStateMove()const { return mpMove.get(); }
	EnemyMainStateDamage* GetStateDamage() const { return mpDamage.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance() const { return mpDisappearance.get(); }

	//�n������t�F�[�Y�ԍ��̃A�N�Z�T
	void SetMovePhaseNumber(const int& num){ mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const {return mMovePhaseNumber;}

	//���f���̌����̃A�N�Z�T
	eAngleEnemy GetAngleEnemy()const { return mEnemyModelAngle; }
	void SetAngleEnemy(const eAngleEnemy& angle) { mEnemyModelAngle = angle; }

	//�G��HP�̃A�N�Z�T
	int GetEnemyHP()override { return ENEMY_HP; }

	//�ړ�����
	void Move();

private:
	//���f����ݒ肷��
	void SetEnemyModel();
};
