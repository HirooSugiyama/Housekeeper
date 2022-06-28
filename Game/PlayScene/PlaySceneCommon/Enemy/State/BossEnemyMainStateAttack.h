/*
�{�X�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"EnemyMainStateBase.h"

#include"EnemyMoveState/EnemyMoveStateRotation.h"
#include"EnemyMoveState/EnemyMoveStateWalk.h"
#include"EnemyMoveState/EnemyMoveStateWallAttack.h"

//�񋓌^�̎g�p
#include"EnemyMainState.h"


//�O���錾
class EnemyMoveStateBase;	//���State
class Block;				//����

class BossEnemyMainStateAttack : public EnemyMainStateBase
{
private:

	//���݂̏��
	EnemyMoveStateBase* mpEnemyMoveStateBase;
	EnemyMoveState mState;

	//��ԕ���


public:

	//�R���X�g���N�^
	BossEnemyMainStateAttack();
	//�f�X�g���N�^
	~BossEnemyMainStateAttack();
	//����������
	void Initialize(IEnemy* pEnemy)override;
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

	//���݂̏��
	EnemyMoveState GetMoveState()const { return mState; }

};
