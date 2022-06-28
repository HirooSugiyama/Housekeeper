/*
ユーザーインターフェース
(指定されたところに指定されたものを描画するクラス)
作成者：杉山
作成日：2021/06/23
*/

#include"pch.h"
#include"UI.h"

//ポインタの保存用
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"
#include"../PlayScene/PlaySceneCommon/Protecter.h"


//敵情報描画位置
const DirectX::SimpleMath::Vector2 UI::STRING_ENEMY_NUM_POSITION(20.f, 80.f);

//所持金減少エフェクトの位置
const DirectX::SimpleMath::Vector2 UI::MONEY_EFFECT_POSITION(1000.f,100.f);

/*==============
コンストラクタ
引数：なし
==============*/
UI::UI()
	:
	mpTimeOfDay(),
	mpMoneyTexture(),
	mpPhaseCursorManager(),
	mpRedAssert(),
	mpPlayerActionInfo(),
	mpDecreaseMoney(),
	mpScoreRender(),
	mpDefeatEnemyRender(),
	mpTimer(),
	mpProtecter(),
	mpPlayer(),
	mpPhaseCountNum(),
	mpPhase(),
	mInitHP(),
	mMaxPhaseNum(),
	mScoreNum(),
	mAllEnemyNum(),
	mRemainingEnemyNum(),
	mUIDrawFlag(true),
	mpControlPanel(nullptr)
{
	//動的確保
	mpTimeOfDay = std::make_unique<TimeOfDay>();
	mpMoneyTexture = std::make_unique<MoneyTexture>();
	mpPhaseCursorManager = std::make_unique<PhaseCursorManager>();
	mpRedAssert = std::make_unique<RedAssert>();
	mpPlayerActionInfo = std::make_unique<PlayerActionInfo>();
	mpDecreaseMoney = std::make_unique<FloatNumber2D>();
	mpScoreRender = std::make_unique<ScoreRender>();
	mpDefeatEnemyRender = std::make_unique<DefeatEnemyRender>();
	mpControlPanel = std::make_unique<ControlPanel>();

}
/*==============
デストラクタ
==============*/	
UI::~UI()
{
}


/*========================
初期化
引数：カメラのポインタ
返り値：なし
==========================*/
void UI::Initialize()
{
	//フェーズ関係の画像の初期設定
	mpTimeOfDay->Initialize(mpTimer, mMaxPhaseNum);

	//所持金の下地画像の初期化処理
	mpMoneyTexture->Initialize();

	//フェーズのカーソルの初期化処理
	mpPhaseCursorManager->Initialize(mMaxPhaseNum);

	//カーソルの座標を設定する
	mpPhaseCursorManager->SetDrawPosition
	(
		mpTimeOfDay->GetIconStartPosition(),
		mpTimeOfDay->GetIconDistancePosition()
	);

	//危険信号の初期化処理
	mpRedAssert->Initialize();

	//プレイヤーの現在の状態の初期化処理
	mpPlayerActionInfo->Initialize();

	//所持金減少エフェクトのフォントを指定
	mpDecreaseMoney->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWDAMAGESTRING));
	mpDecreaseMoney->Initialize();

	//スコア周りの描画クラスの初期化処理
	mpScoreRender->Initialize();

	//残り敵数の初期化処理
	mpDefeatEnemyRender->Initialize();

	//操作方法描画の初期化処理
	mpControlPanel->Initialize();
}

/*==============
更新処理
引数：なし
返り値：なし
==============*/
void UI::Update()
{
	//現在のPhaseが防衛フェーズの場合
	if (*mpPhase == ePlayScenePhase::DEFENCE)
	{
		//フェーズ関係の画像の更新処理
		mpTimeOfDay->Update();

		//危険信号の更新処理
		mpRedAssert->Update();

		//所持金減少エフェクトの更新処理
		mpDecreaseMoney->Update();
	}
	//現在のPhaseがショップフェーズの場合
	if (*mpPhase == ePlayScenePhase::WEAPON_SHOP)
	{
		//所持金減少エフェクトの更新処理
		mpDecreaseMoney->Update();
	}

	//ゲームパッドが刺さった際の処理
	mpControlPanel->ChangeControl();

}

