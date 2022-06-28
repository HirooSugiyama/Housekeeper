/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F������
�쐬�ҁF���R
�쐬���F2021/06/15
*/
#include"pch.h"

#include"PStateDamage.h"


//�O���錾
#include"../DamageTimer.h"

//�Ԃ�l����̊֐��̎擾�Ŏg�p�B
#include"../ObjectModel/BoxModel.h"

//�v���C���[�_�ŃC���^�[�o��
const int PStateDamage::PLAYER_BLINKING_INTERVAL = 20;

/*=========================
�R���X�g���N�^
�����F�Ȃ�
=========================*/
PStateDamage::PStateDamage()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpDamageTimer(nullptr)

{
	mpDamageTimer = std::make_unique<DamageTimer>();
}

/*=========================
�f�X�g���N�^
=========================*/
PStateDamage::~PStateDamage()
{
}

/*=========================
����������
�����F�v���C���[�̃|�C���^
�Ԃ�l�F�Ȃ�
=========================*/
void PStateDamage::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

/*=========================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void PStateDamage::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::DAMAGE) 
	{
		mpPlayer->SetState(ePlayerState::DAMAGE);
	}

	//���Ԃ�������
	if (mpDamageTimer->Update()) 
	{
		//���Ԃ������痧����Ԃɖ߂�
		mpPlayer->ChangeStateStand();
	}
}

/*=========================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void PStateDamage::Draw()
{
	//���f���`��
	//�_�ŕ\��������
	if (mpDamageTimer->RegularIntervalTimer(PLAYER_BLINKING_INTERVAL)) 
	{
		mpPlayer->GetPlayerModel()->Draw();
	}
}
