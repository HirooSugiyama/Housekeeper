/*
ボス敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

//状態分け
#include"BossEnemyMoveState/BossEnemyMoveStateWalk.h"
#include"BossEnemyMoveState/BossEnemyMoveStateEscape.h"
#include"BossEnemyMoveState/BossEnemyMoveStateStand.h"

//列挙型の使用
#include"BossEnemyState.h"


//前方宣言
class BossEnemyMoveStateBase;	//状態State

class BossEnemyMainStateMove : public EnemyMainStateBase
{
private:

	//現在の状態
	BossEnemyMoveStateBase* mpState;
	BossEnemyMoveState mState;

	//状態分け
	std::unique_ptr<BossEnemyMoveStateWalk> mpWalk;
	std::unique_ptr<BossEnemyMoveStateEscape> mpEscape;
	std::unique_ptr<BossEnemyMoveStateStand> mpStand;

	//追いかけ用移動速度保存変数
	DirectX::SimpleMath::Vector3 mChaseVelocity;

	//プレイヤー座標ポインタ保存用変数
	DirectX::SimpleMath::Vector3* mpSavePlayerPointer;

public:

	//コンストラクタ
	BossEnemyMainStateMove();
	//デストラクタ
	~BossEnemyMainStateMove();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;


	//状態変更
	void ChangeStateWalk()
	{
		mState = BossEnemyMoveState::WALK;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpWalk.get());
	}
	void ChangeStateEscape()
	{
		mState = BossEnemyMoveState::ESCAPE;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpEscape.get());
	}
	void ChangeStateStand()
	{
		mState = BossEnemyMoveState::STAND;
		mpState = static_cast<BossEnemyMoveStateBase*>(mpStand.get());
	}

	//現在の状態
	BossEnemyMoveState GetMoveState()const { return mState; }

	//プレイヤー座標ポインタ保存用変数のアクセサ
	void SetSavePlayerPointer(DirectX::SimpleMath::Vector3* position)
	{
		mpSavePlayerPointer = position;
	}
	DirectX::SimpleMath::Vector3* GetSavePlayerPointer()const { return mpSavePlayerPointer; }

	//移動ベクトルの生成
	DirectX::SimpleMath::Vector3 CreateMoveVector(const float& moveVelocity);

	//向き調節処理
	float CalculationModelAngle();

};
