/*
�X�e�[�W�Z���N�g��ʂ���v���C�V�[���֏���n�����߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include"pch.h"
#include"StoPSceneComponent.h"

//�O���ŏ�����
std::unique_ptr<StoPSceneComponent> StoPSceneComponent::sStoPComponent = nullptr;


/*================
�R���X�g���N�^
�����F�Ȃ�
================*/
StoPSceneComponent::StoPSceneComponent()
	:
	mCSVFileName("none"),
	mStageNumber("-1")
{
}


/*================================
�C���X�^���X�̎擾
�����F�Ȃ�
�Ԃ�l�F���g�̃|�C���^
================================*/
StoPSceneComponent& StoPSceneComponent::GetStoPIFInstance()
{
	if (sStoPComponent == nullptr)
	{
		sStoPComponent.reset(new StoPSceneComponent());
	}
	return *sStoPComponent;
}
