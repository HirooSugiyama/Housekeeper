/*
�X�e�[�W���x���̊Ŕ�
�쐬�ҁF���R
�쐬���F2022/03/12
*/
#pragma once

#include"Game/Common/ObjectTexture.h"

class StageLevelSignBoard
{
private:
	//�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 TEXTURE_SCALE;
	//�摜�̍��W
	static const DirectX::SimpleMath::Vector2 TEXTURE_POSITON;


	//�摜
	std::unique_ptr<ObjectTexture> mpSignBoard;

public:

	//�R���X�g���N�^
	StageLevelSignBoard();
	//�f�X�g���N�^
	~StageLevelSignBoard();
	//����������
	void Initialize();
	//�`�揈��
	void Draw();

};
