/*
リザルトで描画する文字の定数群
作成者：杉山
作成日：2021/10/22
*/

#include"pch.h"
#include"ResultDrawStringConstant.h"



//各文字の座標
const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_RESULT_POSITION(20.f,15.f);

const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_CLEARBONUS_POSITION(80.f,120.f);

const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_MONEYBONUS_POSITION(80.f,260.f);

const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_DEFEATBONUS_POSITION(80.f,370.f);

const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_SCORE_POSITION(80.f,520.f);

const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_SCORERANKING_POSITION(650.f,80.f);


//各種文字の移動座標
const float ResultDrawStringConstant::STRING_DISTANCE = 650.f;
//移動速度
const float ResultDrawStringConstant::STRING_VELOCITY = 35.f;

//ハイスコア描画位置
const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::SCORE_RANKING_STRING_POSITION(730.f,175.f);
const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::SCORE_RANKING_NUM_POSITION =
	SCORE_RANKING_STRING_POSITION + DirectX::SimpleMath::Vector2(100.f, 10.f);

//移動幅
const float ResultDrawStringConstant::SCORE_RANKING_SHIFT = 120.f;

//文字から値への移動座標
const DirectX::SimpleMath::Vector2 ResultDrawStringConstant::STRING_NUM_SHIFT(100.f, 90.f);

