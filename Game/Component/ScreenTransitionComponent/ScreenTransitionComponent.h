
/*
��ʑJ�ڊǗ��N���X(Singleton)
�쐬�ҁF���R
�쐬���F2021/12/28
*/
#pragma once
#include "Libraries/MyLibraries/Wipe.h"
#include "Libraries/MyLibraries/Fade.h"

#include"../../Common/ObjectTexture.h"

class ScreenTransitionComponent
{
private:
	//�������g
	static std::unique_ptr <ScreenTransitionComponent> sTransitionInterface;

	//���C�v
	std::unique_ptr<Wipe> mpWipe;
	//�g�p�t���O
	bool mWipeUseFlag;

	//�t�F�[�h
	std::unique_ptr<Fade> mpFade;
	//�g�p�t���O
	bool mFadeUseFlag;


	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	ScreenTransitionComponent(const ScreenTransitionComponent& sti) = delete;
	ScreenTransitionComponent operator=(const ScreenTransitionComponent& sti) = delete;

	//�R���X�g���N�^
	ScreenTransitionComponent();

public:
	//��������
	static ScreenTransitionComponent& GetScreenTransitionInstance();

	//���C�v�̎擾
	Wipe* GetWipe()const { return mpWipe.get(); }
	//�g�p�t���O�̃A�N�Z�T
	bool GetWipeUseFlag() const { return mWipeUseFlag; }
	void SetWipeUseFlag(bool flag) { mWipeUseFlag = flag; }

	//�t�F�[�h�̎擾
	Fade* GetFade()const { return mpFade.get(); }
	//�g�p�t���O�̃A�N�Z�T
	bool GetFadeUseFlag()const { return mFadeUseFlag; }
	void SetFadeUseFlag(bool flag) { mFadeUseFlag = flag; }

};
