/*
プレイヤークラス
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>

#include "Player.h"

//前方宣言
//State処理分け
#include"PStateStand.h"
#include"PStateWalk.h"
#include"PStateDamage.h"

//ActionState処理分け
#include"ActionStateDefenseHouse.h"
#include"ActionStateAttackEnemy.h"


//ポインタ保存用
#include"../Block/BlockManager.h"
#include"../Administrator/Administrator.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../../../UI/UI.h"

//初期座標
const DirectX::SimpleMath::Vector3 Player::PLYAER_INIT_POSITION(0.5f,1.f,1.f);

//モデルの拡大率
	//見た目用
const DirectX::SimpleMath::Vector3 Player::PLAYER_MODEL_SCALE(0.5f, 0.5f, 0.5f);

//プレイヤーは縦長なので当たり判定を縦に伸ばす
const float Player::PLAYER_COLLIDER_EXTEND_Y = 3.f;
//実際のプレイヤーのZ値はとても小さいので小さくする
const float Player::PLAYER_COLLIDER_EXTEND_Z = 0.2f;

//シールドパニッシュ用ゲージ必要量
const int Player::BLOCKBREAK_USE_GAUGENUM = 50;


//シールドパニッシュ用拡大率
const DirectX::SimpleMath::Vector3 Player::BLOCKBREAK_SCALE(30.f, 5.f, 0.5f);


/*===================================
コンストラクタ
引数：なし
===================================*/
Player::Player()
	: 
	mpAnimationPlayerModel(),
	mpPreparingBlock(nullptr),
	mpBlockManager(nullptr),
	mpAdministrator(nullptr),
	mpUI(nullptr),
	mpStand(nullptr),
	mpWalk(nullptr),
	mpDamage(nullptr),
	mpPlayerState(nullptr),
	mState(ePlayerState::STAND),
	mpDefenseHouse(nullptr),
	mpAttackEnemy(nullptr),
	mpPlayerActionState(nullptr),
	mActionState(ePlayerActionState::BLOCK_CREATE),
	mOneFrameBeforePosition(DirectX::SimpleMath::Vector3::Zero),
	mpPlayerShadow(nullptr),
	mPlayerAttackWorldMatrix(DirectX::SimpleMath::Matrix::Identity)
{
	//状態オブジェクトを生成

	mpStand = std::make_unique<PStateStand>();
	mpWalk = std::make_unique<PStateWalk>();
	mpDamage = std::make_unique<PStateDamage>();



	mpDefenseHouse = std::make_unique<ActionStateDefenseHouse>();
	mpAttackEnemy = std::make_unique<ActionStateAttackEnemy>();
	mpPlayerShadow = std::make_unique<Shadow>();


	mpAnimationPlayerModel = std::make_unique<AnimationModel>();
}

/*===================================
デストラクタ
===================================*/
Player::~Player()
{
}

