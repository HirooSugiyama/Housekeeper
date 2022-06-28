/*
カウントダウンフェーズ
作成者：杉山
作成日：2021/09/30
*/

#include"pch.h"

#include"PScenePhaseResult.h"

//所持元
#include"../PlayScene.h"

//関数内部の使用
#include"Game/Money/Money.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/Score.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"

#include"Game/StageSelect/StageNumer.h"


//Master版フラグ
#include"Game/Master.h"

//若干のインターバル
const int PScenePhaseResult::SLIGHTLY_INTERVAL = 2;

//数字増加時間
const int PScenePhaseResult::NUM_MOVE_TIME = 1;

//スコアボーナス係数
//所持金
const int PScenePhaseResult::MONEY_CAST_BONUS = 10;
//撃破数
const int PScenePhaseResult::DEFFEAT_CAST_BONUS = 10;


//リザルト画像移動速度
const int PScenePhaseResult::TEXTURE_MOVE_VELOCITY = 30;


//共通画像の拡大率
const DirectX::SimpleMath::Vector2 PScenePhaseResult::COMMONTEXTURE_SCALE = DirectX::SimpleMath::Vector2(0.95f, 0.9f);
const DirectX::SimpleMath::Vector2 PScenePhaseResult::COMMONTEXTURE_POSITION = DirectX::SimpleMath::Vector2(-1280.f, 0.f);

/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseResult::PScenePhaseResult()
	:
	mpPlayScene(nullptr),
	mpDrawString{},
	mpCommonTexture(),
	mScoreNum(),
	mpScoreMoveNum(nullptr),
	mMoneyNum(),
	mpMoneyMoveNum(nullptr),
	mDeffeatBonusNum(),
	mpDeffeatBonusMoveNum(nullptr),
	mClearBonusNum(),
	mpClearBonusMoveNum(nullptr),
	mScoreRankingNum{},
	mpRanking{nullptr},
	mpResultInfo(nullptr),
	mNumState(eMoveNumState::NONE),
	mpTimer(nullptr)
{
	for (int i = 0; i < static_cast<int>(eResultDrawString::NUM); i++)
	{
		mpDrawString[i] = std::make_unique<MoveString>();
	}


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mpRanking[i] = std::make_unique<MoveSpriteNumber2D>();
	}


	mpScoreMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpMoneyMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpDeffeatBonusMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpClearBonusMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpTimer = std::make_unique<Timer>();
	mpResultInfo = std::make_unique<ResultInfo>();
	mpCommonTexture = std::make_unique<ObjectTexture>();
}

/*====================
デストラクタ
=====================*/
PScenePhaseResult::~PScenePhaseResult()
{
}

/*===============================
初期化処理
引数：プレイシーンのポインタ
返り値：なし
===============================*/
void PScenePhaseResult::Initialize(PlayScene* pPlayScene)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;

	//ちょっとだけ時間を置く処理の初期化処理
	mpTimer->SetMaxTime(SLIGHTLY_INTERVAL);

	mpResultInfo->Initialize(mpPlayScene->GetStageNum());

	//クリア時のボーナススコアを保存
	mClearBonusNum = PlayScenePhaseBase::GetAdministrator()->GetClearBonusScoreNum();

	//画像取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__RESULT));

	mpCommonTexture->SetTexture(texture);
	mpCommonTexture->Initialize();
	mpCommonTexture->SetScale(COMMONTEXTURE_SCALE);
	mpCommonTexture->SetPosition(COMMONTEXTURE_POSITION);

}

