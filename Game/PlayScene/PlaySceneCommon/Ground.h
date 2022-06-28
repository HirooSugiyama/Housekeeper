/*
地面のクラス
作成者：杉山
作成日：2021/06/28
*/
#pragma once


//所持
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class Ground
{
private:
	//定数
	//地面の中心座標
	static const DirectX::SimpleMath::Vector3 GROUND_POSITION;
	//地面の拡大率
	static const DirectX::SimpleMath::Vector3 GROUND_SCALE;

	//変数
	//モデル描画クラス
	std::unique_ptr<ObjectModel> mpGroundModel;

public:
		//関数
	//コンストラクタ
	Ground();
	//デストラクタ
	~Ground();
	//初期化
	void Initialize();
	//描画
	void Draw();

};
