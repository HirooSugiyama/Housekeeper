/*
天球クラス
作成者：杉山
作成日：2021/06/19
*/
#pragma once



//所持
#include"../../PlaySceneCommon/ObjectModel/ObjectModel.h"


class CelestialSphere
{
	
private:
	//定数
	enum class eWhichLight:int
	{
		_0,
		_1,
		_2,
	};

	//天球の半径
	static const DirectX::SimpleMath::Vector3 SPHERE_RADIUS;

	//カラーを最大値に
	static const DirectX::SimpleMath::Vector3 MAX_COLOR_NUM;

	//天球モデル
	std::unique_ptr<ObjectModel> mpSphere;

public:
	//コンストラクタ
	CelestialSphere();
	//デストラクタ
	~CelestialSphere();

	//初期化
	void Initialize();

	//描画
	void Draw();

	//天球を変える
	void ChangeSphereModelNight();
	void ChangeSphereModelDay();

};