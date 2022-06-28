/*
敵移動State　～回転～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMoveStateBase.h"

class EnemyMoveStateRotation : public EnemyMoveStateBase
{
private:

	//回転する方向
	enum class RotationAngle
	{
		LEFT,
		RIGHT,
		NUM,
	};

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//回転スピード
	static const float ESTATE_ROT_SPEED;

	//回転後の角度
	static const float ROTATION_AFTER_ANGLE;


	//現在の回転角度
	float mRotationNowAngle;

	//回転する方向
	RotationAngle mRotationAngle;

	//回転速度
	float mRotationVelocity;

public:

	//コンストラクタ
	EnemyMoveStateRotation();
	//デストラクタ
	~EnemyMoveStateRotation()override;
	//初期化処理
	void Initialize(Enemy* pEnemy, EnemyMainStateMove* pEnemyMainState)override;
	//リセット処理
	void Reset()override;
	//更新処理
	void Update();

private:
	//回転方向を決める
	void ConfigurationRotationAngle();

	//向きに応じて回転速度を決める
	void ConfigurationRotationVelocity();

};
