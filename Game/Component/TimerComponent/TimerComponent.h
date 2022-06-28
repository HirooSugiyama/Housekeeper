/*
�^�C�}�[���Ǘ�����C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/14
*/
#pragma once

class TimerComponent
{
private:

	//�������g
	static std::unique_ptr<TimerComponent> sTimerComponent;

	//�^�C�}�[
	DX::StepTimer mTimer;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	TimerComponent(const  TimerComponent& pv) = delete;
	TimerComponent operator=(const  TimerComponent& pv) = delete;

	//�R���X�g���N�^
	TimerComponent();
public:
	//���g�̃C���X�^���X
	static TimerComponent& GetTimerInstance();

	//�^�C�}�[�̃A�N�Z�T
	DX::StepTimer GetTimer() const { return mTimer; }
	void SetTimer(const DX::StepTimer& timer) { mTimer = timer; }

};
