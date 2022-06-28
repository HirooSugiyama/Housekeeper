/*
機関銃クラス
作成者：杉山
作成日：2021/09/06
*/
#pragma once

//基底クラス
#include"WeaponBase.h"


class WeaponMachineGun:public WeaponBase
{
private:

	//モデルの拡大率
	static const DirectX::SimpleMath::Vector3 MACHINEGUN_MODEL_SCALE;

	//発射位置の調整
	static const DirectX::SimpleMath::Vector3 MACHINEGUN_SHOT_SHIFT_POSITION;

	//購入額
	static const int MACHINEGUN_PRICE;

	//購入時の総弾数
	static const int MACHINEGUN_MAX_BULLET_NUM;


public:

	//コンストラクタ
	WeaponMachineGun();
	//デストラクタ
	~WeaponMachineGun()override;
	//初期化処理
	void Initialize()override;
	//リセット処理
	void Reset()override;
	//描画処理
	void Draw()override;
	//弾発射処理
	void Shot()override;
	//購入額を返す
	int GetWeaponPrice()const override { return MACHINEGUN_PRICE; }

private:
	//モデルの初期設定
	void ModelInit();
};
