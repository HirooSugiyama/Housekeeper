/*
�ړI�̏ꏊ�ɃX�v���C�g�摜�𕽖ʕ`�悷��N���X
(�X�v���C�g�摜�͂�����)
�쐬�ҁF���R
�쐬���F2021/06/21
*/
#include "pch.h"
#include "ObjectSpriteTexture.h"

/*=========================================================================
�R���X�g���N�^
�����Fsrc(�؂�����W)�Amaxsize(�摜�����ő�T�C�Y)�Aposition(�`����W)
		scale(�g�嗦)�Arot(��]��)�Aalpha(�����x)
=========================================================================*/
ObjectSpriteTexture::ObjectSpriteTexture(const RECT& src,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const float& rot, const float& alpha)
	:
	ITexture(position,scale,rot,alpha),
	mSrc(src),
	mpSpriteBatch(),
	mSpriteSrc()
{
	//�T�C�Y�Z�o
	mSpriteSrc.x = static_cast<float>(src.right - src.left);
	mSpriteSrc.y = static_cast<float>(src.bottom - src.top);
}

/*=========================
�f�X�g���N�^
=========================*/
ObjectSpriteTexture::~ObjectSpriteTexture()
{
}

/*=====================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ObjectSpriteTexture::Initialize()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*=========================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void ObjectSpriteTexture::Draw()
{
	//�F(�����x�̎w��)
	DirectX::SimpleMath::Vector4 color{ DirectX::SimpleMath::Vector4::One};
	color.w = ITexture::GetAlpha();
	//�����l�̎w��
	DirectX::SimpleMath::Vector2 center{ DirectX::SimpleMath::Vector2::Zero };

	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();


	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
	//�`��
	mpSpriteBatch->Draw
	(
		ITexture::GetTexture(),
		ITexture::GetPosition(),
		&mSrc,
		color,
		ITexture::GetRot(),
		center,
		ITexture::GetScale()
	);

}