/*
カウントダウンフェーズ
作成者：杉山
作成日：2021/09/30
*/
#pragma once

//基底クラス
#include"PlayScenePhaseBase.h"

//列挙型の使用
#include"../PlaySceneResult/ResultDrawString.h"

//定数の使用
#include"../PlaySceneResult/ResultDrawStringConstant.h"


#include"../PlaySceneResult/MoveSpriteNumber2D.h"

//所持
#include"../../Common/ObjectTexture.h"
#include"../PlaySceneResult/MoveSpriteNumber2D.h"
#include"../PlaySceneResult/MoveString.h"
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneResult/ResultInfo.h"

class PScenePhaseResult :public PlayScenePhaseBase
{
private:

	//さらに細かい状態分け
	enum class eResultState
	{
		CONFIG,	//値設定処理
		UPDATE,	//更新処理
		END,	//終了処理
	};

	enum class eMoveNumState
	{
		NONE,				//最初
		STRING_MOVE,		//文章が画面外から流れてくる
		BONUS_UP,			//BONUS値が上昇
		SCORE_UP,			//スコア値が上昇
		SCORE_BLINKING,		//ランキングに入っていたら点滅
		PUSH_ENTER,			//エンターキー長押し表示を点滅
		
	};

	//若干のインターバル
	static const int SLIGHTLY_INTERVAL;

	//数字増加時間
	static const int NUM_MOVE_TIME;


	//スコアボーナス係数
	//所持金
	static const int MONEY_CAST_BONUS;
	//撃破数
	static const int DEFFEAT_CAST_BONUS;

	//リザルト画像移動速度
	static const int TEXTURE_MOVE_VELOCITY;

	//共通画像の拡大率
	static const DirectX::SimpleMath::Vector2 COMMONTEXTURE_SCALE;
	static const DirectX::SimpleMath::Vector2 COMMONTEXTURE_POSITION;


	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//表示情報保存用変数
	//各種文字
	std::unique_ptr<MoveString> mpDrawString[static_cast<int>(eResultDrawString::NUM)];

	//共通画像
	std::unique_ptr<ObjectTexture> mpCommonTexture;

	//スコア
	int mScoreNum;
	std::unique_ptr<MoveSpriteNumber2D> mpScoreMoveNum;

	//所持金
	int mMoneyNum;
	std::unique_ptr<MoveSpriteNumber2D> mpMoneyMoveNum;

	//全撃破ボーナス
	int mDeffeatBonusNum;
	std::unique_ptr<MoveSpriteNumber2D> mpDeffeatBonusMoveNum;

	//クリアボーナス
	int mClearBonusNum;
	std::unique_ptr<MoveSpriteNumber2D> mpClearBonusMoveNum;

	//ランキングのスコア
	int mScoreRankingNum[ResultDrawStringConstant::SCORE_RANKING_STORAGE];
	std::unique_ptr<MoveSpriteNumber2D> mpRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE];

	//スコア管理
	std::unique_ptr<ResultInfo> mpResultInfo;

	//状態分け変数の実態化
	eMoveNumState mNumState;

	//時間計測用タイマー変数
	std::unique_ptr<Timer> mpTimer;

public:
	//コンストラクタ
	PScenePhaseResult();

	//デストラクタ
	~PScenePhaseResult();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override;

	//リセット処理
	void Reset()override;

	//更新
	void Update()override;

	//描画
	void Draw()override;


private:

	//値の各種設定
	void Configuration();

	//各種値の描画処理
	void NumDraw();


	//スコアを算出する
	void CalculationScore();

	//値を強制移動させる
	void ForcedChange();


	//画像移動処理
	bool MoveTexture();

	//強制終了処理
	void ForcedTermination();

	//次のステージ番号の保存
	void SaveNextStageNum();

};