/*
�|�[�Y
�쐬�ҁF���R
�쐬���F2021/09/30
*/
#pragma once


//����
#include"../../Common/ObjectTexture.h"
#include"../../Common/Cursor.h"

class PlayScene;
class UI;

class Pause 
{
private:

	//���݂̏��
	enum class SelectState:int
	{
		CONFIG_CONTROL,
		KEEP,
		RETRY,
		TO_STAGE_SELECT,
		NONE
	};

	//�m�F��ʗp�J�[�\���̊�{���
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_INIT_POSITION;
	//�ړ���
	static const float SELECT_CURSOR_SHIFT;

	//�����`��ʒu
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_ON_POS;
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_SLASH_POS;
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_OFF_POS;

	//�ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;
	UI* mpUI;

	//UI�܂Ƃ߉摜
	std::unique_ptr<ObjectTexture> mpTexture;
	//�J�[�\��
	std::unique_ptr<Cursor> mpCursor;

	//���݂̏��
	int mState;

	//UI�`��t���O
	bool mControlUIDrawFlag;

public:
	//�R���X�g���N�^
	Pause();

	//�f�X�g���N�^
	~Pause();
	
	//������
	void Initialize(PlayScene* pPlayScene,UI* pUI);

	//�X�V
	bool Update();

	//�`��
	void Draw();

private:
	//�J�[�\���ړ�
	void MoveCursor();

	//���s
	SelectState Execution();

	//UI�`�揈��
	void UpdateControlUI();

	//����UI�̕����`��
	void DrawControlUIString();

};