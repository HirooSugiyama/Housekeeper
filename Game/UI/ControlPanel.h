/*
������@�`��UI
�쐬�ҁF���R
�쐬���F2022/01/30
*/
#pragma once

#include"Game/Common/ObjectSpriteTexture.h"

class ControlPanel
{
private:

	//�ړ�
	std::unique_ptr<ObjectSpriteTexture> mpMove;
	//�U��
	std::unique_ptr<ObjectSpriteTexture> mpAttack;
	//�؂�ւ�
	std::unique_ptr<ObjectSpriteTexture> mpChange;
	//�|�[�Y
	std::unique_ptr<ObjectSpriteTexture> mpPause;
	//���X�^�[�g
	std::unique_ptr<ObjectSpriteTexture> mpReStart;

	//�`��t���O
	bool mDrawFlag;


public:

	//�R���X�g���N�^
	ControlPanel();
	//�f�X�g���N�^
	~ControlPanel();
	//����������
	void Initialize();
	//�`�揈��
	void Draw();

	//�Q�[���p�b�h�ƃL�[��؂�ւ�
	void ChangeControl();

	//�`��t���O�̃A�N�Z�T
	void SetDrawFlag(const bool& flag) { mDrawFlag = flag; }
	bool GetDrawFlag()const { return mDrawFlag; }

};
