/*
球の当たり判定を持ったモデルクラス
作成者：杉山
作成日：2021/06/12
*/
#pragma once

#include"ObjectModel.h"

class SphereModel :public ObjectModel
{
private:
	//当たり判定初期値
	static const float InitCollider;

	//変数
	std::unique_ptr<Sphere> mpSphereCollider;

public:
	//コンストラクタ
	SphereModel();
	//デストラクタ
	~SphereModel();

	//アクセサ
	Sphere* GetSphereCollider() { return mpSphereCollider.get(); }

	void SetSphereCollider(const DirectX::SimpleMath::Vector3& center, float radius);
};
