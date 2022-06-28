/*
ボス敵移動State基底クラス
作成者：杉山
作成日：2022/02/12
*/
#pragma once

//前方宣言
class BossEnemyMainStateMove;
class IEnemy;

class BossEnemyMoveStateBase
{
private:


	//保存用ポインタ
	BossEnemyMainStateMove* mpMoveState;
	IEnemy* mpEnemy;

public:

	//コンストラクタ
	BossEnemyMoveStateBase();
	//デストラクタ
	~BossEnemyMoveStateBase();
	//初期化処理
	virtual void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState) = 0;
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//移動速度設定
	virtual DirectX::SimpleMath::Vector3 GetMoveVelocity() = 0;
	//向き設定
	virtual void SetAngle() = 0;
	
	//逃走状態専用処理
	virtual void EscapeUpdate(){}

	//保存用ポインタのアクセサ
	BossEnemyMainStateMove* GetMoveState()const { return mpMoveState; }
	void SetMoveState(BossEnemyMainStateMove* pState) { mpMoveState = pState; }
	IEnemy* GetBossEnemy() const { return mpEnemy; }
	void SetBossEnemy(IEnemy* pState) { mpEnemy = pState; }
};
