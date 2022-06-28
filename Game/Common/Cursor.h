/*
�J�[�\�����Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/10/13
*/
#pragma once
//����
#include"../Common/ObjectTexture.h"

class Cursor
{
private:

	//�摜�Ǘ��ϐ�
	std::unique_ptr<ObjectTexture> mpCursorTexture;

	//�ړ����ۑ��p�ϐ�
	float mShiftNum;

	//�������W�ۑ��p�ϐ�
	DirectX::SimpleMath::Vector2 mSaveInitPosition;

public:

	//�R���X�g���N�^
	Cursor();
	//�f�X�g���N�^
	~Cursor();
	//����������
	void Initialize(
		const int& key,
		const DirectX::SimpleMath::Vector2& initPosition,
		const DirectX::SimpleMath::Vector2& scale,
		const float& shiftPosition,
		const float& rot=0.f);

	//�`�揈��
	void Draw(const bool& flag=true);

	//�J�[�\�������Ɉړ�����
	void CursorDown();

	//�J�[�\������Ɉړ�����
	void CursorUp();

	//�J�[�\���������ʒu�Ƀ��Z�b�g����
	void CursorReset();

	//�J�[�\������ԉ��ɃZ�b�g����
	void CursorSetUnder(const int& screenMaxStageNum);

};