/*===================================
初期化処理
引数	：pBlockManager(ブロック管理クラスのポインタ)、pAdministrator(管理者クラスのポインタ)
		　pPreparingBlock(見本ブロックのポインタ)、pUI(UIのポインタ)
返り値：なし
===================================*/
void Player::Initialize
(
	BlockManager* pBlockManager,
	Administrator* pAdministrator,
	PreparingBlock* pPreparingBlock,
	UI* pUI
)
{
	//ポインタの保存
	mpBlockManager = pBlockManager;
	mpAdministrator = pAdministrator;
	mpPreparingBlock = pPreparingBlock;
	mpUI = pUI;

	//モデル設定
	mpAnimationPlayerModel->Initialize(static_cast<int>(PlayModelsResouce::MODEL__ANIMATIONMODEL_PLAYERSTAND));

	//モデルの初期色は青色に
	DirectX::SimpleMath::Vector3 color = DirectX::Colors::Blue;
	mpAnimationPlayerModel->SetColor(color);

	//プレイヤー
	mpAnimationPlayerModel->GetModel()->SetScale(PLAYER_MODEL_SCALE);
	mpAnimationPlayerModel->GetModel()->SetPosition(PLYAER_INIT_POSITION);

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = PLAYER_MODEL_SCALE / 2.f;
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	halfsize.z *= PLAYER_COLLIDER_EXTEND_Z;


	//設定
	mPlayerCollider.mMin = PLYAER_INIT_POSITION - halfsize;
	mPlayerCollider.mMax = PLYAER_INIT_POSITION + halfsize;

	//状態オブジェクトの初期化処理
	mpStand->Initialize(this);
	mpWalk->Initialize(this);
	mpDamage->Initialize(this);

	//行動状態オブジェクトの初期化処理
	mpDefenseHouse->Initialize(this);
	mpDefenseHouse->SetCreateBlockPointer(mpPreparingBlock, mpBlockManager);
	mpAttackEnemy->Initialize(this);

	//影クラスの初期化処理
	mpPlayerShadow->WrapInitialize();

	//影のサイズ指定
	mpPlayerShadow->SetScale(DirectX::SimpleMath::Vector2(PLAYER_MODEL_SCALE.x, PLAYER_MODEL_SCALE.z));



	//最初は立ち状態に設定
	this->ChangeStateStand();

	//最初は壁建て処理で設定
	this->ChangePlayerActionStateDefenseHouse();
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void Player::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();
	const auto& pTimerComponent = TimerComponent::GetTimerInstance();

	//モデルの更新処理
	mpAnimationPlayerModel->Update(static_cast<float>(pTimerComponent.GetTimer().GetElapsedSeconds()));

	//立ち状態ならば
	if (mState == ePlayerState::STAND)	//モデル描画の都合上ここで移動処理をする。
	{

		//入力があれば	
		if (pKey->Walk()||pGamePad->Move())//コントローラー上の操作
		{
			this->ChangeStateWalk();//歩き状態へ移行
		}
	}

	//現在の状態の更新処理
	mpPlayerState->Update();
	mpPlayerActionState->Update();

	//行動State変更処理
	this->ChangeAction();

	//攻撃用ワールド座標計算
	this->CalculationAttackMat();

	//当たり判定更新処理
	this->UpdateCollider();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void Player::Draw()
{

	//歩き状態の時はスプライトのモデルを描画する
	if (mState!=ePlayerState::STAND)
	{
		//現在の状態の描画処理
		mpPlayerState->Draw();
	}
	else 
	{
		mpAnimationPlayerModel->Draw();
	}

	//影クラスの描画処理
	mpPlayerShadow->Draw(mpAnimationPlayerModel->GetModel()->GetPosition());
}


/*===================================
終了処理
引数：なし
返り値：なし
===================================*/
void Player::Finalize()
{
	//状態オブジェクトをリセット
	mpStand.reset();
	mpWalk.reset();
	mpDamage.reset();
}


/*===================================
当たり判定更新処理:pirivate
引数：なし
返り値：なし
===================================*/
void Player::UpdateCollider()
{
	/*当たり判定の更新*/
	//ここでは保存してないためモデルから呼び出す。
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	modelpos = mpAnimationPlayerModel->GetModel()->GetPosition();
	modelscale = mpAnimationPlayerModel->GetModel()->GetScale();

	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = modelscale / 2.f;
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	//設定
	mPlayerCollider.mMin = modelpos - halfsize;
	mPlayerCollider.mMax = modelpos + halfsize;
}

/*===========================
行動State変更:pirivate
引数：なし
返り値：なし
============================*/
void Player::ChangeAction()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//ボタンを押していなければ処理をしない
	if (pKey->SwitchToWeapon() == false && pGamePad->ChangePlayerWeapon() == false)return;

	//状態に応じて変更する
	switch (mActionState)
	{
		case ePlayerActionState::BLOCK_CREATE:
		{
			//キーが押されたら
			if (pKey->ChangeActionRight() || pGamePad->ChangePlayerActionRight())
			{
				this->ChangePlayerActionStateAttackEnemy();
				mpUI->ChangeActionInfoTexture(mActionState);
			}		
			break;
		}
		case ePlayerActionState::ATTACK_ENEMY:
		{
			//キーが押されたら
			if ((pKey->ChangeActionRight() || pGamePad->ChangePlayerActionRight()) &&
				mpAttackEnemy->GetStrongWeapon() != nullptr)
			{
				this->ChangePlayerActionStateStrongWeapon();
				mpUI->ChangeActionInfoTexture(mActionState);
			}
			else if(pKey->ChangeActionLeft() || pGamePad->ChangePlayerActionLeft())
			{
				this->ChangePlayerActionStateDefenseHouse();
				mpUI->ChangeActionInfoTexture(mActionState);
			}		
			break;
		}
		case ePlayerActionState::STRONG_WEWPON:
		{
			//キーが押されたら
			if (pKey->ChangeActionLeft() || pGamePad->ChangePlayerActionLeft())
			{
				this->ChangePlayerActionStateAttackEnemy();
				mpUI->ChangeActionInfoTexture(mActionState);
			}
			
			break;
		}
	}
}

/*==========================================
攻撃用ワールド座標の計算:pirivate
引数：なし
返り値：なし
===========================================*/
void Player::CalculationAttackMat()
{
	mPlayerAttackWorldMatrix = 
		mpAnimationPlayerModel->GetModel()->GetRotationX() *
		mpAnimationPlayerModel->GetModel()->GetRotationY() *
		mpAnimationPlayerModel->GetModel()->GetRotationZ() *
		DirectX::SimpleMath::Matrix::CreateTranslation(mpAnimationPlayerModel->GetModel()->GetPosition());
}
