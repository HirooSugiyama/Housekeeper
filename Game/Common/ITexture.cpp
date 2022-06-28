/*
�摜�Ǘ��N���X�̃C���^�[�t�F�[�X�N���X
�쐬�ҁF���R
�쐬���F2021/12/01
*/

#include"pch.h"
#include"ITexture.h"

/*===============================================
�R���X�g���N�^
�����F���W�A�g�嗦�A��]���A�����x
===============================================*/
ITexture::ITexture(const DirectX::SimpleMath::Vector2& position,
				const DirectX::SimpleMath::Vector2& scale,
				const float& rot, const float& alpha)
	:
	mPosition(position),
	mScale(scale),
	mRot(rot),
	mAlpha(alpha),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}
