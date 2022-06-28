/*
�{�X�G�N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#pragma once

//���N���X
#include"IEnemy.h"

//����
#include"../FlatPolygon.h"

//��ԕ���
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateDisappearance.h"
#include"State/BossEnemyMainStateAttack.h"
#include"State/BossEnemyMainStateCreate.h"
#include"State/BossEnemyMainStateMove.h"

//�񋓌^�̎g�p
#include"State/BossEnemyState.h"

//�O���錾
class SubordinateEnemy;

//��Ԋ��N���X
class EnemyMainStateBase;

class BossEnemy :public IEnemy
{
private:
	//�F���͈͂̊g�嗦
	static const float RECOGITION_RANGE_SCALE;

	//�{�X�G��HP
	static const int BOSS_ENEMY_HP;


	//�v���C���[�F���͈�
	std::unique_ptr<FlatPolygon> mpPlayerRecognitionRange;

	//�z���G�̃A�h���X�Ǘ��p�ϐ�
	std::vector<SubordinateEnemy*> mpSaveSubordinateEnemy;

	//�F���͈͓����蔻��
	Sphere mPlayerRecognitionRangeCollider;

	//�����o���^�C�~���O
	int mMovePhaseNumber;

	//�����t���O
	bool mActiveFlag;

	//���݂̏��
	EnemyMainStateBase* mpMainState;
	BossEnemyMainState mState;

	//��ԕ���
	/*�ʏ�Ƌ���*/
	//�����O
	std::unique_ptr<EnemyMainStateCreateBefore> mpCreateBefore;
	//����
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;

	/*����*/
	//�ړ�
	std::unique_ptr<BossEnemyMainStateMove> mpMove;

	//�U��
	std::unique_ptr<BossEnemyMainStateAttack> mpAttack;

	//����
	std::unique_ptr<BossEnemyMainStateCreate> mpCreate;

public:

	//�R���X�g���N�^
	BossEnemy();
	//�f�X�g���N�^
	~BossEnemy()override;
	//����������
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

	//�g�p�t���O
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }

	//�z���G�̃A�h���X�Ǘ��p�ϐ��̃A�N�Z�T
	std::vector<SubordinateEnemy*> GetSaveSubordinateEnemy()const { return mpSaveSubordinateEnemy; }
	void SetSaveSubordinateEnemy(std::vector<SubordinateEnemy*> pSubordinateEnemy);

	//�F���͈͂̓����蔻��̃A�N�Z�T
	Sphere* GetPlayerRecognitionRangeCollider() { return &mPlayerRecognitionRangeCollider; }

	//�n������t�F�[�Y�ԍ��̃A�N�Z�T
	void SetMovePhaseNumber(const int& num) { mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const { return mMovePhaseNumber; }

	//��ԕ���
	/*�ʏ�Ƌ���*/
	//�����O
	void ChangeStateCreateBefore()override
	{
		mState = BossEnemyMainState::CREATE_BEFORE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreateBefore.get());
	}
	//����
	void ChangeStateDisappearance()override
	{
		mState = BossEnemyMainState::DISAPPEARANCE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}

	/*����*/
	//�ړ�
	void ChangeStateMove()override
	{
		mState = BossEnemyMainState::MOVE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}

	//�U��
	void ChangeStateAttack()
	{
		mState = BossEnemyMainState::ATTACK;
		mpMainState = static_cast<EnemyMainStateBase*>(mpAttack.get());
	}
	//����
	void ChangeStateCreate()
	{
		mState = BossEnemyMainState::CREATE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreate.get());
	}

	//��Ԃ̎擾
	BossEnemyMainState GetState() { return mState; }
	EnemyMainStateCreateBefore* GetStateCreateBefore() { return mpCreateBefore.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance() { return mpDisappearance.get(); }
	BossEnemyMainStateMove* GetStateMove() { return mpMove.get(); }
	BossEnemyMainStateAttack* GetStateAttack() { return mpAttack.get(); }
	BossEnemyMainStateCreate* GeStatetCreate() { return mpCreate.get(); }


	//�G��HP�̃A�N�Z�T
	int GetEnemyHP() override { return BOSS_ENEMY_HP; }

	//�����t���O�̃A�N�Z�T
	bool GetActiveFlag()const { return mActiveFlag; }
	void SetActiveFlag(const bool& flag) { mActiveFlag = flag; }

private:
	//�����蔻��ݒ�
	void SetCollider();

	//�|�C���^�폜����
	void DeleteSubordinateEnemyAddress();

};
