/*
�^�C�}�[
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"

#include"Timer.h"

//�t���[���Œ�l
const float Timer::MIN_FRAME = 50.f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Timer::Timer()
	:
	mMaxTime(),
	mMainTimer(),
	mSubTimer()
{
}

/*===================================
�f�X�g���N�^
===================================*/
Timer::~Timer()
{
}

/*=================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�I���t���O
===================================*/
bool Timer::Update()
{
	//���݂�FPS���擾
	const auto& pT = TimerComponent::GetTimerInstance();

	float fps = static_cast<float>(pT.GetTimer().GetFramesPerSecond());

	//�T�u�^�C�}�[����
	mSubTimer += static_cast<float>(pT.GetTimer().GetElapsedSeconds()) * fps;
 
	//���60FPS==1s�Ȃ̂�
	if (mSubTimer >= fps)
	{
		mSubTimer = 0.f;
		mMainTimer++;
	}

	//�ő厞�ԂƂȂ�����
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}

/*=================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�I���t���O
===================================*/
bool Timer::ManualUpdate()
{
	//�T�u�^�C�}�[����
	mSubTimer ++;

	//���60FPS==1s�Ȃ̂�
	if (mSubTimer >= 60.f)
	{
		mSubTimer = 0.f;
		mMainTimer++;
	}

	//�ő厞�ԂƂȂ�����
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}



