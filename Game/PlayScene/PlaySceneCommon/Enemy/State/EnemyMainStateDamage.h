/*
敵基本State　～ダメージ～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

//列挙型の使用
#include"EnemyMainState.h"

//状態分け
#include"EnemyDamageState/EnemyDamageStateKnockBack.h"
#include"EnemyDamageState/EnemyDamageStateBlinking.h"

//前方宣言
class EnemyDamageStateBase;	//状態分け基底クラス

class EnemyMainStateDamage : public EnemyMainStateBase
{
private:
	//状態分け
	std::unique_ptr<EnemyDamageStateKnockBack> mpKnockBack;
	std::unique_ptr<EnemyDamageStateBlinking> mpBlinking;

	//現在の状態
	EnemyDamageStateBase* mpEnemyDamageStateBase;
	EnemyDamageState mState;


public:

	//コンストラクタ
	EnemyMainStateDamage();
	//デストラクタ
	~EnemyMainStateDamage();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//状態変更
	void ChangeStateKnockBack()
	{
		//状態変更
		mState = EnemyDamageState::KNOCK_BACK;
		mpEnemyDamageStateBase = static_cast<EnemyDamageStateBase*>(mpKnockBack.get());
		mpEnemyDamageStateBase->Reset();
	}
	void ChangeStateBlinking()
	{
		//状態変更
		mState = EnemyDamageState::BLINKING;
		mpEnemyDamageStateBase = static_cast<EnemyDamageStateBase*>(mpBlinking.get());
		mpEnemyDamageStateBase->Reset();
	}

	//移動ベクトルのスケーリング
	void MoveVectorScaling(const DirectX::SimpleMath::Vector3& movevec)
	{
		mpKnockBack->SetMoveVector(movevec);
		mpKnockBack->MoveVectorScaling();
	}
};
