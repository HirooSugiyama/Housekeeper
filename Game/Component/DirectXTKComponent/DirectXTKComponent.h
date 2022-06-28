/*
DirectXTK�̔ėp�����̃V���O���g��
�쐬�ҁF���R
������F2021/04/23
*/
#pragma once


namespace DirectX 
{
	class CommonStates;
	class SpriteFont;
	class SpriteBatch;
}

class DirectXtkComponent final
{
private:
	//���g
	static std::unique_ptr <DirectXtkComponent> sDirectXtkComponent;
	
	//�R�����X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> spCommonState;
	// �X�v���C�g�o�b�`
	static std::unique_ptr<DirectX::SpriteBatch> spSpriteBatch;
	// �X�v���C�g�t�H���g
	static std::unique_ptr<DirectX::SpriteFont> spSpriteFont;



	//D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g
	ID3D11Device1* spDevice;
	ID3D11DeviceContext1* spContext;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete
	DirectXtkComponent(const DirectXtkComponent& dxtk) = delete;
	DirectXtkComponent operator=(const DirectXtkComponent& dxtk) = delete;

	//�R���X�g���N�^
	DirectXtkComponent();
public:

	//���g�̃C���X�^���X
	static DirectXtkComponent& GetDirectXtkComponentInstance();

	//�e�|�C���^�̃Q�b�^�[
	DirectX::CommonStates* GetCommonStates()const;
	DirectX::SpriteBatch* GetSpriteBatch()const;
	DirectX::SpriteFont* GetSpriteFont()const;

};