/*
敵ダメージState基底クラス
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//前方宣言
class EnemyMainStateDamage;
class Enemy;

class EnemyDamageStateBase
{
private:

	//所有者のポインタ
	EnemyMainStateDamage* mpEnemyMainState;
	Enemy* mpEnemy;

public:

	//コンストラクタ
	EnemyDamageStateBase();
	//デストラクタ
	~EnemyDamageStateBase();
	//初期化処理
	virtual void Initialize(Enemy* pEnemy, EnemyMainStateDamage* pEnemyMainState) = 0;
	//リセット処理
	virtual void Reset() = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw() {}

	//アクセサ
	EnemyMainStateDamage* GetEnemyMainState() const { return mpEnemyMainState; }
	void SetEnemyMainState(EnemyMainStateDamage* pEnemyMainState) { mpEnemyMainState = pEnemyMainState; }

	Enemy* GetEnemy() const { return mpEnemy; }
	void SetEnemy(Enemy* pEnemy) { mpEnemy = pEnemy; }
};
