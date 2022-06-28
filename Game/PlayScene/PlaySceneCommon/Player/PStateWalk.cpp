/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F�ړ����
�쐬�ҁF���R
�쐬���F2021/06/15
*/
#include"pch.h"

#include "PStateWalk.h"

//�Ԃ�l����̊֐��̎擾�Ŏg�p�B
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"

//�ړ����x�̎擾�Ɏg�p
#include"../ObjectMove.h"

//�����Œ�`����B
const float MoveSpeed::MOVE_VELOCITY_X = 0.15f;
const float MoveSpeed::MOVE_VELOCITY_Y = 0.15f;
const float MoveSpeed::MOVE_VELOCITY_Z = 0.15f;


//�u���b�N�͈̔�
const float PStateWalk::MAX_POSITION_X = Utility::FIELD_MAX_SIZE_X;
const float PStateWalk::MAX_POSITION_Z = Utility::FIELD_MAX_SIZE_Z;
const float PStateWalk::MIN_POSITION_Z = Utility::FIELD_MIN_SIZE_Z;

//�X�v���C�g�̐�
const int PStateWalk::WALKPLAYER_SPRITE_NUM = 5;

//�X�v���C�g�̃T�C�N��(���̎��Ԏ����ŃX�v���C�g�����)
const int PStateWalk::WALKPLAYER_SPRITE_CYCLE = 4;


//�v���C���[�̈ړ���(X)
const float PStateWalk::PLAYER_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//�v���C���[�̈ړ���(Y)					
const float PStateWalk::PLAYER_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//�v���C���[�̈ړ���(Z)					 
const float PStateWalk::PLAYER_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;


//�ړ��ʂ̑�����
const float PStateWalk::PLAYER_MOVE_INCREASE_VELOCITY=0.1f;

//��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_L = 90;
//�E	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_R = -90;
//��	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_U = 0;
//��	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_D = 180;
//����
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LU = 45;
//�E��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RU = -PLAYER_CHARACTER_ANGLE_LU;
//����
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LD = 135;
//�E��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RD = -PLAYER_CHARACTER_ANGLE_LD;

//���f���p�x�C��
const float PStateWalk::PLAYER_FIX_MODEL_ROTATION_Y = 180.f;



/*========================
�R���X�g���N�^
�����F�Ȃ�
=========================*/
PStateWalk::PStateWalk()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpWalkAnimationModel(),
	mActualPlayerVelocity(DirectX::SimpleMath::Vector3::Zero),
	mpDestinationPlayerCollider(),
	mGroundObjectXHitFlag(false),
	mGroundObjectZHitFlag(false),
	mBlockHitFlag(false)
{
	mpWalkAnimationModel = std::make_unique<AnimationModel>();

	mpDestinationPlayerCollider = std::make_unique<AABB>();
}

