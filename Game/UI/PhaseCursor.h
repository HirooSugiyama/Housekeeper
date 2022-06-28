/*
ひとつのフェーズの始まりのテクスチャを管理するクラス
作成者：杉山
作成日：2021/09/18
*/
#pragma once


//所持
#include"../Common/ObjectTexture.h"

class PhaseCursor
{
private:
	//画像の拡大率
	static const DirectX::SimpleMath::Vector2 PHASECURSOR_TEXTURE_SCALE;


	//ユニークポインタ
	std::unique_ptr<ObjectTexture> mpPhaseCursorTexture;

public:

	//コンストラクタ
	PhaseCursor();
	//デストラクタ
	~PhaseCursor();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector2& position);

};
