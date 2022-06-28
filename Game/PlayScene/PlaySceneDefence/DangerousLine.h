/*
警告線クラス
作成者：杉山
作成日：2021/10/06
*/
#pragma once

//所持
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class DangerousLine
{
private:
	//座標
	static const DirectX::SimpleMath::Vector3 ASSETLINE_MODEL_POSITION;
	//拡大率
	static const DirectX::SimpleMath::Vector3 ASSETLINE_MODEL_SCALE;

	//モデル情報
	std::unique_ptr<ObjectModel> mpAssertLineModel;

public:

	//コンストラクタ
	DangerousLine();
	//デストラクタ
	~DangerousLine();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw();

	//Z座標の取得(エフェクト発動基準座標)(関数の都合上CPPで処理)
	float GetLinePositionZ()const;
};
