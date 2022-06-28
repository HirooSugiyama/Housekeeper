/*
敵基本State　～生成前～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

//状態State
#include"EnemyCreateBeforeState/EnemyCreateBeforeStateSinking.h"
#include"EnemyCreateBeforeState/EnemyCreateBeforeStateAppearance.h"

//列挙型の使用
#include"EnemyMainState.h"

//前方宣言
class EnemyCreateBeforeStateBase;

class EnemyMainStateCreateBefore : public EnemyMainStateBase
{
private:

	//生成前の高さ
	static const float ENEMY_INIT_POSITION_Y;

	//現在の状態
	EnemyCreateBeforeStateBase* mpState;
	EnemyCreateBeforeState mState;

	//状態State
	std::unique_ptr<EnemyCreateBeforeStateSinking> mpSinking;
	std::unique_ptr<EnemyCreateBeforeStateAppearance> mpAppearance;

public:

	//コンストラクタ
	EnemyMainStateCreateBefore();
	//デストラクタ
	~EnemyMainStateCreateBefore();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;
	//状態を変更する
	void ChangeState();

private:
	//状態切り替え
	void ChangeStateSinking()
	{
		mState = EnemyCreateBeforeState::SINKING;
		mpState = static_cast<EnemyCreateBeforeStateBase*>(mpSinking.get());
	}

	void ChangeStateAppearance()
	{
		mState = EnemyCreateBeforeState::APPEARANCE;
		mpState = static_cast<EnemyCreateBeforeStateAppearance*>(mpAppearance.get());
	}
};
