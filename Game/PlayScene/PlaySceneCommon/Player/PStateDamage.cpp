/*
プレイヤーの状態分けステートパターン：やられ状態
作成者：杉山
作成日：2021/06/15
*/
#include"pch.h"

#include"PStateDamage.h"


//前方宣言
#include"../DamageTimer.h"

//返り値からの関数の取得で使用。
#include"../ObjectModel/BoxModel.h"

//プレイヤー点滅インターバル
const int PStateDamage::PLAYER_BLINKING_INTERVAL = 20;

/*=========================
コンストラクタ
引数：なし
=========================*/
PStateDamage::PStateDamage()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpDamageTimer(nullptr)

{
	mpDamageTimer = std::make_unique<DamageTimer>();
}

/*=========================
デストラクタ
=========================*/
PStateDamage::~PStateDamage()
{
}

/*=========================
初期化処理
引数：プレイヤーのポインタ
返り値：なし
=========================*/
void PStateDamage::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

/*=========================
更新処理
引数：なし
返り値：なし
=========================*/
void PStateDamage::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::DAMAGE) 
	{
		mpPlayer->SetState(ePlayerState::DAMAGE);
	}

	//時間が来たら
	if (mpDamageTimer->Update()) 
	{
		//時間が来たら立ち状態に戻す
		mpPlayer->ChangeStateStand();
	}
}

/*=========================
描画処理
引数：なし
返り値：なし
=========================*/
void PStateDamage::Draw()
{
	//モデル描画
	//点滅表示をする
	if (mpDamageTimer->RegularIntervalTimer(PLAYER_BLINKING_INTERVAL)) 
	{
		mpPlayer->GetPlayerModel()->Draw();
	}
}
