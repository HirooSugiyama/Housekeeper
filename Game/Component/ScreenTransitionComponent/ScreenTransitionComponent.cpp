/*
��ʑJ�ڊǗ��N���X(Singleton)
�쐬�ҁF���R
�쐬���F2021/12/28
*/

#include"pch.h"

//�N���X�O���ŏ�����
std::unique_ptr <ScreenTransitionComponent> 
	ScreenTransitionComponent::sTransitionInterface = nullptr;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
ScreenTransitionComponent::ScreenTransitionComponent()
	:
	mpWipe(),
	mWipeUseFlag(false),
	mpFade(),
	mFadeUseFlag(false)
{
	mpWipe = std::make_unique<Wipe>();
	mpFade = std::make_unique<Fade>();
}



/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F���g�̃|�C���^
===================================*/
ScreenTransitionComponent& ScreenTransitionComponent::GetScreenTransitionInstance()
{

	if (sTransitionInterface == nullptr)
	{
		sTransitionInterface.reset(new ScreenTransitionComponent());
	}
	return *sTransitionInterface;
}