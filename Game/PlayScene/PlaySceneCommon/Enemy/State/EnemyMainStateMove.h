/*
敵基本State　～移動～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

#include"EnemyMoveState/EnemyMoveStateRotation.h"
#include"EnemyMoveState/EnemyMoveStateWalk.h"
#include"EnemyMoveState/EnemyMoveStateWallAttack.h"

//列挙型の使用
#include"EnemyMainState.h"


//前方宣言
class EnemyMoveStateBase;	//状態State
class Block;				//引数

class EnemyMainStateMove : public EnemyMainStateBase
{
public:

	//現在の衝突状態
	enum class EnemyBlockHit
	{
		NONE,	//通常
		HIT,	//衝突
		NOT_HIT	//離れた
	};

private:
	//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//連続衝突防止用移動定数
	static const DirectX::SimpleMath::Vector3 HIT_STOP_SHIFT;

	//反転角度
	static const float REVERSE_ANGLE;

	//現在の状態
	EnemyMoveStateBase* mpEnemyMoveStateBase;
	EnemyMoveState mState;

	//状態分け
	std::unique_ptr<EnemyMoveStateRotation> mpRotation;
	std::unique_ptr<EnemyMoveStateWalk> mpWalk;
	std::unique_ptr<EnemyMoveStateWallAttack> mpAttack;

	//当たり判定
	AABB mMoveCollider;

	/*壁攻撃*/
	//初めて衝突した壁のアドレス
	Block* mpFirstHitBlock;

	//壁反転数
	int mReverseNum;

	//現在の衝突状態
	EnemyBlockHit mBlockHitFlag;

	//攻撃している壁のポインタ
	bool* mpAttackBlockUseFlag;


public:

	//コンストラクタ
	EnemyMainStateMove();
	//デストラクタ
	~EnemyMainStateMove();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//向きを反転する
	void ReverseAngle();

	//向きを初期化
	void ResetEnemyAngle();

	//状態変更
	void ChangeStateWalk()
	{
		mState = EnemyMoveState::WALK;
		mpEnemyMoveStateBase = static_cast<EnemyMoveStateBase*>(mpWalk.get());
		mpEnemyMoveStateBase->Reset();
	}
	void ChangeStateRotation()
	{
		mState = EnemyMoveState::ROTATION;
		mpEnemyMoveStateBase = static_cast<EnemyMoveStateBase*>(mpRotation.get());
		mpEnemyMoveStateBase->Reset();
	}
	void ChangeStateWallAttack()
	{
		mState = EnemyMoveState::WALL_ATTACK;		//状態変更
		mReverseNum = 0;							//反転回数初期化
		mpAttackBlockUseFlag = nullptr;				//ポインタ初期化
		mpEnemyMoveStateBase = static_cast<EnemyMoveStateBase*>(mpAttack.get());
		mpEnemyMoveStateBase->Reset();				//各状態のリセット処理
	}

	//現在の状態
	EnemyMoveState GetMoveState()const { return mState; }

	//当たり判定のアクセサ
	AABB* GetAABBCollider(){ return &mMoveCollider; }
	void SetAABBCollider(const AABB& aabb) { mMoveCollider = aabb; }

	/*移動*/
	//プレイヤーの座標のアドレス
	DirectX::SimpleMath::Vector3* GetChasePlayerPositon() const{ return mpWalk->GetChasePlayerPositon(); }
	void SetChasePlayerPositon(DirectX::SimpleMath::Vector3* position) { mpWalk->SetChasePlayerPositon(position); }
	//プレイヤー追いかけフラグ
	bool GetChasePlayerFlag() const{ return mpWalk->GetPlayerChaseFlag(); }
	void SetChasePlayerFlag(const bool& flag) { mpWalk->SetPlayerChaseFlag(flag); }
	
	//衝突フラグ
	EnemyBlockHit GetBlockHitFlag()const { return mBlockHitFlag; }
	void SetBlockHitFlag(EnemyBlockHit const& flag) { mBlockHitFlag = flag; }

	//壁反転数
	int GetReverseNum() const { return mReverseNum; }

	/*壁攻撃*/
	//攻撃フラグ
	bool AttackFlag()const { return mpAttack->AttackTiming(); }

	//初めて衝突した壁のアドレス
	Block* GetFirstHitBlock()const { return mpFirstHitBlock; }
	void SetFirstHitBlock(Block* pBlock) { mpFirstHitBlock = pBlock; }

	//攻撃している壁のポインタのアクセサ
	bool* GetAttackBlock()const { return mpAttackBlockUseFlag; }
	void SetAttackBlock(bool* pBlock) { mpAttackBlockUseFlag = pBlock; }


private:

	//衝突しなくなった場合回転させる
	void NotHitEnemyChangeStateRotation();

	//当たり判定を設定する
	void SetAABBCollider();
};
