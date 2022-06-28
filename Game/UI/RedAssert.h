/*
赤色点滅テクスチャ管理クラス
作成者：杉山
作成日：2021/10/07
*/
#pragma once

//前方宣言
#include"../Common/ObjectTexture.h"

class RedAssert
{
private:
	//定数

	//座標
	static const DirectX::SimpleMath::Vector2 DANGEROUSUI_TEXTURE_POSITION;
	//拡大率
	static const DirectX::SimpleMath::Vector2 DANGEROUSUI_TEXTURE_SCALE;

	//透明度増幅
	static const float DANGEROUSUI_SIN_NUM;
	//透明度の値調節
	static const float DANGEROUSUI_SIN_SHIFT;


	//変数
	//sin値
	float mSin;

	//画像
	std::unique_ptr<ObjectTexture> mpDangerousUI;

	//描画するかどうかの判定用フラグ
	bool mPassFlag;

public:

	//コンストラクタ
	RedAssert();
	//デストラクタ
	~RedAssert();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//処理を通すかどうかのフラグのアクセサ
	void SetPassFlag(const bool& flag) { mPassFlag = flag; }

};
