/*
敵移動State基底クラス
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//前方宣言
class EnemyMainStateMove;
class Enemy;

class EnemyMoveStateBase
{
private:

	//正面
	static const float FRONT;

	//所有者のポインタ
	EnemyMainStateMove* mpEnemyMainState;
	Enemy* mpEnemy;

public:

	//コンストラクタ
	EnemyMoveStateBase();
	//デストラクタ
	virtual ~EnemyMoveStateBase();
	//初期化処理
	virtual void Initialize(Enemy* pEnemy, EnemyMainStateMove* pEnemyMainState) = 0;
	//リセット処理
	virtual void Reset() = 0;
	//更新処理
	virtual void Update() = 0;
	//アクセサ
	EnemyMainStateMove* GetEnemyMainState()const { return mpEnemyMainState; }
	void SetEnemyMainState(EnemyMainStateMove* pEnemyMainState) { mpEnemyMainState = pEnemyMainState; }

	Enemy* GetEnemy()const { return mpEnemy; }
	void SetEnemy(Enemy* pEnemy) { mpEnemy = pEnemy; }

	//正面
	float GetFrontAngle()const { return FRONT; }
};
