/*
�X�v���C�g���f���`��N���X
�쐬�ҁF���R
�쐬���F2021/04/18
*/
#include<pch.h>
#include"ObjectSpriteModel.h"

// ���f���̃X�v���C�g�ԍ����ő�l�𒴂������������������邽�߂̌W��
const int ObjectSpriteModel::SPRITE_REVERSE_NUM = 2;
/*
���X�v���C�g�l���ő�l�𒴂����ꍇ�Ɉ������߂̌W��
�E���O�Ń��f���v�f���̍ő�l�𒴂��Ă��邽�ߔ͈͓��ɖ߂����߂̏����Ƃ���[1]���炷�B
�E�X�v���C�g�P�T�C�N�����ς��Ȃ���Ԃŉ���Ă��܂����߂����[1]���炷�B
*/


/*======================================
�R���X�g���N�^
�����F�X�v���C�g�̍ő吔
========================================*/

ObjectSpriteModel::ObjectSpriteModel(const int& maxspritenum)
	:
	IModel(),
	mpCommonState(nullptr),
	mpSpriteBatch(nullptr),
	mpSpriteFont(nullptr),
	mWorld(),
	mView(),
	mProj(),
	mFxFactory(),
	mModel{},
	mPosition(),
	mScale(),
	mRot(),
	mPosition3(),
	mScale3(),
	mDrawFlag(true),
	mSpriteTimer(0),
	mConstTimer(0),
	mSpriteFlag(true),
	mUseModelNum(0),
	mMaxSpriteNum(maxspritenum),
	mReverseFlag(false)
{
	// �R�����X�e�[�g::D3D�����_�����O��ԃI�u�W�F�N�g
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	mpCommonState = pDxIF.GetCommonStates();
	mpSpriteBatch = pDxIF.GetSpriteBatch();
	mpSpriteFont = pDxIF.GetSpriteFont();
	//�C���X�^���X�̎擾
		//�r���[�s��A�v���W�F�N�V�����s��̎擾
	const auto pDR = DX::DeviceResources::GetInstance();
	ID3D11Device1* pDevice = pDR->GetD3DDevice();
	const auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();
	mView = *pCiIF.GetView();
	mProj = *pCiIF.GetProjection();

	// ���f���f�[�^�̓����Ă���t�H���_�̎w��
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(pDevice);
	factory->SetDirectory(L"Resources/Models/");


	mFxFactory = std::make_unique<DirectX::EffectFactory>(pDevice);
	mWorld = DirectX::SimpleMath::Matrix::Identity;


	mScale3 = DirectX::SimpleMath::Vector3::One;
	mPosition3 = DirectX::SimpleMath::Vector3::Zero;
	//������̉��
	mWorld = DirectX::SimpleMath::Matrix::CreateScale(mScale3);
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);

	//�������m��
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mModel.push_back(nullptr);
	}
}

/*===================================
�f�X�g���N�^
===================================*/
ObjectSpriteModel::~ObjectSpriteModel()
{
}

/*=============================================
���f���̎w��
�����F�X�v���C�g�̍ő吔�A���f�����
�Ԃ�l�F�Ȃ�
========================================================*/
void ObjectSpriteModel::SetSpriteModel(const int& spritenum, DirectX::Model* model)
{
	mModel[spritenum] = model;
}

/*============
���W�̎w��
�����F���W
�Ԃ�l�F�Ȃ�
==============*/
void ObjectSpriteModel::SetPosition( const DirectX::SimpleMath::Vector3& position)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(position);

		mPosition3 = position;
	}
}

/*============
�g�嗦�̎w��
�����F���W
�Ԃ�l�F�Ȃ�
==============*/
void ObjectSpriteModel::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mScale = DirectX::SimpleMath::Matrix::CreateScale(scale);
		mScale3 = scale;
	}
}

/*============
��]�̎w��
�����F��]��
�Ԃ�l�F�Ȃ�
==============*/
void ObjectSpriteModel::SetRotationX(const float& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rot));
	}	
}
void ObjectSpriteModel::SetRotationY(const float& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rot));
	}	
}
void ObjectSpriteModel::SetRotationZ(const float& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rot));
	}
}


/*================================
���W�̎擾
�����F�Ȃ�
�Ԃ�l�F���W(x,y,z)
==================================*/
DirectX::SimpleMath::Vector3 ObjectSpriteModel::GetPosition()const 
{
	return mPosition3;
}

/*================================
�g�嗦�̎擾
�����F�Ȃ�
�Ԃ�l�F�g�嗦(x,y,z)
==================================*/
DirectX::SimpleMath::Vector3 ObjectSpriteModel::GetScale()const
{
	return mScale3;
}


/*===================
�ړ�
�����F�̓x�N�g��
�Ԃ�l�F�Ȃ�
=====================*/
void ObjectSpriteModel::Move(const DirectX::SimpleMath::Vector3& vel)
{
	//�ϐ��̐錾
	DirectX::SimpleMath::Vector3 vel3 = vel;

	
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);
		//���݂̍��W�Ɉ����̍��W��ǉ�����
		mPosition3 += vel3;
	}	
}

/*============
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============*/
void ObjectSpriteModel::SpriteUpdate() 
{
	//�����X�v���C�g���񂷃t���O�������Ă��Ȃ������珈����ʂ��Ȃ�
	if (!mSpriteFlag)
	{
		return;
	}

	//�X�v���C�g�^�C�}�[����
	mSpriteTimer++;
	if (!mReverseFlag)
	{
		//�����X�v���C�g���񂷃^�C�~���O��������
		if (mSpriteTimer == mConstTimer)
		{
			//�^�C�}�[�͏���������
			mSpriteTimer = 0;
			mUseModelNum++;
			//�����g�p���f�������f���ő吔���z������
			if (mUseModelNum >= mMaxSpriteNum) 
			{
				mUseModelNum = mMaxSpriteNum - SPRITE_REVERSE_NUM;
				mReverseFlag = true;
			}
		}
	}
	else
	{
		//�����X�v���C�g���񂷃^�C�~���O��������
		if (mSpriteTimer == mConstTimer)
		{
			//�^�C�}�[�͏���������
			mSpriteTimer = 0;
			mUseModelNum--;
			//�����g�p���f�������f���ő吔���z������
			if (mUseModelNum <= 0) 
			{
				mReverseFlag = false;
			}
		}
	}
}


/*==================================
�`��
�����F���[���h���W(�����Ă���)
�Ԃ�l�F�Ȃ�
======================================*/
void ObjectSpriteModel::Draw(DirectX::SimpleMath::Matrix* world)
{
	if (mDrawFlag)
	{
		//�C���X�^���X�̎擾
		const auto pDR = DX::DeviceResources::GetInstance();


		const auto& pDI = DirectXtkComponent::GetDirectXtkComponentInstance();
		const auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();


		mView = *pCiIF.GetView();

		mProj = *pCiIF.GetProjection();

		if (world == nullptr)
		{
			//���낢�딽�f
			mWorld = mRot * mScale * mPosition;
		}

		ID3D11DeviceContext1* pContext = pDR->GetD3DDeviceContext();

		mModel[mUseModelNum]->Draw
		(pContext, *pDI.GetCommonStates(), mWorld, mView, mProj);
	}
}
