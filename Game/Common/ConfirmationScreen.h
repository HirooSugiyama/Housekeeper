/*
�m�F���
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

//�O���錾
#include"../Common/ObjectTexture.h"
#include"../Common/Cursor.h"
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"

class ConfirmationScreen
{
private:

	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_INIT_POSITION;

	//�����`��
	//���ʏ���
	//�g�嗦
	static const float STRING_SCALE;
	//YES
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_YES_POSITION;
	//No
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_NO_POSITION;

	//�m�F��ʗp�J�[�\���̊�{���
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_INIT_POSITION;
	//�ړ���
	static const float CONFI_CURSOR_SHIFT;

	//�����e�N�X�`��
	//�g�嗦
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_SCALE;
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_POSITION;

	//�A�������h�~����
	static const int CONTINUITY_STOP_TIME;

	//�摜
	std::unique_ptr<ObjectTexture> mpConfirTexture;

	//�I���J�[�\��
	std::unique_ptr<Cursor> mpCursor;

	//���ݑI�����Ă���I����
	bool mSelectFlag;

	//�����e�N�X�`��
	std::unique_ptr<ObjectTexture> mpStringTexture;

	//�A�������h�~�̃^�C�}�[
	std::unique_ptr<Timer> mpTimer;


public:

	//�R���X�g���N�^
	ConfirmationScreen();
	//�f�X�g���N�^
	~ConfirmationScreen();
	//����������
	void Initialize(const int& stringTexturekey);

	//���Z�b�g����
	void Reset();

	//�X�V����
	bool Update();
	//�`�揈��
	void Draw(const bool& blinkingFlag);


	//�I���t���O�̃A�N�Z�T
	bool GetSelectFlag() const { return mSelectFlag; }


private:

	//�����̕`��
	void DrawString(const bool& blinkingFlag);


};

