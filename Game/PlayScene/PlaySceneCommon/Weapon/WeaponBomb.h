/*
爆弾クラス
作成者：杉山
作成日：2021/10/14
*/
#pragma once

//基底クラス
#include"WeaponBase.h"

//所持
#include"../FlatPolygon.h"

class WeaponBomb:public WeaponBase
{
private:

	//モデルの拡大率
	static const DirectX::SimpleMath::Vector3 BOMB_MODEL_SCALE;

	//発射位置の調整
	static const DirectX::SimpleMath::Vector3 BOMB_SHOT_SHIFT_POSITION;

	//購入額
	static const int BOMB_PRICE;

	//購入時の総弾数
	static const int BOMB_MAX_BULLET_NUM;

	//初期速度
	static const float FIRST_VELOCITY;

	//最初の高さ
	static const float FIRST_HEIGHT;

	//弾の速度
	static const float BULLET_VELOCITY;

	//爆破する高さ
	static const float BOMB_MIN_HEIGHT;

	//影
	std::unique_ptr<FlatPolygon> mpShadow;

public:

	//コンストラクタ
	WeaponBomb();
	//デストラクタ
	~WeaponBomb()override;
	//初期化処理
	void Initialize()override;
	//リセット処理
	void Reset()override;
	//描画処理
	void Draw()override;
	//弾発射処理
	void Shot()override;
	//購入額を返す
	int GetWeaponPrice()const override  { return BOMB_PRICE; }

private:
	//モデルの初期設定
	void ModelInit();

	//落下地点予測
	DirectX::SimpleMath::Vector3 FallPoint();
};
