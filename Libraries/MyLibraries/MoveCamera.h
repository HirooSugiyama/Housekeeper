/*
動くカメラクラス
作成者：杉山
作成日：2021/12/05
*/
#pragma once

#include"CameraBase.h"


class MoveCamera :public CameraBase
{
private:
	//ばねの強さ
	static const float SPRING_POWER;

public:
	//コンストラクタ
	MoveCamera(const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target);

	//アクセサ
	float GetSpringPower()const { return SPRING_POWER; }

};
