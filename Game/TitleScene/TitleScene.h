/*
�^�C�g���V�[��
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

//����
#include"Game/Common/Cloud.h"
#include"Game/Common/ObjectSpriteTexture.h"

class TitleScene : public IScene
{
private:

	//�^�C�g���o�[�����؂���ʒu
	static const RECT TITLE_BAR_INIT_RECT;

	//���S�̍��W
	static const DirectX::SimpleMath::Vector2 TITLE_LOGO_POSITION;
	//�J�n�{�^���ʒu
	static const DirectX::SimpleMath::Vector2 TITLE_START_BAR_POSITION;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpLogo;

	std::unique_ptr<Cloud> mpCloud;

	std::unique_ptr<ObjectSpriteTexture> mpTitleBar;

	//���yID
	int mBGMID;

public:

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

	// ������
	void Initialize() override;

	// �X�V
	eGameScene Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:
	//�Q�[���p�b�h�ƃL�[��؂�ւ�
	void ChangeControl();

	//BGM�𗬂�
	void PlayBGM()override;

	//BGM���~�߂�
	void StopBGM()override;
};