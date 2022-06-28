/*
�^�C�}�[���Ǘ�����C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/14
*/
#include"pch.h"

//�N���X�O���ŏ�����
std::unique_ptr<TimerComponent> TimerComponent::sTimerComponent = nullptr;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
TimerComponent::TimerComponent()
	:
	mTimer()
{
}


/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F���g�̃|�C���^
===================================*/
TimerComponent& TimerComponent::GetTimerInstance()
{

	if (sTimerComponent == nullptr)
	{
		sTimerComponent.reset(new TimerComponent());
	}
	return *sTimerComponent;
}

