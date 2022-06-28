/*
ブーメランクラス
作成者：杉山
作成日：2021/10/14
*/
#include"pch.h"
#include"WeaponBoomerang.h"

//関数の使用
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"
#include"../Bullet/BulletStateBoomerang.h"


//モデルの拡大率
const DirectX::SimpleMath::Vector3 WeaponBoomerang::BOOMERANG_MODEL_SCALE(1.5f,1.5f,1.5f);

//発射位置の調整
const DirectX::SimpleMath::Vector3 WeaponBoomerang::BOOMERANG_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//購入額
const int WeaponBoomerang::BOOMERANG_PRICE = 1000;

//購入時の総弾数
const int WeaponBoomerang::BOOMERANG_MAX_BULLET_NUM = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponBoomerang::WeaponBoomerang()
	:
	WeaponBase(),
	mSecondFlag(false)
{
}

/*===================================
デストラクタ
===================================*/
WeaponBoomerang::~WeaponBoomerang()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponBoomerang::Initialize()
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
void WeaponBoomerang::Reset()
{
	//総弾数の初期化
	WeaponBase::SetBulletNum(BOOMERANG_MAX_BULLET_NUM);
}

/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponBoomerang::Draw()
{
	//まだ弾を表示していなかったら
	if (!mSecondFlag)
	{
		//モデルを描画する
		WeaponBase::GetWeaponModel()->Draw();
	}
}

/*===================================
弾発射処理
引数：なし
返り値：なし
===================================*/
void  WeaponBoomerang::Shot()
{

	//弾発射が1回目なら
	if (!mSecondFlag)
	{
		bool shotFlag = WeaponBase::GetBulletManager()->Create
		(
			WeaponBase::GetWeaponModel()->GetPosition() + BOOMERANG_SHOT_SHIFT_POSITION
		);
		//無事発射できれば
		if (shotFlag)
		{
			//次打つのは2回目
			mSecondFlag = true;

			//弾数を減らす
			WeaponBase::ReduceBulletNum();
		}
	}
	else if(WeaponBase::GetBulletManager()->GetBoomerangBullet()->
			GetBoomerangState()== eBoomerangState::CATCH)
	{
		//既にある弾を発射状態とする
		WeaponBase::GetBulletManager()->GetBoomerangBullet()->
			ChangeBoomerangState(eBoomerangState::NONE);


		//タイマーは起動する
		WeaponBase::GetBulletManager()->ResetIntervalTimer();

		//弾数を減らす
		WeaponBase::ReduceBulletNum();
	}
}

/*===================================
モデルの初期設定:private
引数：なし
返り値：なし
===================================*/
void WeaponBoomerang::ModelInit()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__BOOMERANG));

	//モデルの設定
	WeaponBase::GetWeaponModel()->SetModel(model);


	//モデルの拡大率
	WeaponBase::GetWeaponModel()->SetScale(BOOMERANG_MODEL_SCALE);
}

