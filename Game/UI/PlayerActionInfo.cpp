/*
現在のプレイヤーの行動状態を表すUI
作成者：杉山
作成日：2021/10/15
*/
#include"pch.h"
#include"PlayerActionInfo.h"


//下地画像の拡大率
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_SCALE(1.f,1.f);
//下地画像の座標
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_POSITION(840.f, 600.f);


//下地画像の移動幅
const int PlayerActionInfo::UNDERTEXTURE_SHIFT = 125;


//攻撃状態の切り取り位置
const RECT PlayerActionInfo::ATTACK_ENEMY_RECT = RECT{ 0,0,165,36 };

//武器画像の拡大率
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SCALE(0.14f, 0.14f);
//武器画像の座標
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_POSITION(1110.f, 620.f);
//弱攻撃画像のずらす幅
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SHIFT(125.f,0.f);

//武器画像の分割サイズ
const int PlayerActionInfo::PlayerActionInfo::WEAPON_SIZE = 500;


//武器画像の初期位置
const RECT PlayerActionInfo::WEAPON_INIT_RECT = RECT{ 0, 0, 500, 500 };

//弾数の描画位置
const DirectX::SimpleMath::Vector2 PlayerActionInfo::BULLET_NUM_POSITION(1105.f, 630.f);

/*=================================
コンストラクタ
引数：なし
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
デストラクタ
===================================*/
PlayerActionInfo::~PlayerActionInfo()
{
}

/*==================================
初期化処理
引数：なし
返り値：なし
===================================*/
void PlayerActionInfo::Initialize()
{
	//リソースの確保
	ResourceManager *pRM = ResourceManager::GetInstance(); 
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__PLAYERSTATE));

	//初期化処理
	mpGroundworkTexture->Initialize();
	mpGroundworkTexture->SetTexture(texture);
	mpGroundworkTexture->SetPosition(GROUNDWORK_TEX_POSITION);
	mpGroundworkTexture->SetScale(GROUNDWORK_TEX_SCALE);

	//選択している行動の強調を行う画像の初期化処理
	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SELECTPLATE));
	mpSelectPlate->Initialize();
	mpSelectPlate->SetTexture(texture);
	mpSelectPlate->SetPosition(GROUNDWORK_TEX_POSITION);
	mpSelectPlate->SetScale(GROUNDWORK_TEX_SCALE);


	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONSPRITE));

	//初期化処理
	mpWeaponSpriteTexture->Initialize();
	mpWeaponSpriteTexture->SetTexture(texture);

	mpSpriteWeaponBulletNum->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING));
	mpSpriteWeaponBulletNum->Initialize();
	mpSpriteWeaponBulletNum->SetAlign(eAlign::LEFT);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void PlayerActionInfo::Update()
{

}

/*=================================
描画処理
引数：なし
返り値：なし
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
切り取り位置を切り替える
引数：なし
返り値：なし
===================================*/
void PlayerActionInfo::ChangeTexture()
{
	//変換用変数の宣言
	DirectX::SimpleMath::Vector2 position = GROUNDWORK_TEX_POSITION;
	//現在のプレイヤーの状態を見てテクスチャを設定する
	switch (mActionState)
	{
		case ePlayerActionState::BLOCK_CREATE:
		{			
			break;
		}
		
		case ePlayerActionState::ATTACK_ENEMY:
		{
			//下地画像を移動させる
			position.x += UNDERTEXTURE_SHIFT;
			break;
		}
		case ePlayerActionState::STRONG_WEWPON:
		{
			//武器画像の切り取り位置を初期化する
			mpWeaponSpriteTexture->SetRect(WEAPON_INIT_RECT);

			//画像を移動させる
			mpWeaponSpriteTexture->Beside(WEAPON_SIZE, static_cast<int>(mPlayerWeapon));

			//下地画像を移動させる
			position.x += UNDERTEXTURE_SHIFT + UNDERTEXTURE_SHIFT;
			mpWeaponSpriteTexture->SetPosition(WEAPON_TEX_POSITION);


			break;
		}

	}
	//下地画像の座標設定
	mpSelectPlate->SetPosition(position);
}