/*=========================
����������
�����F�v���C���[�̃|�C���^
�Ԃ�l�F�Ȃ�
=========================*/
void PStateWalk::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;

	//�A�j���[�V�������f���̐ݒ�
	mpWalkAnimationModel->Initialize(static_cast<int>(PlayModelsResouce::MODEL__ANIMATIONMODEL_STANDARD_RUN));

	//���f���̏����F�͐F��
	DirectX::SimpleMath::Vector3 color = DirectX::Colors::Blue;
	mpWalkAnimationModel->SetColor(color);
}
/*=========================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void PStateWalk::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::WALK)
	{
		mpPlayer->SetState(ePlayerState::WALK);
	}

	//�ړ��ʑ�������
	this->ConstantAcceleration();

	//�ړ��ł��邩���f����
	this->AllObjectHit();

	//�^�C�}�[�̎擾
	const auto& pTimerComponent = TimerComponent::GetTimerInstance();
	//�v���C���[�̃A�j���[�V��������
	mpWalkAnimationModel->Update(static_cast<float>(pTimerComponent.GetTimer().GetElapsedSeconds()));
}

/*=========================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void PStateWalk::Draw()
{
	//�X�v���C�g���f���̏��ݒ�
	this->SetSpriteModelPosition();

	//�p�x���ꎞ�I�ɕۑ�
	float rot = mpWalkAnimationModel->GetModel()->GetRotAngleY();

	//���f���������̌����̃~�X���C��
	mpWalkAnimationModel->GetModel()->SetRotationY(rot+ PLAYER_FIX_MODEL_ROTATION_Y);

	//�A�j���[�V�����̕`��
	mpWalkAnimationModel->Draw();

	//�Đݒ�
	mpWalkAnimationModel->GetModel()->SetRotationY(rot);
}

/*=====================================
�ړ��x�N�g�����Z�o��ݒ肷��
�����F�Ȃ�
�Ԃ�l�F�ړ��x�N�g��
======================================*/
DirectX::SimpleMath::Vector3 PStateWalk::CalculationMoveVelocity()
{
	//�Ԃ�l�p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 returnpos = DirectX::SimpleMath::Vector3::Zero;

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward()|| pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			returnpos.z = -mActualPlayerVelocity.z;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			returnpos.x = -mActualPlayerVelocity.x;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			returnpos.z = mActualPlayerVelocity.z;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			returnpos.x = mActualPlayerVelocity.x;
			side = true;
		}
	}

	//���������̏���(�R���g���[���[�͌����I�ɕs�\�Ȃ̂ŏ����͖���)
	//�o�����ւ̓��͈͂ړ���0�Ƃ���B
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		returnpos.x = 0;
	}


	if(pKey->WalkForward() && pKey->WalkBack())
	{
		returnpos.z = 0;
	}

	//�΂ߕ����̈ړ�����
	if (whith && side && returnpos.x != 0 || returnpos.z != 0)
	{

		//�΂߂Ɉړ�����ۂ͏c���Ƃ͒������قȂ�i���������j�̂ŁA����̒ǉ��̌v�Z�B
		//�x�N�g���̒������擾
		float vl = sqrtf((returnpos.x * returnpos.x) + (returnpos.z * returnpos.z));

		//�P�ʃx�N�g���i�������P�̃x�N�g���j���v�Z
		returnpos.x /= vl;
		returnpos.z /= vl;

		//�ړ��x�N�g����ړI�̑傫���i�ړ��ʁj�ɃX�P�[�����O
		returnpos.x *= mActualPlayerVelocity.x;
		returnpos.z *= mActualPlayerVelocity.z;
	}

	return returnpos;
}


/*==================================================================
�ړ���̃v���C���[�̓����蔻���Ԃ�(�ړ��͂��Ȃ�)
�����F�Ȃ�
�Ԃ�l�F�����蔻��
===================================================================*/
AABB* PStateWalk::GetDestinationPlayerCollider()
{
	//�Z�o�p�����蔻��̐錾
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	
	//�v���C���[�̍��W��ۑ�
	modelpos = mpPlayer->GetPlayerModel()->GetPosition();
	
	//�v���C���[�̊g�嗦��ۑ�
	modelscale = mpPlayer->GetPlayerModel()->GetScale();
	
	//���݂̃L�[���͂ł̈ړ��ʂ��Z�o�p�ϐ��ɒǉ�
	modelpos += mpPlayer->GetStateWalk()->CalculationMoveVelocity();
	
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = modelscale / 2.f;
	halfsize.y *= mpPlayer->GetPlayerColliderExtendY();
	
	//���͂����ƂɎ��̓����蔻����Z�o
	mpDestinationPlayerCollider->SetCollider(modelpos - halfsize, modelpos + halfsize);

	//�����蔻���Ԃ�
	return mpDestinationPlayerCollider.get();
}







/*=====================================
State�J�n���̏���������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
======================================*/
void PStateWalk::SetSpriteModelPosition()
{
	//�ȗ���
	DirectX::SimpleMath::Vector3 position= DirectX::SimpleMath::Vector3::Zero, scale= DirectX::SimpleMath::Vector3::Zero;
	position = mpPlayer->GetPlayerModel()->GetPosition();
	scale = mpPlayer->GetPlayerModel()->GetScale();

	mpWalkAnimationModel->GetModel()->SetPosition(position);
	mpWalkAnimationModel->GetModel()->SetScale(scale);
	
	//�������蔻��͒ʏ탂�f���̕��ŏ���
}

/*=====================================
�ړ��ʂ������x�I�ɑ���������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=======================================*/
void PStateWalk::ConstantAcceleration()
{
	//���������x���ő�l�ł͂Ȃ�������A�����x���������₷�B
	/*X*/
	if (mActualPlayerVelocity.x < PLAYER_MOVE_VELOCITY_X)
	{
		mActualPlayerVelocity.x += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.x = PLAYER_MOVE_VELOCITY_X;
	}
	/*Y*/
	if (mActualPlayerVelocity.y < PLAYER_MOVE_VELOCITY_Y)
	{
		mActualPlayerVelocity.y += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.y = PLAYER_MOVE_VELOCITY_Y;
	}
	/*Z*/
	if (mActualPlayerVelocity.z < PLAYER_MOVE_VELOCITY_Z)
	{
		mActualPlayerVelocity.z += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.y = PLAYER_MOVE_VELOCITY_Y;
	}


}