/*====================
リセット処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseResult::Reset()
{
	//値設定処理
	this->Configuration();
}

/*====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseResult::Update()
{
	//タイマーの取得
	const auto& pT = TimerComponent::GetTimerInstance();
	DX::StepTimer time = pT.GetTimer();

	switch (mNumState)
	{
		case eMoveNumState::NONE:
		{
			//少し間を置く
			bool flag = mpTimer->Update();

			//時間になったら次の処理へ
			if (flag)
			{
				//タイマーを次に備えてリセットしておく
				mpTimer->ResetMainTimer();

				mNumState = eMoveNumState::STRING_MOVE;
			}

			break;
		}
		case eMoveNumState::STRING_MOVE:
		{
			bool flag = this->MoveTexture();

			if (flag)
			{
				//少し間を置く
				flag = mpTimer->Update();

				//時間になったら次の処理へ
				if (flag)
				{
					//タイマーを次に備えてリセットしておく
					mpTimer->ResetMainTimer();

					mNumState = eMoveNumState::BONUS_UP;
				}
			}
			break;
		}
		case eMoveNumState::BONUS_UP:
		{
			//動く数字の更新処理
			int moneyNum = mpMoneyMoveNum->Update(time);
			int deffeatNum = mpDeffeatBonusMoveNum->Update(time);
			int clearnum = mpClearBonusMoveNum->Update(time);
			//最大値になったら次の処理へ
			if (moneyNum == mMoneyNum &&
				deffeatNum == mDeffeatBonusNum &&
				clearnum == mClearBonusNum)
			{
				//少し間を置く
				bool flag = mpTimer->Update();

				//時間になったら次の処理へ
				if (flag)
				{
					//タイマーを次に備えてリセットしておく
					mpTimer->ResetMainTimer();


					mNumState = eMoveNumState::SCORE_UP;
				}
			}

			break;
		}
		case eMoveNumState::SCORE_UP:
		{
			//動く数字の更新処理
			int num = mpScoreMoveNum->Update(time);
			//最大値になったら次の処理へ
			if (num == mScoreNum)
			{
				//少し間を置く
				bool flag = mpTimer->Update();

				//時間になったら次の処理へ
				if (flag)
				{
					//タイマーを次に備えてリセットしておく
					mpTimer->ResetMainTimer();


					mNumState = eMoveNumState::SCORE_BLINKING;
				}
			}

			break;
		}
		case eMoveNumState::SCORE_BLINKING:
		{
			bool flag = false;
			for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
			{
				int num = mpRanking[i]->Update(time);

				if (num != mScoreRankingNum[i] && !flag)
				{
					flag = true;
				}
			}
			if (!flag)
			{
				//状態を最終へ
				mNumState = eMoveNumState::PUSH_ENTER;
			}
			break;
		}
		case eMoveNumState::PUSH_ENTER:
		{
			break;
		}
	}
	//リザルト終了処理
	this->ForcedTermination();

}

/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void PScenePhaseResult::Draw()
{	
	//項目画像の描画処理
	mpCommonTexture->Draw();

	//値の描画
	this->NumDraw();
}

/*================================
値の各種設定:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseResult::Configuration()
{

	//最終スコアを算出する
	this->CalculationScore();

	//スコアランキングに値を設定する
	mpResultInfo->SetScoreRanking(mScoreNum);

	int textureKey = static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING);

	//動く数字の初期化処理
	mpScoreMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mScoreNum);
	mpScoreMoveNum->SetScale(Utility::STRING_SIZE_MEDIUM);
	mpScoreMoveNum->SetAlign(eAlign::LEFT);

	mpMoneyMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mMoneyNum);
	mpMoneyMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpMoneyMoveNum->SetAlign(eAlign::LEFT);

	mpDeffeatBonusMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mDeffeatBonusNum);
	mpDeffeatBonusMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpDeffeatBonusMoveNum->SetAlign(eAlign::LEFT);

	mpClearBonusMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mClearBonusNum);
	mpClearBonusMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpClearBonusMoveNum->SetAlign(eAlign::LEFT);


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mScoreRankingNum[i] = mpResultInfo->GetScoreRanking(i);
		mpRanking[i]->Initialize(textureKey, 0, NUM_MOVE_TIME, mScoreRankingNum[i]);
		mpRanking[i]->SetScale(Utility::STRING_SIZE_MINIMUM);
		mpRanking[i]->SetAlign(eAlign::LEFT);
	}
	//1番のみサイズ変更
	mpRanking[0]->SetScale(Utility::STRING_SIZE_MEDIUM);

}

/*=================================
各種値の描画処理:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseResult::NumDraw()
{

	if (static_cast<int>(mNumState) < static_cast<int>(eMoveNumState::BONUS_UP))
	{
		return;
	}

	//クリアボーナス値の描画
	mpClearBonusMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_CLEARBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT
	);
	mpClearBonusMoveNum->Draw();

	//残金の描画
	mpMoneyMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_MONEYBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT		
	);
	mpMoneyMoveNum->Draw();

	//撃破数ボーナス値の描画
	mpDeffeatBonusMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_DEFEATBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT	
	);
	mpDeffeatBonusMoveNum->Draw();


	if (static_cast<int>(mNumState) < static_cast<int>(eMoveNumState::SCORE_UP))
	{
		return;
	}

	//累計スコア値の描画
	mpScoreMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_SCORE_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT
	);
	mpScoreMoveNum->Draw();

	//スコアランキングの描画
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mpRanking[i]->SetPosition
		(
			ResultDrawStringConstant::SCORE_RANKING_NUM_POSITION +
			DirectX::SimpleMath::Vector2(0.f, i * ResultDrawStringConstant::SCORE_RANKING_SHIFT)
		);
		mpRanking[i]->Draw();
	}
}

/*=================================
スコアを算出する:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseResult::CalculationScore()
{
	//現在のスコアを取得
	int score= PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum();

	mDeffeatBonusNum = PlayScenePhaseBase::GetEnemyManager()->GetBreakEnemyNum();
	//撃破数に係数をかける
	int deffeatScore = mDeffeatBonusNum * DEFFEAT_CAST_BONUS;

	//現在の所持金の取得
	auto& pM = Money::GetMoneyInstance();
	mMoneyNum = pM.GetMoney();
	//残金に係数をかける
	int moneyScore = mMoneyNum * MONEY_CAST_BONUS;

	//全て足す
	mScoreNum = score + deffeatScore + moneyScore + mClearBonusNum;
}

/*=================================
値を強制移動させる:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseResult::ForcedChange()
{
	//値を強制移動
	mpClearBonusMoveNum->ForcedChangeMoveNum();
	mpMoneyMoveNum->ForcedChangeMoveNum();
	mpDeffeatBonusMoveNum->ForcedChangeMoveNum();
	mpScoreMoveNum->ForcedChangeMoveNum();

	//文字群の位置を強制移動
	for (int i = 0; i < static_cast<int>(eResultDrawString::NUM); i++)
	{
		mpDrawString[i]->ForcedChangeString();
	}
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mScoreRankingNum[i] = mpResultInfo->GetScoreRanking(i);
		mpRanking[i]->ForcedChangeMoveNum();
	}

	//画像を強制移動
	mpCommonTexture->SetPosition(DirectX::SimpleMath::Vector2::Zero);
}

/*=================================
画像移動処理:private
引数：なし
返り値：終了フラグ
=================================*/
bool PScenePhaseResult::MoveTexture()
{
	mpCommonTexture->SetPosition(mpCommonTexture->GetPosition()+ DirectX::SimpleMath::Vector2(TEXTURE_MOVE_VELOCITY,0.f));

	//もし指定位置に来たら
	if (mpCommonTexture->GetPosition().x >= 0)
	{
		mpCommonTexture->SetPosition(DirectX::SimpleMath::Vector2::Zero);
		return true;
	}
	return false;
}

/*=================================
強制終了処理:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseResult::ForcedTermination()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->Decision() || pGamePad->Decision())	//決定
	{

		if (mNumState != eMoveNumState::PUSH_ENTER)
		{
			//描画を強制移動させ
			this->ForcedChange();

			//状態を最終へ
			mNumState = eMoveNumState::PUSH_ENTER;
		}
		else
		{
			//ステージ番号保存
			this->SaveNextStageNum();
			mpResultInfo->WriteScore();

			//勝利フラグを建てる
			mpPlayScene->SetClearFlag(true);
		}
	}
}

/*===================================================
最後にクリアしたステージ番号の保存:private
引数：なし
返り値：なし
===================================================*/
void PScenePhaseResult::SaveNextStageNum()
{
	//ファイルを開く
	std::ofstream writingFile;
	writingFile.open(Utility::NEXT_STAGE_NUM_FILEPATH, std::ios::out);

	//番号を保存
	if (mpPlayScene->GetStageNum() + 1 < static_cast<int>(eSelectNum::NUM))
	{
		writingFile << mpPlayScene->GetStageNum() + 1 << std::endl;
	}
	else
	{
		writingFile << mpPlayScene->GetStageNum() << std::endl;
	}

	writingFile.close();
}
