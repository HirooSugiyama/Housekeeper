/*
平面ポリゴン描画基底クラス
作成者：杉山
作成日：2021/11/13
*/
#pragma once





class FlatPolygonBase
{
protected:


	//コンストラクタ
	FlatPolygonBase() = default;
	//デストラクタ
	virtual ~FlatPolygonBase() = default;

public:

	//初期化
	virtual void Initialize() = 0;

	//描画
	virtual void Draw(const DirectX::SimpleMath::Vector3& position) = 0;

	//拡大率のアクセサ
	virtual void SetScale(const DirectX::SimpleMath::Vector2& scale) = 0;


};
