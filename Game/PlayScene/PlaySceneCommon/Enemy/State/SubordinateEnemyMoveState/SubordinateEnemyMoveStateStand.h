/*
配下敵移動State　～立ち状態～
作成者：杉山
作成日：2022/02/14
*/
#pragma once

//基底クラス
#include"SubordinateEnemyMoveStateBase.h"


//所持
#include"Game/PlayScene/PlaySceneCommon/Administrator/Timer.h"

class SubordinateEnemyMoveStateStand :public SubordinateEnemyMoveStateBase
{
private:
	
	//停止インターバル時間
	static const int STAND_INTERVAL;

	//停止インターバル計測変数
	std::unique_ptr<Timer> mpTimer;

	//停止インターバル稼働フラグ
	bool mStandIntervalActiveFlag;

public:

	//コンストラクタ
	SubordinateEnemyMoveStateStand();
	//デストラクタ
	~SubordinateEnemyMoveStateStand()override;
	//初期化処理
	void Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)override;
	//更新処理
	void Update()override;

	//停止インターバル稼働フラグのアクセサ
	void SetStandIntervalActiveFlag(const bool& flag) { mStandIntervalActiveFlag = flag; }
};
