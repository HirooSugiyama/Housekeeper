/*
終了時アニメーション処理
勝ちクラス
作成者：杉山
作成日：2021/11/10
*/
#include"pch.h"
#include "EndAnimationWin.h"

//エフェクトの使用
#include"../Effect/EffectManager.h"

//関数の使用
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"

//カメラのターゲット
const DirectX::SimpleMath::Vector3 EndAnimationWin::ENDANIM_WIN_CAMERA_TARGET(0.f, 0.f, -20.1f);

const DirectX::SimpleMath::Vector3 EndAnimationWin::ENDANIM_WIN_CAMERA_EYE(0.f, 65.5f, -20.f);

//カメラZ値最小値
const float EndAnimationWin::CAMERA_MIN_POSITION_Z = -20.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EndAnimationWin::EndAnimationWin()
	:
	EndAnimationBase(),
	mState(eWinAnimStep::NONE),
	mpTimer(nullptr),
	mpAdministrator(nullptr)
{
	mpTimer = std::make_unique<Timer>();
}

/*===================================
デストラクタ
===================================*/
EndAnimationWin::~EndAnimationWin()
{
}

/*==================================
初期化処理
引数：なし
返り値：なし
===================================*/
void EndAnimationWin::Initialize()
{
	mpTimer->SetMaxTime(1);
}

/*===================================
更新処理
引数：なし
返り値：アニメーション終了
===================================*/
bool EndAnimationWin::Update()
{
	switch (mState)
	{
		case eWinAnimStep::NONE:
		{
			mState = eWinAnimStep::PREPARATION;
			break;
		}
		case eWinAnimStep::PREPARATION:
		{
			//エフェクトマネージャーの取得
			auto pEM = EffectManager::GetInstance();
			pEM->SetCameraPointer(EndAnimationBase::GetCamera());

			//注視点とカメラ位置を調節
			EndAnimationBase::GetCamera()->SetRefTargetPosition(ENDANIM_WIN_CAMERA_TARGET);
			EndAnimationBase::GetCamera()->SetRefEyePosition(ENDANIM_WIN_CAMERA_EYE);

			mpAdministrator->DirectAcceserCelestialSphere()->ChangeSphereModelDay();

			mState = eWinAnimStep::SUNRISE;
			
			break;
		}
		case eWinAnimStep::SUNRISE:
		{
			mpTimer->Update();
			if (mpTimer->GetMaxTime() == mpTimer->GetMainTimer())
			{
				mState = eWinAnimStep::ROTATION_ANGLE1;
				
			}
			break;
		}
		case eWinAnimStep::ROTATION_ANGLE1:
		{
			EndAnimationBase::GetCamera()->Update();

			if (EndAnimationBase::GetCamera()->GetTargetPosition().z < CAMERA_MIN_POSITION_Z)
			{
				mState = eWinAnimStep::EXTERM_ENEMY;

				//敵を一斉爆破
				mpEnemyManager->ExplosionSimultaneousEnemy();
			}
			break;
		}
		case eWinAnimStep::EXTERM_ENEMY:
		{
			//エフェクトの描画処理
			EffectManager* pEM = EffectManager::GetInstance();
			
			//エフェクトが終了したら
			if (!pEM->ChackAllEffect())
			{
				mState = eWinAnimStep::END;
			}
			break;
		}
		case eWinAnimStep::END:
		{

			return true;

			break;
		}
	}


	return false;
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EndAnimationWin::Draw()
{
	//エフェクトの描画処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();
}
