/*
ピストルクラス
作成者：杉山
作成日：2021/10/14
*/
#pragma once

//基底クラス
#include"WeaponBase.h"


class WeaponPistol:public WeaponBase
{
private:

	//モデルの拡大率
	static const DirectX::SimpleMath::Vector3 PISTOL_MODEL_SCALE;

	//発射位置の調整
	static const DirectX::SimpleMath::Vector3 PISTOL_SHOT_SHIFT_POSITION;

	//購入額
	static const int PISTOL_PRICE;

	//購入時の総弾数
	static const int PISTOL_MAX_BULLET_NUM;

public:

	//コンストラクタ
	WeaponPistol();
	//デストラクタ
	~WeaponPistol()override;
	//初期化処理
	void Initialize()override;
	//リセット処理
	void Reset()override;
	//描画処理
	void Draw()override;
	//弾発射処理
	void Shot()override;
	//購入額を返す
	int GetWeaponPrice()const override { return PISTOL_PRICE; }

private:
	//モデルの初期設定
	void ModelInit();
};
