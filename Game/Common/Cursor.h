/*
カーソルを管理するクラス
作成者：杉山
作成日：2021/10/13
*/
#pragma once
//所持
#include"../Common/ObjectTexture.h"

class Cursor
{
private:

	//画像管理変数
	std::unique_ptr<ObjectTexture> mpCursorTexture;

	//移動幅保存用変数
	float mShiftNum;

	//初期座標保存用変数
	DirectX::SimpleMath::Vector2 mSaveInitPosition;

public:

	//コンストラクタ
	Cursor();
	//デストラクタ
	~Cursor();
	//初期化処理
	void Initialize(
		const int& key,
		const DirectX::SimpleMath::Vector2& initPosition,
		const DirectX::SimpleMath::Vector2& scale,
		const float& shiftPosition,
		const float& rot=0.f);

	//描画処理
	void Draw(const bool& flag=true);

	//カーソルを下に移動する
	void CursorDown();

	//カーソルを上に移動する
	void CursorUp();

	//カーソルを初期位置にリセットする
	void CursorReset();

	//カーソルを一番下にセットする
	void CursorSetUnder(const int& screenMaxStageNum);

};
