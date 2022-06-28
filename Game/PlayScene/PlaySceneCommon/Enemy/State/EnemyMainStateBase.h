/*
敵基本State基底クラス
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//前方宣言
class IEnemy;

class EnemyMainStateBase
{
private:

	//所有者のポインタ
	IEnemy* mpEnemy;

public:

	//コンストラクタ
	EnemyMainStateBase();
	//デストラクタ
	~EnemyMainStateBase();
	//初期化処理
	virtual void Initialize(IEnemy* pEnemy) = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw() {}

	//アクセサ
	IEnemy* GetEnemy() const { return mpEnemy; }
	void SetEnemy(IEnemy* pEnemy) { mpEnemy = pEnemy; }

};
