/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"BossEnemyMoveStateBase.h"

class BossEnemyMoveStateWalk :public BossEnemyMoveStateBase
{
private:
	//�ړ����x
	static const float ENEMY_WALK_SPEED;

public:

	//�R���X�g���N�^
	BossEnemyMoveStateWalk();
	//�f�X�g���N�^
	~BossEnemyMoveStateWalk();
	//����������
	void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)override;

	//�����ݒ菈��
	void SetAngle()override;

	//�ړ����x�ݒ�
	DirectX::SimpleMath::Vector3 GetMoveVelocity()override;
};
