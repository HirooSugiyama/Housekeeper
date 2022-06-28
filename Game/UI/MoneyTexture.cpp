/*
����������̕`��摜�Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include"pch.h"
#include"MoneyTexture.h"

//���݂̏������̎擾
#include"Game/Money/Money.h"
//�摜�̍��W
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEYTEXTURE_POSITION(1000.f,0.f);

//�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEYTEXTURE_SCALE(1.3f,1.3f);

//���ۂ̒l�̕`��
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEY_NUM_POSITION =
	UI_MONEYTEXTURE_POSITION + DirectX::SimpleMath::Vector2(230, 8.f);

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
MoneyTexture::MoneyTexture()
	:
	mpTexture(),
	mpSpriteTexture(nullptr)
{
	mpTexture = std::make_unique<ObjectTexture>();
	mpSpriteTexture = std::make_unique<SpriteNumber2D>();
}

/*===================================
�f�X�g���N�^
===================================*/
MoneyTexture::~MoneyTexture()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void MoneyTexture::Initialize()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model=pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__MONEYGAUGE));

	//�摜�̐ݒ�
	mpTexture->SetTexture(model);
	mpTexture->Initialize();

	//���W�̐ݒ�
	mpTexture->SetPosition(UI_MONEYTEXTURE_POSITION);

	//�g�嗦�̐ݒ�
	mpTexture->SetScale(UI_MONEYTEXTURE_SCALE);

	//�����摜�̏���������
	mpSpriteTexture->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING));
	mpSpriteTexture->Initialize();
}


/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void MoneyTexture::Draw()
{
	//�摜�̕`��
	mpTexture->Draw();

	//�������̕`��
	auto& pM = Money::GetMoneyInstance();

	mpSpriteTexture->Create(pM.GetMoney(), UI_MONEY_NUM_POSITION);
	mpSpriteTexture->Draw();
}