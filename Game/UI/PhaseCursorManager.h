/*
�t�F�[�Y���n�܂�^�C�~���O�������J�[�\���̕`����s���N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

//�O���錾
#include"PhaseCursor.h"

class PhaseCursorManager
{
private:

	//�擾���W�̂��炷��
	static const float PHASECURSOR_SHIFT_POSITION;

	//�ϐ�
	std::vector<std::unique_ptr<PhaseCursor>> mpPhaseCursor;

public:

	//�R���X�g���N�^
	PhaseCursorManager();
	//�f�X�g���N�^
	~PhaseCursorManager();
	//����������
	void Initialize(const int& phasemaxnum);
	//�`�揈��
	void Draw();

	//�`�悷����W�����߂�
	void SetDrawPosition(const DirectX::SimpleMath::Vector2& startpos,const float& movepos);

};
