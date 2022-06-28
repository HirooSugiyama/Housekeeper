/*
�z���G�ړ�State�@�`������ԁ`
�쐬�ҁF���R
�쐬���F2022/02/14
*/
#pragma once

//���N���X
#include"SubordinateEnemyMoveStateBase.h"


//����
#include"Game/PlayScene/PlaySceneCommon/Administrator/Timer.h"

class SubordinateEnemyMoveStateStand :public SubordinateEnemyMoveStateBase
{
private:
	
	//��~�C���^�[�o������
	static const int STAND_INTERVAL;

	//��~�C���^�[�o���v���ϐ�
	std::unique_ptr<Timer> mpTimer;

	//��~�C���^�[�o���ғ��t���O
	bool mStandIntervalActiveFlag;

public:

	//�R���X�g���N�^
	SubordinateEnemyMoveStateStand();
	//�f�X�g���N�^
	~SubordinateEnemyMoveStateStand()override;
	//����������
	void Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)override;
	//�X�V����
	void Update()override;

	//��~�C���^�[�o���ғ��t���O�̃A�N�Z�T
	void SetStandIntervalActiveFlag(const bool& flag) { mStandIntervalActiveFlag = flag; }
};
