/*
カメラ旋回フェーズ
作成者：杉山
作成日：2021/10/11
*/

#include"pch.h"

#include"PScenePhaseEndAnimation.h"


//所持元
#include"../PlayScene.h"

//関数の使用
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"



/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseEndAnimation::PScenePhaseEndAnimation()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mUseAnim(eUseEndAnim::NONE),
	mpWinAnim(nullptr),
	mpLoseAnim(nullptr)
{
	//使用しない可能性があるためいつでも削除できるように
	mpLoseAnim = std::make_unique< EndAnimationLose>();
	mpWinAnim = std::make_unique<EndAnimationWin>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseEndAnimation::~PScenePhaseEndAnimation()
{
}

/*===================
初期化処理
引数：所有先のポインタ
返り値：なし
=====================*/
void PScenePhaseEndAnimation::Initialize(PlayScene* pPlayScene)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;

	
	mpWinAnim->SetPointer
	(
		PlayScenePhaseBase::GetEnemyManager(),
		PlayScenePhaseBase::GetAdministrator()
	);
}

/*=====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseEndAnimation::Update()
{
	bool endJuge = false;

	
	
	//アニメーションを設定する
	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			endJuge = mpLoseAnim->Update();

			if (endJuge)
			{
				//ステージ選択シーンへ
				mpPlayScene->SetClearFlag(true);
			}


			if (mpLoseAnim->GetState()==eLoseAnimStep::END)
			{
				mpPlayScene->StopBGM();
			}

			
			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			//リザルトフェーズへ
			endJuge = mpWinAnim->Update();

			if (endJuge)
			{
				mpPlayScene->ChangePhaseToResult();
				mpPlayScene->GetPhase()->Reset();
			}

			break;
		}
	}
}

/*====================
描画処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseEndAnimation::Draw()
{
	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			mpLoseAnim->Draw();

			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			mpWinAnim->Draw();
			break;
		}
	}
}

/*====================
リセット処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseEndAnimation::Reset()
{

	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			mpLoseAnim->Initialize();
			mpLoseAnim->SetProtecterPointer(PlayScenePhaseBase::GetProtecter());

			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			mpWinAnim->Initialize();

			break;
		}
	}

}