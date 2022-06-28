/*
リザルトで描画する文字の定数群
作成者：杉山
作成日：2021/10/22
*/
#pragma once




struct ResultDrawStringConstant
{
	//各文字の座標
	static const DirectX::SimpleMath::Vector2 STRING_RESULT_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_CLEARBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_MONEYBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_DEFEATBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_SCORE_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_SCORERANKING_POSITION;
	//各種文字の移動座標
	static const float STRING_DISTANCE;
	//移動速度
	static const float STRING_VELOCITY;

	//スコアランキングの記憶領域
	static const int SCORE_RANKING_STORAGE = 5;

	//ハイスコア描画位置
	static const DirectX::SimpleMath::Vector2 SCORE_RANKING_STRING_POSITION;
	static const DirectX::SimpleMath::Vector2 SCORE_RANKING_NUM_POSITION;
	//移動幅
	static const float SCORE_RANKING_SHIFT;

	//文字から値への移動座標
	static const DirectX::SimpleMath::Vector2 STRING_NUM_SHIFT;
};