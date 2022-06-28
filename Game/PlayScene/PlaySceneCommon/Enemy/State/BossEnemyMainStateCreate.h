/*
ボス敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
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
class SubordinateEnemy;

class BossEnemyMainStateCreate : public EnemyMainStateBase
{
private:
	//回転速度
	static const float ROTATION_VELOCITY;

	//配列代表番号
	static const int ARRAY_REPRESENTATIVE_NUM;

public:

	//コンストラクタ
	BossEnemyMainStateCreate();
	//デストラクタ
	~BossEnemyMainStateCreate();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//中身があるアドレスを返す
	SubordinateEnemy* GetSubordinateEnemyAddress();

};
