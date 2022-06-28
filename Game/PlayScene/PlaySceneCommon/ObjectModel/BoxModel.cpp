/*
AABBの当たり判定を持ったモデルクラス
作成者：杉山
作成日：2021/06/12
*/

#include"pch.h"
#include"BoxModel.h"

//定数
//初期化値
const DirectX::SimpleMath::Vector3 BoxModel::InitCollider(-10.f, -10.f, -10.f);

/*===================================
コンストラクタ
引数：なし
===================================*/
BoxModel::BoxModel()
	:
	ObjectModel(),
	mpAABBCollider()
{
	mpAABBCollider = std::make_unique<AABB>();
	mpAABBCollider->mMin = InitCollider;
	mpAABBCollider->mMax = InitCollider;
}

/*===================================
デストラクタ
===================================*/
BoxModel::~BoxModel()
{
}


/*==================================================
拡大率の半分を返す(最小値、最大値の算出に使用)
引数：拡大率
返り値：拡大率の半分の値
====================================================*/
DirectX::SimpleMath::Vector3 BoxModel::ReturnHalfSize(const DirectX::SimpleMath::Vector3& scale)
{
	DirectX::SimpleMath::Vector3 returnsize;

	returnsize.x = scale.x / Utility::SCALE_HALF;
	returnsize.y = scale.y / Utility::SCALE_HALF;
	returnsize.z = scale.z / Utility::SCALE_HALF;
	return returnsize;
}

/*=========================================
情報のセッター
引数：min(最小値)、max(最大値)
返り値：なし
=========================================*/
void BoxModel::SetAABBCollider(const DirectX::SimpleMath::Vector3& min,
	const DirectX::SimpleMath::Vector3& max)
{
	mpAABBCollider->mMin = min;
	mpAABBCollider->mMax = max;
}
