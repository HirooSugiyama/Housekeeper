/*
ハリボテの針葉樹のモデルを管理するクラス
作成者：杉山
作成日：2021/08/19
*/
#pragma once

//基底クラス
#include"IGroundObject.h"

//所持
#include"../ObjectModel/ObjectModel.h"


class GroundObjectConiferGroup :public IGroundObject
{
private:

	//モデルの拡大率
	static const DirectX::SimpleMath::Vector3 CONIFER_SCALE;

	//針葉樹グループモデルのY座標
	static const float CONIFER_MODEL_POSITION_Y;

	//針葉樹グループモデル
	std::unique_ptr<ObjectModel> mpConiferModel;


public:
	//コンストラクタ
	GroundObjectConiferGroup();

	//デストラクタ
	~GroundObjectConiferGroup()override;
	//初期化
	void Initialize()override;

	void Update()override {}

	//描画
	void Draw()override;

	//モデルの座標を設定する
	void SetConiferModelPosition(const DirectX::SimpleMath::Vector3& position);

	//Y座標を変換する
	float GetConiferModelPositionY() const { return CONIFER_MODEL_POSITION_Y; };

	//拡大率を取得
	DirectX::SimpleMath::Vector3 GetConiferScale()const { return CONIFER_SCALE; }

};