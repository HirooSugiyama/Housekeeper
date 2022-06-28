/*
ユーザーインターフェース
(指定されたところに指定されたものを描画するクラス)
作成者：杉山
作成日：2021/06/23
*/
#pragma once



//現在のフェーズ取得に使用
#include"../PlayScene/PlayScenePhase/PlayScenePhase.h"

//列挙型の使用
#include"../PlayScene/PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlayScene/PlaySceneCommon/Weapon/WeaponeType.h"


//前方宣言
//所持
#include"ScoreRender.h"
#include"DefeatEnemyRender.h"
#include"TimeOfDay.h"
#include"MoneyTexture.h"
#include"PhaseCursorManager.h"
#include"RedAssert.h"
#include"PlayerActionInfo.h"
#include"../Common/SpriteNumber/FloatNumber2D.h"
#include"ControlPanel.h"

//ポインタの保存
class Timer;
class Protecter;
class Player;

//引数
class CameraBase;
class DirectXtkComponent;


class UI
{
private:
	//敵情報描画位置
	static const DirectX::SimpleMath::Vector2 STRING_ENEMY_NUM_POSITION;
	//所持金減少エフェクトの位置
	static const DirectX::SimpleMath::Vector2 MONEY_EFFECT_POSITION;


	//現在のフェーズとフェーズの残り時間を表す
	std::unique_ptr<TimeOfDay> mpTimeOfDay;
	//所持金の下地の画像を描画
	std::unique_ptr<MoneyTexture> mpMoneyTexture;
	//フェーズのカーソルを描画
	std::unique_ptr<PhaseCursorManager> mpPhaseCursorManager;
	//危険信号表示
	std::unique_ptr<RedAssert> mpRedAssert;
	//プレイヤーの現在の状態
	std::unique_ptr<PlayerActionInfo> mpPlayerActionInfo;
	
	//所持金減少エフェクト
	std::unique_ptr<FloatNumber2D> mpDecreaseMoney;

	//スコア周りの描画
	std::unique_ptr<ScoreRender> mpScoreRender;

	//残り敵数の描画
	std::unique_ptr<DefeatEnemyRender> mpDefeatEnemyRender;

	//操作方法の描画
	std::unique_ptr<ControlPanel> mpControlPanel;


	//ポインタ保存用
	Timer* mpTimer;
	Protecter* mpProtecter;
	Player* mpPlayer;

	//内部クラスへ渡すための一時的な保存用変数
	int* mpPhaseCountNum;
	ePlayScenePhase* mpPhase;
	int mInitHP;
	//最大フェーズ数
	int mMaxPhaseNum;

	//描画するスコアの値
	int mScoreNum;

	//全ての敵の数
	int mAllEnemyNum;
	//残っている敵の数
	int mRemainingEnemyNum;

	//描画フラグ
	bool mUIDrawFlag;

public:
	//コンストラクタ
	UI();
	//デストラクタ
	~UI();


	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//UI描画に必要な情報を取得する
	void SetTimerPointer(Timer* pTimer);
	void SetPlayerPointer(Player* pPlayer);
	void SetProtecterPointer(Protecter* pProtecter);
	void SetPhaseCountPointer(int* pPhaseCount);
	void SetPhase(ePlayScenePhase* phase);
	void SetInitHP(const int& pHP);
	void SetMaxPhaseNum(const int& phasenum);

	void SetScoreNum(const int& score);
	void SetAllEnemyNum(const int& enemynum);
	void SetRemainingEnemyNum(const int& enemynum);

	//危険信号を操作する関数
	void RedAssertControl(const bool& flag);

	//描画する画像を変える関数
	void ChangeActionInfoTexture(const ePlayerActionState& state);
	void ChangeActionInfoTexture(const eWeaponType& type);
	//現在の武器の弾数を取得する関数
	void SetActionInfoStrongBulletNum(const int& num);

	//所持金を描画する関数
	void DrawMoneyTexture();

	//所持金減少エフェクトを作成する
	void CreateMoneyEffect(const int& moneynum);

	//描画フラグ
	void SetUIDrawFlag(const bool& flag){mUIDrawFlag = flag; }


	//操作方法UIの描画フラグ切り替える
	void ChangeDrawControlUIFlag();

	//操作方法描画フラグを渡す
	bool GetDrawControlUIFlag() const { return mpControlPanel->GetDrawFlag(); }

};
