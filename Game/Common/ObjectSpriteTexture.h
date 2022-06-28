/*
�ړI�̏ꏊ�ɉ摜�𕽖ʕ`�悷��N���X
(�X�v���C�g�摜�͂�����)
�쐬�ҁF���R
�쐬���F2021/06/21
*/
#pragma once

//���N���X
#include"ITexture.h"

namespace DirectX
{
	class SpriteBatch;
}
class ObjectSpriteTexture:public ITexture
{
private:
	//�ϐ�============================

	//�؂�����W
	RECT mSrc;

	//�ۑ��p�X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;

	//�X�v���C�g�؂���P��
	DirectX::SimpleMath::Vector2 mSpriteSrc;

	//�֐�============================

public:
	//�R���X�g���N�^
	ObjectSpriteTexture(const RECT& src = {0,0,0,0},					//�؂�����W
		const DirectX::SimpleMath::Vector2& position = { 0.f,0.f },			//�\�����W						
		const DirectX::SimpleMath::Vector2& scale = { 1.f,1.f },		//�\���g�嗦											
		const float& rot = 0.f,										//��]					
		const float& alpha = 1.f);										//�����x	
										


	//�f�X�g���N�^
	~ObjectSpriteTexture();

	//������
	void Initialize()override;

	//�`��
	void Draw()override;

	//�؂���ʒu�ύX����
	void SetRect(const RECT& rect) { mSrc = rect; }

	//�w��̕��������ɉ摜���ړ�������
	void Beside(const float& size,const int& shiftnum)
	{
		mSrc.right += static_cast<LONG>(size* shiftnum);
		mSrc.left += static_cast<LONG>(size * shiftnum);
	}
};