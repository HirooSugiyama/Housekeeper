/*
���݂̃v���C���[�̍s����Ԃ�\��UI
�쐬�ҁF���R
�쐬���F2021/10/15
*/
#include"pch.h"
#include"PlayerActionInfo.h"


//���n�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_SCALE(1.f,1.f);
//���n�摜�̍��W
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_POSITION(840.f, 600.f);


//���n�摜�̈ړ���
const int PlayerActionInfo::UNDERTEXTURE_SHIFT = 125;


//�U����Ԃ̐؂���ʒu
const RECT PlayerActionInfo::ATTACK_ENEMY_RECT = RECT{ 0,0,165,36 };

//����摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SCALE(0.14f, 0.14f);
//����摜�̍��W
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_POSITION(1110.f, 620.f);
//��U���摜�̂��炷��
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SHIFT(125.f,0.f);

//����摜�̕����T�C�Y
const int PlayerActionInfo::PlayerActionInfo::WEAPON_SIZE = 500;


//����摜�̏����ʒu
const RECT PlayerActionInfo::WEAPON_INIT_RECT = RECT{ 0, 0, 500, 500 };

//�e���̕`��ʒu
const DirectX::SimpleMath::Vector2 PlayerActionInfo::BULLET_NUM_POSITION(1105.f, 630.f);

/*=================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
PlayerActionInfo::PlayerActionInfo()
	:
	mpGroundworkTexture(),
	mpSelectPlate(),
	mpWeaponSpriteTexture(nullptr),
	mpSpriteWeaponBulletNum(nullptr),
	mActionState(ePlayerActionState::BLOCK_CREATE),
	mPlayerWeapon(eWeaponType::NONE),
	mStrongWeaponBulletNum(0)
{
	mpGroundworkTexture = std::make_unique<ObjectTexture>();
	mpSelectPlate = std::make_unique<ObjectTexture>();

	mpWeaponSpriteTexture = std::make_unique<ObjectSpriteTexture>
	(
		ATTACK_ENEMY_RECT,
		WEAPON_TEX_POSITION,
		WEAPON_TEX_SCALE
	);

	mpSpriteWeaponBulletNum = std::make_unique<SpriteNumber2D>();
}

/*=================================
�f�X�g���N�^
===================================*/
PlayerActionInfo::~PlayerActionInfo()
{
}

/*==================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayerActionInfo::Initialize()
{
	//���\�[�X�̊m��
	ResourceManager *pRM = ResourceManager::GetInstance(); 
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__PLAYERSTATE));

	//����������
	mpGroundworkTexture->Initialize();
	mpGroundworkTexture->SetTexture(texture);
	mpGroundworkTexture->SetPosition(GROUNDWORK_TEX_POSITION);
	mpGroundworkTexture->SetScale(GROUNDWORK_TEX_SCALE);

	//�I�����Ă���s���̋������s���摜�̏���������
	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SELECTPLATE));
	mpSelectPlate->Initialize();
	mpSelectPlate->SetTexture(texture);
	mpSelectPlate->SetPosition(GROUNDWORK_TEX_POSITION);
	mpSelectPlate->SetScale(GROUNDWORK_TEX_SCALE);


	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONSPRITE));

	//����������
	mpWeaponSpriteTexture->Initialize();
	mpWeaponSpriteTexture->SetTexture(texture);

	mpSpriteWeaponBulletNum->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING));
	mpSpriteWeaponBulletNum->Initialize();
	mpSpriteWeaponBulletNum->SetAlign(eAlign::LEFT);
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayerActionInfo::Update()
{

}

/*=================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayerActionInfo::Draw()
{
	mpSelectPlate->Draw();
	mpGroundworkTexture->Draw();

	if (mActionState == ePlayerActionState::STRONG_WEWPON)
	{
		mpWeaponSpriteTexture->Draw();
		mpSpriteWeaponBulletNum->Create(mStrongWeaponBulletNum, BULLET_NUM_POSITION);
		mpSpriteWeaponBulletNum->Draw();
	}	
}

/*==================================
�؂���ʒu��؂�ւ���
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayerActionInfo::ChangeTexture()
{
	//�ϊ��p�ϐ��̐錾
	DirectX::SimpleMath::Vector2 position = GROUNDWORK_TEX_POSITION;
	//���݂̃v���C���[�̏�Ԃ����ăe�N�X�`����ݒ肷��
	switch (mActionState)
	{
		case ePlayerActionState::BLOCK_CREATE:
		{			
			break;
		}
		
		case ePlayerActionState::ATTACK_ENEMY:
		{
			//���n�摜���ړ�������
			position.x += UNDERTEXTURE_SHIFT;
			break;
		}
		case ePlayerActionState::STRONG_WEWPON:
		{
			//����摜�̐؂���ʒu������������
			mpWeaponSpriteTexture->SetRect(WEAPON_INIT_RECT);

			//�摜���ړ�������
			mpWeaponSpriteTexture->Beside(WEAPON_SIZE, static_cast<int>(mPlayerWeapon));

			//���n�摜���ړ�������
			position.x += UNDERTEXTURE_SHIFT + UNDERTEXTURE_SHIFT;
			mpWeaponSpriteTexture->SetPosition(WEAPON_TEX_POSITION);


			break;
		}

	}
	//���n�摜�̍��W�ݒ�
	mpSelectPlate->SetPosition(position);
}