/*==============
描画
引数：なし
返り値：なし
==============*/
void UI::Draw()
{
	//フラグが下りている場合は描画しない
	if (!mUIDrawFlag)return;

	//プレイヤーの現在の状態の描画処理
	mpPlayerActionInfo->Draw();
	
	//危険信号の描画処理
	mpRedAssert->Draw();
	
	//フェーズ関係の画像の描画
	mpTimeOfDay->Draw();
	
	//フェーズのカーソルの描画処理
	mpPhaseCursorManager->Draw();
	
	//所持金関係の描画
	this->DrawMoneyTexture();
	
	//スコアの描画
	mpScoreRender->Draw(mScoreNum);
	
	//残りの敵の数の描画
	mpDefeatEnemyRender->Draw(mRemainingEnemyNum, mAllEnemyNum);

	//操作方法描画の描画
	mpControlPanel->Draw();
}

/*============
ポインタの保存
返り値：なし
==============*/
//引数：タイマーのポインタ
void UI::SetTimerPointer(Timer* pTimer)
{
	mpTimer = pTimer;
}

//引数：プレイヤーのポインタ
void UI::SetPlayerPointer(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//引数：拠点のポインタ
void UI::SetProtecterPointer(Protecter* pProtecter)
{
	mpProtecter = pProtecter;
}

//引数：フェーズカウント数のポインタ
void UI::SetPhaseCountPointer(int* pPhaseCount)
{
	mpPhaseCountNum = pPhaseCount;
}

//引数：現在のフェーズのポインタ
void UI::SetPhase(ePlayScenePhase* phase)
{
	mpPhase = phase;
}

//引数：初期HP
void UI::SetInitHP(const int& pHP)
{
	mInitHP = pHP;
}

//引数：最大Phase数
void UI::SetMaxPhaseNum(const int& phasenum)
{
	mMaxPhaseNum = phasenum;
}

//引数：スコア値
void UI::SetScoreNum(const int& phasenum)
{
	mScoreNum = phasenum;
}
//引数：全ての敵の数
void UI::SetAllEnemyNum(const int& phasenum)
{
	mAllEnemyNum = phasenum;
}
//引数：倒した敵の数
void UI::SetRemainingEnemyNum(const int& phasenum)
{
	mRemainingEnemyNum = phasenum;
}


/*==========================
危険信号を操作する関数
引数：危険信号フラグ
返り値：なし
==========================*/
void UI::RedAssertControl(const bool& flag)
{
	mpRedAssert->SetPassFlag(flag);
}

/*========================
描画する画像を変える関数
返り値：なし
==========================*/
//引数：プレイヤーの行動状態State
void UI::ChangeActionInfoTexture(const ePlayerActionState & state)
{
	mpPlayerActionInfo->SetPlayerActionState(state);
}
//引数：武器種
void UI::ChangeActionInfoTexture(const eWeaponType& type)
{
	mpPlayerActionInfo->SetPlayerWeaponType(type);
}

/*==============================
現在の武器の弾数を取得する関数
引数：銃の弾数
返り値：なし
================================*/
void UI::SetActionInfoStrongBulletNum(const int& num)
{
	mpPlayerActionInfo->StrongWeaponBulletNum(num);
}

/*==============================
所持金を描画する関数
引数：なし
返り値：なし
================================*/
void UI::DrawMoneyTexture()
{
	//所持金の描画
	mpMoneyTexture->Draw();

	//所持金減少エフェクトの描画
	mpDecreaseMoney->Draw();
}

/*============================================
所持金減少エフェクトを作成する
引数：減少額
返り値：なし
==============================================*/
void UI::CreateMoneyEffect(const int& moneynum)
{
	mpDecreaseMoney->Reset();

	mpDecreaseMoney->Create(moneynum, MONEY_EFFECT_POSITION);
}

/*============================================
所持金減少エフェクトを作成する
引数：なし
返り値：なし
==============================================*/
void UI::ChangeDrawControlUIFlag()
{
	//もし現在ONなら
	if (mpControlPanel->GetDrawFlag())
	{
		//OFFにする
		mpControlPanel->SetDrawFlag(false);
	}
	else
	{
		//ONにする
		mpControlPanel->SetDrawFlag(true);
	}
}
