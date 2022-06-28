/*
�{�X�G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"BossEnemyMoveStateBase.h"

class BossEnemyMoveStateEscape :public BossEnemyMoveStateBase
{
private:	
	
	//�ړ����x
	static const float ENEMY_ESCAPE_SPEED;

	//�v���C���[�Ƃ̑��苗��
	static const float PLAYER_DISTANCE;

public:

	//�R���X�g���N�^
	BossEnemyMoveStateEscape();
	//�f�X�g���N�^
	~BossEnemyMoveStateEscape();
	//����������
	void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)override;

	//�����ݒ菈��
	void SetAngle()override;

	//������Ԑ�p�X�V����
	void EscapeUpdate()override;

	//�ړ����x�ݒ�
	DirectX::SimpleMath::Vector3 GetMoveVelocity()override;
};
