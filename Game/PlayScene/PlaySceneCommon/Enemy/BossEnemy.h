/*
ボス敵クラス
作成者：杉山
作成日：2022/02/11
*/
#pragma once

//基底クラス
#include"IEnemy.h"

//所持
#include"../FlatPolygon.h"

//状態分け
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateDisappearance.h"
#include"State/BossEnemyMainStateAttack.h"
#include"State/BossEnemyMainStateCreate.h"
#include"State/BossEnemyMainStateMove.h"

//列挙型の使用
#include"State/BossEnemyState.h"

//前方宣言
class SubordinateEnemy;

//状態基底クラス
class EnemyMainStateBase;

class BossEnemy :public IEnemy
{
private:
	//認識範囲の拡大率
	static const float RECOGITION_RANGE_SCALE;

	//ボス敵のHP
	static const int BOSS_ENEMY_HP;


	//プレイヤー認識範囲
	std::unique_ptr<FlatPolygon> mpPlayerRecognitionRange;

	//配下敵のアドレス管理用変数
	std::vector<SubordinateEnemy*> mpSaveSubordinateEnemy;

	//認識範囲当たり判定
	Sphere mPlayerRecognitionRangeCollider;

	//動き出すタイミング
	int mMovePhaseNumber;

	//生成フラグ
	bool mActiveFlag;

	//現在の状態
	EnemyMainStateBase* mpMainState;
	BossEnemyMainState mState;

	//状態分け
	/*通常と共通*/
	//生成前
	std::unique_ptr<EnemyMainStateCreateBefore> mpCreateBefore;
	//消滅
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;

	/*特殊*/
	//移動
	std::unique_ptr<BossEnemyMainStateMove> mpMove;

	//攻撃
	std::unique_ptr<BossEnemyMainStateAttack> mpAttack;

	//生成
	std::unique_ptr<BossEnemyMainStateCreate> mpCreate;

public:

	//コンストラクタ
	BossEnemy();
	//デストラクタ
	~BossEnemy()override;
	//初期化処理
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//使用フラグ
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }

	//配下敵のアドレス管理用変数のアクセサ
	std::vector<SubordinateEnemy*> GetSaveSubordinateEnemy()const { return mpSaveSubordinateEnemy; }
	void SetSaveSubordinateEnemy(std::vector<SubordinateEnemy*> pSubordinateEnemy);

	//認識範囲の当たり判定のアクセサ
	Sphere* GetPlayerRecognitionRangeCollider() { return &mPlayerRecognitionRangeCollider; }

	//始動するフェーズ番号のアクセサ
	void SetMovePhaseNumber(const int& num) { mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const { return mMovePhaseNumber; }

	//状態分け
	/*通常と共通*/
	//生成前
	void ChangeStateCreateBefore()override
	{
		mState = BossEnemyMainState::CREATE_BEFORE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreateBefore.get());
	}
	//消滅
	void ChangeStateDisappearance()override
	{
		mState = BossEnemyMainState::DISAPPEARANCE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}

	/*特殊*/
	//移動
	void ChangeStateMove()override
	{
		mState = BossEnemyMainState::MOVE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}

	//攻撃
	void ChangeStateAttack()
	{
		mState = BossEnemyMainState::ATTACK;
		mpMainState = static_cast<EnemyMainStateBase*>(mpAttack.get());
	}
	//生成
	void ChangeStateCreate()
	{
		mState = BossEnemyMainState::CREATE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreate.get());
	}

	//状態の取得
	BossEnemyMainState GetState() { return mState; }
	EnemyMainStateCreateBefore* GetStateCreateBefore() { return mpCreateBefore.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance() { return mpDisappearance.get(); }
	BossEnemyMainStateMove* GetStateMove() { return mpMove.get(); }
	BossEnemyMainStateAttack* GetStateAttack() { return mpAttack.get(); }
	BossEnemyMainStateCreate* GeStatetCreate() { return mpCreate.get(); }


	//敵のHPのアクセサ
	int GetEnemyHP() override { return BOSS_ENEMY_HP; }

	//生成フラグのアクセサ
	bool GetActiveFlag()const { return mActiveFlag; }
	void SetActiveFlag(const bool& flag) { mActiveFlag = flag; }

private:
	//当たり判定設定
	void SetCollider();

	//ポインタ削除処理
	void DeleteSubordinateEnemyAddress();

};
