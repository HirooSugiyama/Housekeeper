/*
DirectXTK�̔ėp�����̃V���O���g����
�쐬�ҁF���R
������F2021/04/23
*/
#include<pch.h>


//�N���X�O���ŏ�����
std::unique_ptr <DirectXtkComponent> DirectXtkComponent::sDirectXtkComponent = nullptr;
std::unique_ptr<DirectX::CommonStates> DirectXtkComponent::spCommonState = nullptr;
std::unique_ptr<DirectX::SpriteBatch> DirectXtkComponent::spSpriteBatch = nullptr;
std::unique_ptr<DirectX::SpriteFont> DirectXtkComponent::spSpriteFont = nullptr;

/*=========================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
DirectXtkComponent::DirectXtkComponent()
	:
	spDevice(),
	spContext()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	spDevice = pDR->GetD3DDevice();
	spContext = pDR->GetD3DDeviceContext();

	spCommonState = std::make_unique<DirectX::CommonStates>(spDevice);
	
	spSpriteBatch = std::make_unique<DirectX::SpriteBatch>(spContext);
	
	spSpriteFont = std::make_unique<DirectX::SpriteFont>(spDevice, L"Resources/Fonts/SegoeUI_18.spritefont");
}
/*=========================================
�C���X�^���X�̎擾
�����F�Ȃ�
�Ԃ�l�F���g�̃C���X�^���X
=========================================*/
DirectXtkComponent& DirectXtkComponent::GetDirectXtkComponentInstance()
{
	if (sDirectXtkComponent == nullptr)
	{
		sDirectXtkComponent.reset(new DirectXtkComponent());
	}
	return *sDirectXtkComponent;
}

/*=========================================
�R�����X�e�[�g�̃Q�b�^�[
�����F�Ȃ�
�Ԃ�l�F�R�����X�e�[�g
=========================================*/
DirectX::CommonStates* DirectXtkComponent::GetCommonStates() const 
{
	return spCommonState.get();
}
/*=========================================
�X�v���C�g�o�b�`�̎擾
�����F�Ȃ�
�Ԃ�l�F�X�v���C�g�o�b�`
=========================================*/
DirectX::SpriteBatch* DirectXtkComponent::GetSpriteBatch() const 
{
	return spSpriteBatch.get();
}
/*=========================================
�X�v���C�g�t�H���g�̎擾
�����F�Ȃ�
�Ԃ�l�F�X�v���C�g�t�H���g
=========================================*/
DirectX::SpriteFont* DirectXtkComponent::GetSpriteFont()const 
{
	return spSpriteFont.get();
}