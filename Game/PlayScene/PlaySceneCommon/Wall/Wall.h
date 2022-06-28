/*
壁クラス
作成者：杉山
作成日：2021/10/21
*/

#pragma once


//定数群
#include"WallConstant.h"

//前方宣言
#include"../ObjectModel/BoxModel.h"

class Wall
{
private:
	//変数

	//モデル描画クラス
	std::unique_ptr<BoxModel> mpWallModel;

public:
	//関数
	//コンストラクタ
	Wall();
	//デストラクタ
	~Wall();
	//初期化
	void Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 scale);

	//描画
	void Draw();

	//当たり判定を返す
	BoxModel* GetWallModel()const { return mpWallModel.get(); }
};