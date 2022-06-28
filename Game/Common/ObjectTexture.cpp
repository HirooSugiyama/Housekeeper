/*
�ړI�̏ꏊ�ɉ摜�𕽖ʕ`�悷��N���X
(�P��摜�͂�����)
�쐬�ҁF���R
�쐬���F2021/06/05
*/
#include "pch.h"
#include "ObjectTexture.h"

/*=======================================
�R���X�g���N�^
�����F	position(���W)�Ascale(�g�嗦)
		rot(��]��)�Aalpha(�����x)
=======================================*/
ObjectTexture::ObjectTexture(
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const float& rot, const float& alpha)
	:
	ITexture(position, scale,rot,alpha),
	mColor{ DirectX::SimpleMath::Vector4::One},
	mpSpriteBatch(nullptr)
{
	mColor.w = ITexture::GetAlpha();
}

/*=========================
�f�X�g���N�^
=========================*/
ObjectTexture::~ObjectTexture()
{
}

/*=========================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void ObjectTexture::Initialize()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	
	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*========================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void ObjectTexture::Draw()
{
	//���l��ݒ肷��
	mColor.w = ITexture::GetAlpha();

	//�`��
	mpSpriteBatch->Draw(ITexture::GetTexture(),
		ITexture::GetPosition(),
		nullptr,
		mColor,
		ITexture::GetRot(),
		DirectX::SimpleMath::Vector2::One,
		ITexture::GetScale());
}
