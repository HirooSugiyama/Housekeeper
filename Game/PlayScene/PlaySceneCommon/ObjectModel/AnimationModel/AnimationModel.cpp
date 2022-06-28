/*
�A�j���[�V�������f��
�쐬�ҁF���R
�쐬���F2021/12/26
*/
#include"pch.h"

#include"AnimationModel.h"
#include"Game/Manager/ResourceManager.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
AnimationModel::AnimationModel()
	:mpModel()
	,mBones()
	,mpAnimation()
{
	mpModel = std::make_unique<ObjectModel>();
}

/*=================================
�f�X�g���N�^
===================================*/
AnimationModel::~AnimationModel()
{
	mpModel.reset();
}

/*=================================
����������
�����F�t�@�C���̃L�[���
�Ԃ�l�F�Ȃ�
===================================*/
void AnimationModel::Initialize(const int& fileKey)
{
	//���\�[�X�}�l�[�W����������擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	AnimModel* animModel = pRM->GetAnimationCmoModel(fileKey);

	//���̕ۑ�
	mpModel->SetModel(animModel->mModel.get());

	mpAnimation = &animModel->mAnim;

	mpAnimation->Bind(*mpModel->GetModel());

	mBones = DirectX::ModelBone::MakeArray(mpModel->GetModel()->bones.size());

	mpModel->GetModel()->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto skin = dynamic_cast<DirectX::SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		});


}
/*===================================
�X�V����
�����F����
�Ԃ�l�F�Ȃ�
===================================*/
void AnimationModel::Update(const float& deltaTime)
{
	//�A�j���[�V�����X�V����
	mpAnimation->Update(deltaTime);

	//���f���X�V����(�F�ς�)
	mpModel->Update();
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void AnimationModel::Draw()
{
	const auto pDeviceResources = DX::DeviceResources::GetInstance();
	const auto& pCameraInfoComponent = CameraInfoComponent::GetCameraInfoComponentInstance();
	const auto& pDirectXtkComponent = DirectXtkComponent::GetDirectXtkComponentInstance();

	// �f�o�C�X�R���e�L�X�g�̎擾
	auto context = pDeviceResources->GetD3DDeviceContext();

	//�F���ݒ肵�Ă���ꍇ�̂ݏ�����ʂ�
	//�F�ς�����
	this->UpdateColor();

	//�{�[���̃T�C�Y���擾
	size_t nbones = mpModel->GetModel()->bones.size();

	mpAnimation->Apply(*mpModel->GetModel(), nbones, mBones.get());

	//���[���h���W���v�Z���Ă���
	mpModel->CalculationWorldMatrix();

	mpModel->GetModel()->DrawSkinned
	(
		context,
		*pDirectXtkComponent.GetCommonStates(),
		nbones,
		mBones.get(),
		mpModel->GetWorld(),
		*pCameraInfoComponent.GetView(),
		*pCameraInfoComponent.GetProjection()
	);
}

/*==================================
�F�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void AnimationModel::UpdateColor()
{
	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 color{ DirectX::Colors::Gray };

	//�t���O�������Ă���Ƃ��̂ݎw�肷��
	if (mColorFlag)
	{
		color = mColor;
	}
	else
	{
		return;
	}

	//�F�ݒ�
	mpModel->GetModel()->UpdateEffects
	(
		[=](DirectX::IEffect* effect)
		{
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightingEnabled(true);
				lights->SetPerPixelLighting(true);
				lights->SetLightEnabled(0, true);
				lights->SetLightDiffuseColor(0, color);
				lights->SetLightEnabled(1, true);
				lights->SetLightDiffuseColor(1, color);
				lights->SetLightEnabled(2, true);
				lights->SetLightDiffuseColor(2, color);
			}
		}
	);
}
