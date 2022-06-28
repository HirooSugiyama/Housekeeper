/*
針葉樹のモデルを管理するクラス
作成者：杉山
作成日：2021/08/19
*/
#pragma once

//基底クラス
#include"IGroundObject.h"


#include"../ObjectModel/ObjectModel.h"

class GroundObjectShop :public IGroundObject
{
private:

	//ショップモデルの拡大率
	static const DirectX::SimpleMath::Vector3 SHOP_SCALE;

	//ショップモデルのY座標
	static const float SHOP_MODEL_POSITION_Y;

	//ショップモデル
	std::unique_ptr<ObjectModel> mpShopModel;


public:
	//コンストラクタ
	GroundObjectShop();

	//デストラクタ
	~GroundObjectShop()override;
	//初期化
	void Initialize()override;

	void Update()override {};

	//描画
	void Draw()override;

	//モデルの座標を設定する
	void SetShopModelPosition(const DirectX::SimpleMath::Vector3& position);

	//Y座標を返す
	float GetShopModelPositionY()const { return SHOP_MODEL_POSITION_Y; }

	//拡大率を取得
	DirectX::SimpleMath::Vector3 GetConiferScale() const { return SHOP_SCALE; }
};