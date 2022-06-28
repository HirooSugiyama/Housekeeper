/*
機関銃クラス
作成者：杉山
作成日：2021/10/14
*/
#include"pch.h"
#include"WeaponMachineGun.h"


//関数の使用
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"

#include"../Bullet/BulletType.h"


//モデルの拡大率
const DirectX::SimpleMath::Vector3 WeaponMachineGun::MACHINEGUN_MODEL_SCALE(1.5f,1.5f,1.5f);

//発射位置の調整
const DirectX::SimpleMath::Vector3 WeaponMachineGun::MACHINEGUN_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//購入額
const int WeaponMachineGun::MACHINEGUN_PRICE = 1500;

//購入時の総弾数
const int WeaponMachineGun::MACHINEGUN_MAX_BULLET_NUM = 120;

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponMachineGun::WeaponMachineGun()
	:
	WeaponBase()
{
}

/*===================================
デストラクタ
===================================*/
WeaponMachineGun::~WeaponMachineGun()
{

}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponMachineGun::Initialize()
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
void WeaponMachineGun::Reset()
{
	//総弾数の初期化
	WeaponBase::SetBulletNum(MACHINEGUN_MAX_BULLET_NUM);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponMachineGun::Draw()
{
	//モデルを描画する
	WeaponBase::GetWeaponModel()->Draw();
}

/*===================================
弾発射処理
引数：なし
返り値：なし
===================================*/
void WeaponMachineGun::Shot()
{
	//弾を生成する
	bool shotFlag = WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + MACHINEGUN_SHOT_SHIFT_POSITION
	);

	//無事発射できれば
	if (shotFlag)
	{
		//弾数を減らす
		WeaponBase::ReduceBulletNum();
	}
}


/*===================================
モデルの初期設定:private
引数：なし
返り値：なし
===================================*/
void WeaponMachineGun::ModelInit()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__MACHINEGUN));

	//モデルの設定
	WeaponBase::GetWeaponModel()->SetModel(model);
	
	//モデルの拡大率
	WeaponBase::GetWeaponModel()->SetScale(MACHINEGUN_MODEL_SCALE);
}