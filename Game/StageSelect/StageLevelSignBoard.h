/*
ステージレベルの看板
作成者：杉山
作成日：2022/03/12
*/
#pragma once

#include"Game/Common/ObjectTexture.h"

class StageLevelSignBoard
{
private:
	//画像の拡大率
	static const DirectX::SimpleMath::Vector2 TEXTURE_SCALE;
	//画像の座標
	static const DirectX::SimpleMath::Vector2 TEXTURE_POSITON;


	//画像
	std::unique_ptr<ObjectTexture> mpSignBoard;

public:

	//コンストラクタ
	StageLevelSignBoard();
	//デストラクタ
	~StageLevelSignBoard();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw();

};
