/*
スコア周りの描画クラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once


//所持
#include"../Common/SpriteNumber/SpriteNumber2D.h"
#include"../Common/ObjectTexture.h"

class ScoreRender
{
private:

	//スコアの描画位置
	static const DirectX::SimpleMath::Vector2 SCORE_NUM_POSITION;
	//スコアの文字画像の描画位置
	static const DirectX::SimpleMath::Vector2 SCORE_STRING_POSITION;

	//文字の拡大率
	static const float SCORE_NUM_SCALE;
	static const float SCORE_STRING_SCALE;


	//スコア描画
	std::unique_ptr<SpriteNumber2D> mpDrawScore;

	//文字画像
	std::unique_ptr<ObjectTexture> mpScoreStringTexture;

public:

	//コンストラクタ
	ScoreRender();
	//デストラクタ
	~ScoreRender();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw(int scoreNum);

};
