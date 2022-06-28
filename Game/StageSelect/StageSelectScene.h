/*
�X�e�[�W�I���V�[��
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once


#include "../IScene.h"
#include "Game/GameMain.h"

//�I�����������v���C�V�[����(�\���̂��g�p)
#include"Game/Component/SceneComponent/StoPSceneComponent.h"

//�񋓌^�̎g�p
#include"StageNumer.h"

//����
#include"../Common/Cursor.h"
#include"StageInfomation.h"
#include"StageNumberTag.h"
#include"../Common/ConfirmationScreen.h"
#include"../Common/Blinking.h"
#include"../Common/Cloud.h"
#include"../Common/ObjectTexture.h"
#include"StageLevelSignBoard.h"


class StageSelectScene : public IScene
{
private:

	//1��ʓ�����̍ő�X�e�[�W��
	static const int SCREEN_STEGE_MAX_NUM = 6;

	//�^�O�̏������W
	static const DirectX::SimpleMath::Vector2 TAG_INIT_POSITION;
	//��
	static const float TAG_SHIFT;

	//�m�F��ʗp�J�[�\���̊�{���
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_INIT_POSITION;
	//�ړ���
	static const float SELECT_CURSOR_SHIFT;

	//��̈ʒu
	static const DirectX::SimpleMath::Vector2 NAME_POSITION;
	static const DirectX::SimpleMath::Vector2 NAME_SCALE;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;

	//�J�[�\��
	std::unique_ptr<Cursor> mpCursor;

	//�X�e�[�W�e����
	std::unique_ptr<StageInfomation> mpStageInfo;

	//�^�O
	std::unique_ptr<StageNumberTag> mpTag[SCREEN_STEGE_MAX_NUM];

	//�m�F���
	std::unique_ptr<ConfirmationScreen> mpConfirmationScreen;

	//�_��
	std::unique_ptr<Blinking> mpTextureBlinking;

	//��
	std::unique_ptr<ObjectTexture> mpStageSelectNameTexture;

	//�_
	std::unique_ptr<Cloud> mpCloud;

	//�Ŕ�
	std::unique_ptr<StageLevelSignBoard> mpSignBoard;

	//���ݑI�𒆂̔ԍ�
	int mSelectNum;

	//�I���t���O
	bool mSelectFlag;

	//BGM��ID
	int mBGMID;

	//�I���ł���ő�X�e�[�W�ԍ�
	int mMaxSelectStageNumber;

public:

	// �R���X�g���N�^
	StageSelectScene();

	// �f�X�g���N�^
	~StageSelectScene();

	// ������
	void Initialize() override;

	// �X�V
	eGameScene Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:
	//���[�h�I��
	void StageSelect();

	//�t�@�C�����Z�o
	std::string SetFileName();

	//�J�[�\����������
	void CursorUp();

	//�J�[�\����������
	void CursorDown();


	//�ԍ���ݒ肷��
	void SetNumberTag();

	//�X�e�[�W�ԍ��擾
	int GetFirstSelectStageNum();


	//BGM�𗬂�
	void PlayBGM()override;

	//BGM���~�߂�
	void StopBGM()override;

};