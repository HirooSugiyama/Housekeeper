
/*
�z���G�ړ�State�@�`������ԁ`
�쐬�ҁF���R
�쐬���F2022/02/14
*/
#include"pch.h"

#include"SubordinateEnemyMoveStateStand.h"

//�֐��̎g�p
#include"../SubordinateEnemyMainStateMove.h"


//��~�C���^�[�o������
const int SubordinateEnemyMoveStateStand::STAND_INTERVAL = 2;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
SubordinateEnemyMoveStateStand::SubordinateEnemyMoveStateStand()
	:
	SubordinateEnemyMoveStateBase(),
	mpTimer(),
	mStandIntervalActiveFlag()
{
	mpTimer = std::make_unique<Timer>();
}

/*===================================
�f�X�g���N�^
===================================*/
SubordinateEnemyMoveStateStand::~SubordinateEnemyMoveStateStand()
{
}

/*===================================
����������
�����F�G�̃|�C���^�A�G�̍s��State
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateStand::Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)
{
	//�|�C���^�ۑ�
	SubordinateEnemyMoveStateBase::SetEnemy(pEnemy);
	SubordinateEnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);


	//�^�C�}�[�ݒ菈��
	mpTimer->SetMaxTime(STAND_INTERVAL);
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemyMoveStateStand::Update()
{
	//�t���O�������Ă��Ȃ��ꍇ���������Ȃ�
	if (!mStandIntervalActiveFlag)return;

	//�^�C�}�[�X�V����
	bool finishFlag = mpTimer->Update();

	//���ԂƂȂ�����
	if (finishFlag)
	{
		//�t���O������
		mStandIntervalActiveFlag = false;

		//�^�C�}�[�����Z�b�g����
		mpTimer->ResetMainTimer();

		//��ԕύX
		SubordinateEnemyMoveStateBase::GetEnemyMainState()->ChangeStateWalk();
	}
}
