/*
画像を平面描画するクラス
作成者：杉山
作成日：2021/11/13
*/
#pragma once

//基底クラス
#include"FlatPolygonBase.h"

namespace DirectX
{
	class BasicEffect;
	struct VertexPositionTexture;
}

class FlatPolygon :public FlatPolygonBase
{
private:

	//変数============================

	//拡大率
	DirectX::SimpleMath::Vector2 mScale;

	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpPrimitiveBatch;

	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;


	//関数============================

public:
	//コンストラクタ	
	FlatPolygon();

	//デストラクタ
	~FlatPolygon()override;

	//初期化
	void Initialize()override;

	//描画
	void Draw(const DirectX::SimpleMath::Vector3& position)override;

	//拡大率のアクセサ
	void SetScale(const DirectX::SimpleMath::Vector2& scale)override { mScale = scale; }

	//画像を設定する
	void SetTexture(const int& texPath);
};
