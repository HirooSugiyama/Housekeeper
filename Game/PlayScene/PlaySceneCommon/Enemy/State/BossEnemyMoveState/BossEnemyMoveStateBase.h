/*
�{�X�G�ړ�State���N���X
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//�O���錾
class BossEnemyMainStateMove;
class IEnemy;

class BossEnemyMoveStateBase
{
private:


	//�ۑ��p�|�C���^
	BossEnemyMainStateMove* mpMoveState;
	IEnemy* mpEnemy;

public:

	//�R���X�g���N�^
	BossEnemyMoveStateBase();
	//�f�X�g���N�^
	~BossEnemyMoveStateBase();
	//����������
	virtual void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState) = 0;
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�ړ����x�ݒ�
	virtual DirectX::SimpleMath::Vector3 GetMoveVelocity() = 0;
	//�����ݒ�
	virtual void SetAngle() = 0;
	
	//������Ԑ�p����
	virtual void EscapeUpdate(){}

	//�ۑ��p�|�C���^�̃A�N�Z�T
	BossEnemyMainStateMove* GetMoveState()const { return mpMoveState; }
	void SetMoveState(BossEnemyMainStateMove* pState) { mpMoveState = pState; }
	IEnemy* GetBossEnemy() const { return mpEnemy; }
	void SetBossEnemy(IEnemy* pState) { mpEnemy = pState; }
};
