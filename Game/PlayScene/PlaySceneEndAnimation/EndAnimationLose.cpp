/*
終了時アニメーション処理
負けクラス
作成者：杉山
作成日：2021/11/10
*/
#include"pch.h"
#include "EndAnimationLose.h"

//エフェクトの使用
#include"../Effect/EffectManager.h"
#include"../Effect/EffectType.h"
#include"../Effect/Effect.h"

//関数の使用
#include"../PlaySceneCommon/Protecter.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//爆破処理座標
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_FIRST(-10.f,15.f,20.f);

const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_SECOND(10.f, 15.f, 20.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_THIRD(0.f, 15.f, 20.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_FORTH(0.f, 15.f, 20.f);

//爆発サイズ
const DirectX::SimpleMath::Vector2 EndAnimationLose::EXPLOSION_SCALE_SMALL(3.f,3.f);
const DirectX::SimpleMath::Vector2 EndAnimationLose::EXPLOSION_SCALE_BIG(25.f,25.f);

//カメラ関係
const DirectX::SimpleMath::Vector3 EndAnimationLose::ENDANIM_LOSE_CAMERA_TARGET(0.f, 0.f, 10.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::ENDANIM_LOSE_CAMERA_EYE(0.f, 65.5f, 10.5f);

//カメラY値最大値
const float EndAnimationLose::CAMERA_MAX_POSITION_Y = 65.f;

//大爆発の途中
const int EndAnimationLose::EXPLOSION_FORTH_MIDDLE = 3;

//待機時間
const int EndAnimationLose::WAIT_TIME = 3;

/*===================================
コンストラクタ
引数：なし
===================================*/
EndAnimationLose::EndAnimationLose()
	:
	EndAnimationBase(),
	mState(eLoseAnimStep::NONE),
	mEffectAddress(nullptr),
	mpTimer(nullptr),
	mMiniTimer(0),
	mpProtecter(nullptr),
	mpLoseTexture(nullptr),
	mBGMID(Utility::EXCEPTION_NUM)
{
	mpTimer = std::make_unique<Timer>();
	mpLoseTexture = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
EndAnimationLose::~EndAnimationLose()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void EndAnimationLose::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__LOSE));

	mpTimer->SetMaxTime(WAIT_TIME);

	mpLoseTexture->SetTexture(texture);
	mpLoseTexture->Initialize();
}

/*===================================
更新処理
引数：なし
返り値：アニメーション終了
===================================*/
bool EndAnimationLose::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	switch (mState)
	{
		case eLoseAnimStep::NONE:
		{
			mState = eLoseAnimStep::PREPARATION;
			break;
		}		
		case eLoseAnimStep::PREPARATION:
		{
			//エフェクトマネージャーの取得
			auto pEM = EffectManager::GetInstance();
			pEM->SetCameraPointer(EndAnimationBase::GetCamera());


			//注視点とカメラ位置を調節
			EndAnimationBase::GetCamera()->SetRefEyePosition(ENDANIM_LOSE_CAMERA_EYE);
			EndAnimationBase::GetCamera()->SetRefTargetPosition(ENDANIM_LOSE_CAMERA_TARGET);
			mState = eLoseAnimStep::ROTATION_ANGLE;
			break;
		}
		case eLoseAnimStep::ROTATION_ANGLE:
		{
			EndAnimationBase::GetCamera()->Update();

			if (EndAnimationBase::GetCamera()->GetEyePosition().y > CAMERA_MAX_POSITION_Y)
			{
				//エフェクトを設定する
				this->SetEffect(EXPLOSION_POSITION_FIRST, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::FIRST_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::FIRST_EXPLOSION:
		{

			//エフェクトが終了したら
			if (!*mEffectAddress)
			{
				//エフェクトを設定する
				this->SetEffect(EXPLOSION_POSITION_SECOND, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::SECOND_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::SECOND_EXPLOSION:
		{
			if (!*mEffectAddress)
			{
				//エフェクトを設定する
				this->SetEffect(EXPLOSION_POSITION_THIRD, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::THIRD_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::THIRD_EXPLOSION:
		{
			if (!*mEffectAddress)
			{
				//エフェクトを設定する
				this->SetEffect(EXPLOSION_POSITION_FORTH, EXPLOSION_SCALE_BIG);

				mState = eLoseAnimStep::FORTH_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::FORTH_EXPLOSION:
		{
			mMiniTimer++;

			if (mMiniTimer == EXPLOSION_FORTH_MIDDLE)
			{
				mpProtecter->ChangeOldHouse();
			}

			if (!*mEffectAddress)
			{
				
				mState = eLoseAnimStep::END;
			}
			break;
		}
		case eLoseAnimStep::END:
		{
			mpTimer->Update();
			if (mpTimer->GetMaxTime() == mpTimer->GetMainTimer())
			{
				//音楽を流す
				mBGMID=ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_LOSE);

				mState = eLoseAnimStep::LOSE_TEXTURE;
			}

			break;
		}
		case eLoseAnimStep::LOSE_TEXTURE:
		{
			//決定ボタンが押されたら移動する
			if (pKey->Decision()|| pGamePad->Decision())
			{
				ADX2::GetInstance().Stop(mBGMID);
				return true;
			}

			break;
		}
		default:
		{
			throw "Exception handling";
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
void EndAnimationLose::Draw()
{
	//エフェクトの描画処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();

	//負け画像描画の段階の場合のみ描画する
	if (mState == eLoseAnimStep::LOSE_TEXTURE)
	{
		mpLoseTexture->Draw();
	}
}

/*==============================================================
エフェクトを設定する:private
引数：エフェクトを発生させる座標、エフェクト画像の拡大率
返り値：なし
================================================================*/
void EndAnimationLose::SetEffect(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 scale)
{
	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(eEffectType::BOMB);
	effect->SetPosition(position);
	effect->SetScale(scale);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
	mEffectAddress = effect->GetSpriteFlagAddress();
}
