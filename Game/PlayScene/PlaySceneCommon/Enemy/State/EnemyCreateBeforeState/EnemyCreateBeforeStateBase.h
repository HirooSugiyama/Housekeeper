/*
敵生成前State基底クラス
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//前方宣言
class EnemyMainStateCreateBefore;
class IEnemy;

class EnemyCreateBeforeStateBase
{
private:

	//所有者のポインタ
	EnemyMainStateCreateBefore* mpEnemyMainState;
	IEnemy* mpEnemy;

public:

	//コンストラクタ
	EnemyCreateBeforeStateBase();
	//デストラクタ
	virtual ~EnemyCreateBeforeStateBase();
	//初期化処理
	virtual void Initialize(EnemyMainStateCreateBefore* pEnemyMainState, IEnemy* pEnemy) = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw() {}

	//アクセサ
	EnemyMainStateCreateBefore* GetEnemyMainState()const { return mpEnemyMainState; }
	void SetEnemyMainState(EnemyMainStateCreateBefore* pEnemyMainState) { mpEnemyMainState = pEnemyMainState; }
	
	IEnemy* GetEnemy()const { return mpEnemy; }
	void SetEnemy(IEnemy* pEnemy) { mpEnemy = pEnemy; }

};
