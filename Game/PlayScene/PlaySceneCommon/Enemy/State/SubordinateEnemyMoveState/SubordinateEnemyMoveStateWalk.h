/*
�z���G�ړ�State�@�`���s�`
�쐬�ҁF���R
�쐬���F2022/02/14
*/
#pragma once

//���N���X
#include"SubordinateEnemyMoveStateBase.h"

class SubordinateEnemyMoveStateWalk :public SubordinateEnemyMoveStateBase
{
private:

	//�ړ����x
	static const float SUBORDINATE_ENEMY_MOVE_VELOCITY;

	//���������W��
	static const int ANGLE_SHIFT;


	//�ǂ��������x
	DirectX::SimpleMath::Vector3 mChaseVelocity;

	//�Ώۂ̃|�C���^
	DirectX::SimpleMath::Vector3* mpSavePlayerPointer;

public:

	//�R���X�g���N�^
	SubordinateEnemyMoveStateWalk();
	//�f�X�g���N�^
	~SubordinateEnemyMoveStateWalk();
	//����������
	void Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)override;
	//�X�V����
	void Update()override;

	//�Ώۂ̃|�C���^�̃A�N�Z�T
	void SetSavePlayerPointer(DirectX::SimpleMath::Vector3* address) { mpSavePlayerPointer = address; }


private:
	//�ړ�����
	void Move();

	//�������ߏ���
	void CalculationModelAngle();

};