/*===========================================================================
�S�ẴI�u�W�F�N�g�ɓ������Ă��Ȃ��ꍇ�̂ݏ�����ʂ��֐�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
============================================================================*/
void PStateWalk::AllObjectHit()
{
	//�ǂ̃I�u�W�F�N�g�Ƃ��������Ă��Ȃ�������
	if (mBlockHitFlag == false)
	{
		//�ړ�����
		this->Move();

		//�����蔻����X�V����
		mpPlayer->UpdateCollider();
	}
}

/*=====================================
�ړ�����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
======================================*/
void PStateWalk::Move()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	DirectX::SimpleMath::Vector3 vel;
	int rot = -1;//Model�̌X��

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward() || pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
	{		
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			vel.z = -mActualPlayerVelocity.z;
			rot = PLAYER_CHARACTER_ANGLE_U;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			vel.x = -mActualPlayerVelocity.x;
			rot = PLAYER_CHARACTER_ANGLE_L;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			vel.z = mActualPlayerVelocity.z;
			rot = PLAYER_CHARACTER_ANGLE_D;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			vel.x = mActualPlayerVelocity.x;
			rot = PLAYER_CHARACTER_ANGLE_R;
			side = true;
		}
	}

	//���������̏���(�R���g���[���[�͌����I�ɕs�\�Ȃ̂ŏ����͖���)
	//�o�����ւ̓��͈͂ړ���0�Ƃ���B
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		vel.x = 0;
	}


	if (pKey->WalkForward() && pKey->WalkBack())
	{
		vel.z = 0;
	}


	//�΂ߕ����̈ړ�����
	if (whith && side && vel.x != 0 || vel.z != 0)
	{

		//�΂߂Ɉړ�����ۂ͏c���Ƃ͒������قȂ�i���������j�̂ŁA����̒ǉ��̌v�Z�B
		//�x�N�g���̒������擾
		float vl = sqrtf((vel.x * vel.x) + (vel.z * vel.z));

		//�P�ʃx�N�g�����v�Z
		vel.x /= vl;
		vel.z /= vl;

		//�ړ��x�N�g����ړI�̑傫���i�ړ��ʁj�ɃX�P�[�����O
		vel.x *= mActualPlayerVelocity.x;
		vel.z *= mActualPlayerVelocity.z;

		if (pKey->WalkForward() || pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_LU;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_RU;
			}
		}
		if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_LD;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_RD;
			}
		}
	}

	//��؏������Ȃ������痧����Ԃֈڍs
	if (vel == DirectX::SimpleMath::Vector3::Zero)
	{
		mpPlayer->ChangeStateStand();

		//�����x�����ׂď���������
		this->AllActualPlayerVelocityInit();
	}

	//X������������Z�����ɓ��͂���������
	if (vel.x != 0 || vel.z != 0) 
	{
		if (mGroundObjectXHitFlag&& mGroundObjectZHitFlag)
		{
			return;
		}
		else if (mGroundObjectXHitFlag)
		{
			vel.x = 0.f;
			mpPlayer->GetPlayerModel()->Move(vel);								//���f�����ړ�������B
		}
		else if (mGroundObjectZHitFlag)
		{
			vel.z = 0.f;
			mpPlayer->GetPlayerModel()->Move(vel);								//���f�����ړ�������B
		}
		else
		{
			mpPlayer->GetPlayerModel()->Move(vel);								//���f�����ړ�������B
		}

		
		mpPlayer->GetPlayerModel()->SetRotationY(static_cast<float>(rot));	//�X����ύX������
		mpWalkAnimationModel->GetModel()->SetRotationY(static_cast<float>(rot));
		//degree�ɂ͊֐����ŕϊ�
	}
}

/*=====================================
�g�p��������x�����ׂď�����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
======================================*/
void PStateWalk::AllActualPlayerVelocityInit()
{
	mActualPlayerVelocity = DirectX::SimpleMath::Vector3::Zero;
}
