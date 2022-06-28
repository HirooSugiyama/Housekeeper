/*
爆弾クラス
作成者：杉山
作成日：2021/10/14
*/
#include"pch.h"
#include"WeaponBomb.h"

//関数の使用
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"

//前方宣言
#include"../Shadow.h"

//重力定数の使用
#include"../../PlaySceneDefence/Gravity.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//モデルの拡大率
const DirectX::SimpleMath::Vector3 WeaponBomb::BOMB_MODEL_SCALE(1.5f,1.5f,1.5f);

//発射位置の調整
const DirectX::SimpleMath::Vector3 WeaponBomb::BOMB_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//購入額
const int WeaponBomb::BOMB_PRICE = 200;

//購入時の総弾数
const int WeaponBomb::BOMB_MAX_BULLET_NUM = 5;


//初期速度
const float WeaponBomb::FIRST_VELOCITY = 0.3f;

//最初の高さ
const float WeaponBomb::FIRST_HEIGHT = 1.f;

//弾の速度
const float WeaponBomb::BULLET_VELOCITY = 0.05f;

//爆破する高さ
const float WeaponBomb::BOMB_MIN_HEIGHT = 1.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponBomb::WeaponBomb()
	:
	WeaponBase(),
	mpShadow()
{
	mpShadow = std::make_unique<Shadow>();
}

/*===================================
デストラクタ
===================================*/
WeaponBomb::~WeaponBomb()
{
}

/*=================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponBomb::Initialize()
{
	//モデルの初期設定
	this->ModelInit();

	mpShadow->Initialize();

	//画像を設定する
	mpShadow->SetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__AIM));

	mpShadow->SetScale(DirectX::SimpleMath::Vector2(BOMB_MODEL_SCALE.x,BOMB_MODEL_SCALE.z)/2.f);

	//リセット処理
	this->Reset();
}

/*===================================
リセット処理
引数：なし
返り値：なし
===================================*/
void WeaponBomb::Reset()
{
	WeaponBase::SetBulletNum(BOMB_MAX_BULLET_NUM);
}
/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponBomb::Draw()
{
	//モデルを描画する
	WeaponBase::GetWeaponModel()->Draw();
	//落下値を算出
	DirectX::SimpleMath::Vector3 fallpos = this->FallPoint();

	//影の描画
	mpShadow->Draw(fallpos);
}

/*===================================
弾発射処理
引数：なし
返り値：なし
===================================*/
void WeaponBomb::Shot()
{

	//サウンド再生情報を取得する
	ADX2& pSound = ADX2::GetInstance();

	//実際に弾を発射する処理
	bool shotFlag= WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + BOMB_SHOT_SHIFT_POSITION
	);


	//無事発射できれば
	if (shotFlag)
	{
		//弾数を減らす
		WeaponBase::ReduceBulletNum();

		pSound.Play(CRI_CUESHEET_0_SE_THROW_BOMB);
	}
}

/*===================================
モデルの初期設定:private
引数：なし
返り値：なし
===================================*/
void WeaponBomb::ModelInit()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__GRENADE));

	//モデルの設定
	WeaponBase::GetWeaponModel()->SetModel(model);

	//モデルの拡大率
	WeaponBase::GetWeaponModel()->SetScale(BOMB_MODEL_SCALE);
}

/*=================================
落下地点予測:private
引数：なし
返り値：落下する座標
===================================*/
DirectX::SimpleMath::Vector3 WeaponBomb::FallPoint()
{
	//返り値用変数の宣言
	DirectX::SimpleMath::Vector3 fallpos = 
		WeaponBase::GetWeaponModel() ->GetPosition() + BOMB_SHOT_SHIFT_POSITION;

	//速度
	float bulletVelocity = FIRST_VELOCITY;
	//高さ
	float bulletHeight = FIRST_HEIGHT;
	int i = 0;

	while (fallpos.y >= BOMB_MIN_HEIGHT)
	{
		bulletVelocity -= Gravity::mGravityConstant;
		bulletHeight += bulletVelocity;

		//代入用変数の宣言
		DirectX::SimpleMath::Vector3 movevel = DirectX::SimpleMath::Vector3(0.f, 0.f, -BULLET_VELOCITY);

		//座標へ反映
		fallpos += movevel;

		DirectX::SimpleMath::Vector3 position = fallpos;
		position.y = bulletHeight;

		fallpos = position;
		i++;
	}

	fallpos.y = BOMB_MIN_HEIGHT;

	return fallpos;
}
