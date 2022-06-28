/*
���������摜�N���X
�쐬�ҁF���R
�쐬���F2021/12/17
*/
#pragma once

#include"CountNumber.h"
#include"../../Common/SpriteNumber/SpriteNumber2D.h"

//����

class MoveSpriteNumber2D
{
private:

	//���������N���X
	std::unique_ptr<CountNumber> mpCountNumber;

	//�����摜�N���X
	std::unique_ptr<SpriteNumber2D> mpSpriteNumber2D;

	//�`����W
	DirectX::SimpleMath::Vector2 mDrawPosition;

public:

	//�R���X�g���N�^
	MoveSpriteNumber2D();
	//�f�X�g���N�^
	~MoveSpriteNumber2D();
	//����������
	void Initialize(const int& textureKey,const int& firstNum,
						const float& moveSecondSpeed, const int& maxNum);
	//�X�V����
	int Update(const DX::StepTimer& timer);
	//�`�揈��
	void Draw();

	//���W���w��
	void SetPosition(DirectX::SimpleMath::Vector2 position) { mDrawPosition = position; }
	//�g�嗦�w��
	void SetScale(float scale) { mpSpriteNumber2D->SetScale(scale); }

	//���S�ʒu��ύX
	void SetAlign(eAlign algin) { mpSpriteNumber2D->SetAlign(algin); }

	//�l���ő�l�ɕύX����
	void ForcedChangeMoveNum() { mpCountNumber->ForcedChangeMoveNum(); }
};
