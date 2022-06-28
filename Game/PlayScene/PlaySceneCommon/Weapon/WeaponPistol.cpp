/*
ピストルクラス
作成者：杉山
作成日：2021/10/14
*/
#include"pch.h"
#include"WeaponPistol.h"


//関数の使用
#include"../Bullet/BulletManager.h"
#include"../ObjectModel/ObjectModel.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//モデルの拡大率
const DirectX::SimpleMath::Vector3 WeaponPistol::PISTOL_MODEL_SCALE(1.5f,1.5f,1.5f);

//発射位置の調整
const DirectX::SimpleMath::Vector3 WeaponPistol::PISTOL_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//購入額
const int WeaponPistol::PISTOL_PRICE = 1000;

//購入時の総弾数
const int WeaponPistol::PISTOL_MAX_BULLET_NUM = 21;

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponPistol::WeaponPistol()
	: 
	WeaponBase()
{
}

/*===================================
デストラクタ
===================================*/
WeaponPistol::~WeaponPistol()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponPistol::Initialize()
{
	//モデルの初期設定
	this->ModelInit();

	//リセット処理
	this->Reset();
}

/*===================================
リセット処理
引数：なし
返り値：なし
===================================*/
void WeaponPistol::Reset()
{
	WeaponBase::SetBulletNum(PISTOL_MAX_BULLET_NUM);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponPistol::Draw()
{
	//モデルを描画する
	WeaponBase::GetWeaponModel()->Draw();
}

/*==================================
弾発射処理
引数：なし
返り値：なし
===================================*/
void WeaponPistol::Shot()
{
	//サウンド再生情報を取得する
	ADX2& pSound = ADX2::GetInstance();

	//弾を生成する
	bool shotFlag= WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + PISTOL_SHOT_SHIFT_POSITION
	);

	//無事発射できれば
	if (shotFlag)
	{
		//弾数を減らす
		WeaponBase::ReduceBulletNum();

		pSound.Play(CRI_CUESHEET_0_SE_SHOT_PISTOL);

	}

}

/*===================================
モデルの初期設定:private
引数：なし
返り値：なし
===================================*/
void WeaponPistol::ModelInit()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__PISTOL));

	//モデルの設定
	WeaponBase::GetWeaponModel()->SetModel(model);
	

	//モデルの拡大率
	WeaponBase::GetWeaponModel()->SetScale(PISTOL_MODEL_SCALE);
}




