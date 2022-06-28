/*
現在の敵の数を描画するクラス
作成者：杉山
作成日：2021/12/11
*/
#pragma once

#include"../Common/ObjectTexture.h"
#include"../Common/SpriteNumber/SpriteNumber2D.h"

class DefeatEnemyRender
{
private:
	//背景画像の座標
	static const DirectX::SimpleMath::Vector2 TEX_POSITION;
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//現在の敵の数の文字画像の座標
	static const DirectX::SimpleMath::Vector2 CURRENT_NUM_POSITION;
	static const float CURRENT_NUM_SCALE;

	//敵の最大数の画像の座標
	static const DirectX::SimpleMath::Vector2 OVERALL_NUM_POSITION;
	static const float OVERALL_NUM_SCALE;


	//背景画像
	std::unique_ptr<ObjectTexture> mpDefeatEnemyTexture;

	//現在の敵の数
	std::unique_ptr<SpriteNumber2D> mpCurrentEnemyNum;
	//全体の敵の数
	std::unique_ptr<SpriteNumber2D> mpOverallEnemyNum;

public:

	//コンストラクタ
	DefeatEnemyRender();
	//デストラクタ
	~DefeatEnemyRender();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw(int currentNum,int overallNum);

};
