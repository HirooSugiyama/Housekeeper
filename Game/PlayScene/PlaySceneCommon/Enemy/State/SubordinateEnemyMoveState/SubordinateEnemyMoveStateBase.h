/*
配下敵移動State　基底クラス
作成者：杉山
作成日：2022/02/14
*/
#pragma once

//前方宣言
class SubordinateEnemyMainStateMove;
class IEnemy;

class SubordinateEnemyMoveStateBase
{
private:

	//所有者のポインタ
	SubordinateEnemyMainStateMove* mpEnemyMainState;
	IEnemy* mpEnemy;

public:

	//コンストラクタ
	SubordinateEnemyMoveStateBase();
	//デストラクタ
	virtual ~SubordinateEnemyMoveStateBase();
	//初期化処理
	virtual void Initialize(IEnemy* mpEnemy, SubordinateEnemyMainStateMove* mpEnemyMainState) = 0;
	//更新処理
	virtual void Update() = 0;

	//アクセサ
	SubordinateEnemyMainStateMove* GetEnemyMainState() const { return mpEnemyMainState; }
	void SetEnemyMainState(SubordinateEnemyMainStateMove* pEnemyMainState) { mpEnemyMainState = pEnemyMainState; }

	IEnemy* GetEnemy() const { return mpEnemy; }
	void SetEnemy(IEnemy* pEnemy) { mpEnemy = pEnemy; }

};
