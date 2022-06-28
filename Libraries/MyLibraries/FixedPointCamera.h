/*
定点カメラ
作成者：杉山
作成日：2021/10/24
*/
#pragma once



//規定クラス
#include"CameraBase.h"

class FixedPointCamera :public CameraBase
{
private:

	//カメラ座標
	static const DirectX::SimpleMath::Vector3 EYE_TO_VEC;

public:
	// コンストラクタ
	FixedPointCamera();

	// デストラクタ
	~FixedPointCamera();

};
