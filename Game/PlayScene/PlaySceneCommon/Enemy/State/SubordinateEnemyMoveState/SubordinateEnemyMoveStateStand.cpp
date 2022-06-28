
/*
配下敵移動State　～立ち状態～
作成者：杉山
作成日：2022/02/14
*/
#include"pch.h"

#include"SubordinateEnemyMoveStateStand.h"

//関数の使用
#include"../SubordinateEnemyMainStateMove.h"


//停止インターバル時間
const int SubordinateEnemyMoveStateStand::STAND_INTERVAL = 2;

/*===================================
コンストラクタ
引数：なし
===================================*/
SubordinateEnemyMoveStateStand::SubordinateEnemyMoveStateStand()
	:
	SubordinateEnemyMoveStateBase(),
	mpTimer(),
	mStandIntervalActiveFlag()
{
	mpTimer = std::make_unique<Timer>();
}

/*===================================
デストラクタ
===================================*/
SubordinateEnemyMoveStateStand::~SubordinateEnemyMoveStateStand()
{
}

/*===================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void SubordinateEnemyMoveStateStand::Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)
{
	//ポインタ保存
	SubordinateEnemyMoveStateBase::SetEnemy(pEnemy);
	SubordinateEnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);


	//タイマー設定処理
	mpTimer->SetMaxTime(STAND_INTERVAL);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMoveStateStand::Update()
{
	//フラグが立っていない場合処理をしない
	if (!mStandIntervalActiveFlag)return;

	//タイマー更新処理
	bool finishFlag = mpTimer->Update();

	//時間となったら
	if (finishFlag)
	{
		//フラグを下す
		mStandIntervalActiveFlag = false;

		//タイマーをリセットする
		mpTimer->ResetMainTimer();

		//状態変更
		SubordinateEnemyMoveStateBase::GetEnemyMainState()->ChangeStateWalk();
	}
}
