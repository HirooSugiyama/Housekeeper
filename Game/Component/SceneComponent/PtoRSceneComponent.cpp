/*
�v���C�V�[�����烊�U���g�V�[���֏���n�����߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include"pch.h"
#include"PtoRSceneComponent.h"

//�O���ŏ�����
std::unique_ptr<PtoRSceneComponent> PtoRSceneComponent::sPtoRComponent = nullptr;

/*================
�R���X�g���N�^
�����F�Ȃ�
================*/
PtoRSceneComponent::PtoRSceneComponent()
	:mScoreNum()
{
}


/*========================
�C���X�^���X�̎擾
�����F�Ȃ�
�Ԃ�l�F���g�̃|�C���^
==========================*/
PtoRSceneComponent& PtoRSceneComponent::GetPtoRIFInstance()
{
	if (sPtoRComponent == nullptr)
	{
		sPtoRComponent.reset(new PtoRSceneComponent());
	}
	return *sPtoRComponent;
}
