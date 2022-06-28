/*
�V�[���C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

#include "StepTimer.h"
#include "GameMain.h"


class IScene
{
public:

	virtual ~IScene() = default;

	// ������
	virtual void Initialize() = 0;

	// �X�V
	virtual eGameScene Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// �I������
	virtual void Finalize() = 0;

protected:
	//BGM�𗬂�
	virtual void PlayBGM() = 0;

	//BGM���~�߂�
	virtual void StopBGM() = 0;
};