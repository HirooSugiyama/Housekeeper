/*
動く文字画像クラス
作成者：杉山
作成日：2021/12/17
*/
#pragma once

#include"CountNumber.h"
#include"../../Common/SpriteNumber/SpriteNumber2D.h"

//所持

class MoveSpriteNumber2D
{
private:

	//動く数字クラス
	std::unique_ptr<CountNumber> mpCountNumber;

	//数字画像クラス
	std::unique_ptr<SpriteNumber2D> mpSpriteNumber2D;

	//描画座標
	DirectX::SimpleMath::Vector2 mDrawPosition;

public:

	//コンストラクタ
	MoveSpriteNumber2D();
	//デストラクタ
	~MoveSpriteNumber2D();
	//初期化処理
	void Initialize(const int& textureKey,const int& firstNum,
						const float& moveSecondSpeed, const int& maxNum);
	//更新処理
	int Update(const DX::StepTimer& timer);
	//描画処理
	void Draw();

	//座標を指定
	void SetPosition(DirectX::SimpleMath::Vector2 position) { mDrawPosition = position; }
	//拡大率指定
	void SetScale(float scale) { mpSpriteNumber2D->SetScale(scale); }

	//中心位置を変更
	void SetAlign(eAlign algin) { mpSpriteNumber2D->SetAlign(algin); }

	//値を最大値に変更する
	void ForcedChangeMoveNum() { mpCountNumber->ForcedChangeMoveNum(); }
};
