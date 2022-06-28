/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"BossEnemyMoveStateBase.h"

class BossEnemyMoveStateStand :public BossEnemyMoveStateBase
{
private:

public:

	//�R���X�g���N�^
	BossEnemyMoveStateStand();
	//�f�X�g���N�^
	~BossEnemyMoveStateStand();
	//����������
	void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)override;

	//�����ݒ菈��
	void SetAngle()override;

	//�ړ����x�ݒ�
	DirectX::SimpleMath::Vector3 GetMoveVelocity()override { return DirectX::SimpleMath::Vector3::Zero; }


};
