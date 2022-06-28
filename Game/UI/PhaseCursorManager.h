/*
フェーズが始まるタイミングを示すカーソルの描画を行うクラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once

//前方宣言
#include"PhaseCursor.h"

class PhaseCursorManager
{
private:

	//取得座標のずらす量
	static const float PHASECURSOR_SHIFT_POSITION;

	//変数
	std::vector<std::unique_ptr<PhaseCursor>> mpPhaseCursor;

public:

	//コンストラクタ
	PhaseCursorManager();
	//デストラクタ
	~PhaseCursorManager();
	//初期化処理
	void Initialize(const int& phasemaxnum);
	//描画処理
	void Draw();

	//描画する座標を決める
	void SetDrawPosition(const DirectX::SimpleMath::Vector2& startpos,const float& movepos);

};
