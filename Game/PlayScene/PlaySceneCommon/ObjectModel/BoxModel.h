/*
AABBの当たり判定を持ったモデルクラス
作成者：杉山
作成日：2021/06/12
*/
#pragma once

#include"ObjectModel.h"

class BoxModel :public ObjectModel
{
private:
	//定数
	//初期化値
	static const DirectX::SimpleMath::Vector3 InitCollider;

	//拡大率を半分にする
	static const int SCALE_HALF;


	//変数
	std::unique_ptr<AABB> mpAABBCollider;

public:
	//コンストラクタ
	BoxModel();
	//デストラクタ
	~BoxModel();

	//拡大率の半分を返す(AABBの算出に使用)
	DirectX::SimpleMath::Vector3 ReturnHalfSize
		(const DirectX::SimpleMath::Vector3& scale);


	//アクセサ
	AABB* GetAABBCollider()const { return mpAABBCollider.get(); }

	void SetAABBCollider(const DirectX::SimpleMath::Vector3& min,
		const DirectX::SimpleMath::Vector3& max);
};

