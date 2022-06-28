/*
配下敵移動State　～歩行～
作成者：杉山
作成日：2022/02/14
*/
#pragma once

//基底クラス
#include"SubordinateEnemyMoveStateBase.h"

class SubordinateEnemyMoveStateWalk :public SubordinateEnemyMoveStateBase
{
private:

	//移動速度
	static const float SUBORDINATE_ENEMY_MOVE_VELOCITY;

	//向き調整係数
	static const int ANGLE_SHIFT;


	//追いかけ速度
	DirectX::SimpleMath::Vector3 mChaseVelocity;

	//対象のポインタ
	DirectX::SimpleMath::Vector3* mpSavePlayerPointer;

public:

	//コンストラクタ
	SubordinateEnemyMoveStateWalk();
	//デストラクタ
	~SubordinateEnemyMoveStateWalk();
	//初期化処理
	void Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)override;
	//更新処理
	void Update()override;

	//対象のポインタのアクセサ
	void SetSavePlayerPointer(DirectX::SimpleMath::Vector3* address) { mpSavePlayerPointer = address; }


private:
	//移動処理
	void Move();

	//向き調節処理
	void CalculationModelAngle();

};
