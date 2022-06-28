/*
敵移動State　～歩行～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMoveStateBase.h"			

class EnemyMoveStateWalk : public EnemyMoveStateBase
{
private:

	//移動速度
	static const float ENEMY_MOVE_SPEED;

	//傾き補正
	static const float SHIFT_ANGLE;
	//追いかけフラグ
	bool mPlayerChaseFlag;

	//追いかけ用移動速度保存変数
	DirectX::SimpleMath::Vector3 mChaseVelocity;

	//移動量
	DirectX::SimpleMath::Vector3 mEnemyMoveVelocity;

	//プレイヤーの座標のアドレス
	DirectX::SimpleMath::Vector3* mChasePlayerPositon;

public:

	//コンストラクタ
	EnemyMoveStateWalk();
	//デストラクタ
	~EnemyMoveStateWalk()override;
	//初期化処理
	void Initialize(Enemy* pEnemy, EnemyMainStateMove* pEnemyMainState)override;
	//リセット処理
	void Reset()override;
	//更新処理
	void Update()override;

	//向きを変更する
	void RotEnemyForTarget();


	//プレイヤーの座標のアドレス
	DirectX::SimpleMath::Vector3* GetChasePlayerPositon() const { return mChasePlayerPositon; }
	void SetChasePlayerPositon(DirectX::SimpleMath::Vector3* position) { mChasePlayerPositon = position; }

	//追いかけフラグのアクセサ
	bool GetPlayerChaseFlag()const { return mPlayerChaseFlag; }
	void SetPlayerChaseFlag(const bool& flag) { mPlayerChaseFlag = flag; }

	//移動量を算出
	void CalculationMoveVelocity();

private:
	//追尾速度設定
	void ChaseVelocity();

	//移動処理
	void Move();

	//追尾処理
	void Chase();
};
