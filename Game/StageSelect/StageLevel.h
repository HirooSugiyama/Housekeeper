/*
ステージのレベル描画クラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once

//前方宣言
#include"../Common/ObjectTexture.h"


class StageLevel
{
private:
	//ステージ最大レベル
	static const int STAGE_MAX_LEVELOCITY = 6;

	//画像初期座標
	static const DirectX::SimpleMath::Vector2 STAGELEVELOCITY_TEXTURE_INIT_POSITION;
	//画像拡大率
	static const DirectX::SimpleMath::Vector2 STAGELEVELOCITY_TEXTURE_SCALE;
	//画像をずらす幅
	static const float STAGELEVELOCITY_SHIFT_POSITION_X;

	//画像クラス
	std::unique_ptr<ObjectTexture> mpStarTexture[STAGE_MAX_LEVELOCITY];

public:

	//コンストラクタ
	StageLevel();
	//デストラクタ
	~StageLevel();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw(const int& stagelevel);

};
