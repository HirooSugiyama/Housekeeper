/*
武器購入フェーズ
作成者：杉山
作成日：2021/09/30
*/

#include"pch.h"
#include"PScenePhaseWeaponShop.h"

//所持元
#include"../PlayScene.h"

//所持金の取得
#include"../../Money/Money.h"

//関数内部の使用
#include"../../UI/UI.h"
#include"../PlaySceneCommon/Weapon/WeaponBase.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../PlaySceneCommon/Bullet/BulletType.h"
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"
#include"Game/PlayScene/PlaySceneCommon/Bullet/BulletStateBoomerang.h"

//背面画像の初期座標
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_INIT_POSITION(0.f, 0.f);
//背面画像の拡大率
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_SCALE(1.f, 1.f);

//カーソルの座標
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_INIT_POSITION(20.f, 217.f);
//カーソルの拡大率
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_SCALE(0.25f, 0.25f);
//カーソルの移動幅
const float PScenePhaseWeaponShop::CURSOR_SHIFT = 98.f;

//点滅画像の拡大率
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_SCALE(0.3f, 0.3f);
//点滅画像の座標
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_POSITION(0.f, 0.f);

//定点カメラの座標
const DirectX::SimpleMath::Vector3 PScenePhaseWeaponShop::PIXED_CAMERA_POSITION(0.0f, 2.0f, 10.0f);

//各文字の色
const DirectX::SimpleMath::Vector4 PScenePhaseWeaponShop::STRING_COLOR(0.7f, 0.7f, 0.7f, 1.f);

//値段
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_PRICENUM_POSITION(830.f, 505.f);
//攻撃力
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_ATTACKNUM_POSITION(960.f, 575.f);
//弾数
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_BULLETNUM_POSITION(960.f, 645.f);


//点滅画像の初期切り取り座標
const RECT PScenePhaseWeaponShop::BACK_TEX_INIT_RECT{ 0,0,595,178 };


/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseWeaponShop::PScenePhaseWeaponShop()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpWeaponManager(nullptr),
	mpBackTexture(nullptr),
	mSelectWeaponNum(1),
	mpShopCursor(nullptr),
	mpBackGroundTexture(nullptr),
	mpRotWeaponSample(nullptr),
	mpFixedPointCamera(nullptr),
	mpTextureBlinking(nullptr),
	mSelectWeaponBulletNum(0),
	mSelectWeaponPrice(0),
	mSelectWeaponAttackNum(0),
	mpWeaponExplanatory(nullptr),
	mDefenceBackFlag(false),
	mpConfirmationScreen(nullptr),
	mConfirmationFlag(false)
{
	mpWeaponManager = std::make_unique<WeaponManager>();
	mpShopCursor = std::make_unique<Cursor>();
	mpBackGroundTexture = std::make_unique<ObjectTexture>();
	mpRotWeaponSample = std::make_unique<RotWeaponSample>();
	mpFixedPointCamera = std::make_unique<FixedPointCamera>();
	mpBackTexture = std::make_unique<ObjectSpriteTexture>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpWeaponExplanatory = std::make_unique<WeaponExplanatory>();
	mpConfirmationScreen = std::make_unique<ConfirmationScreen>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseWeaponShop::~PScenePhaseWeaponShop()
{
}

/*=====================
初期化処理
引数：所有先のポインタ
返り値：なし
=====================*/
void PScenePhaseWeaponShop::Initialize(PlayScene* pPlayScene)
{
	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONBACKGROUND));

	//ポインタの保存
	mpPlayScene = pPlayScene;

	//カーソルの初期化処理
	mpShopCursor->Initialize(
		static_cast<int>(PlayTexturesResouce::TEXTURE__CURSOR),
		CURSOR_INIT_POSITION,
		CURSOR_SCALE,
		CURSOR_SHIFT);

	//画像読み込み処理
	mpBackGroundTexture->Initialize();
	mpBackTexture->Initialize();

	//背景画像の初期化処理
	mpBackGroundTexture->SetTexture(texture);
	mpBackGroundTexture->SetPosition(BACKGROUND_TEXTURE_INIT_POSITION);
	mpBackGroundTexture->SetScale(BACKGROUND_TEXTURE_SCALE);

	//展示見本モデルの初期化処理
	mpRotWeaponSample->Initialize();

	//武器管理クラスの初期化処理
	mpWeaponManager->Initialize(PlayScenePhaseBase::GetBulletManager());

	//情報を対応した武器に切り替える
	this->ChangeInfoSelectWeapon();

	//点滅画像の画像設定処理
	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__BACK));
	mpBackTexture->SetTexture(texture);
	mpBackTexture->SetScale(BACK_TEX_SCALE);
	mpBackTexture->SetPosition(BACK_TEX_POSITION);
	mpBackTexture->SetRect(BACK_TEX_INIT_RECT);

	//最初はマシンガンを設定しておく(最初の項目はマシンガン固定)
	//対象のモデルを展示モデルへ
	DirectX::Model* model =
		mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
		WeaponBase::GetWeaponModel()->GetModel();

	mpRotWeaponSample->SetWeaponModel(model);

	//情報を対応した武器に切り替える
	this->ChangeInfoSelectWeapon();

	//説明文の初期化処理
	mpWeaponExplanatory->Initialize();

	//確認画面の初期化処理
	mpConfirmationScreen->Initialize(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONBUYSTRING));
}

/*=====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseWeaponShop::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//入力機器判定処理
	this->ChackControl();

	//展示見本モデルの更新処理
	mpRotWeaponSample->Update();

	//点滅処理の更新
	mpTextureBlinking->Update();

	//時間フラグ
	bool timerFlag = true;

	//確認画面の更新処理
	if (mConfirmationFlag)
	{
		timerFlag = mpConfirmationScreen->Update();
	}
	if (timerFlag)
	{
		//武器選択処理
		this->SelectWeapon();
	}
	


	//防衛へ戻る処理
	if (pKey->Back()|| pGamePad->Back())
	{
		auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();

		mDefenceBackFlag = true;
		//ワイプ処理
		if (pSTI.GetWipe()->GetState())
		{
			pSTI.SetWipeUseFlag(true);
			pSTI.GetWipe()->SetClose();
			return;
		}	
	}
	if (mDefenceBackFlag)
	{
		auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
		//各種設定する

		//防衛フェーズへ
		mpPlayScene->ChangePhaseToDefence();

		//リセット処理を行う
		mpPlayScene->GetPhase()->Reset();

		//ワイプ処理
		pSTI.SetWipeUseFlag(true);
		pSTI.GetWipe()->SetOpen();
	}
}

/*==============================
State変更前のリセット処理
引数：なし
返り値：なし
================================*/
void PScenePhaseWeaponShop::Reset()
{
	//定点カメラに移動
	mpPlayScene->ChangeFixedCamera();

	//カメラ行列を取得
	auto& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();

	//定点カメラに変更する
	mpFixedPointCamera->SetEyePosition(PIXED_CAMERA_POSITION);			//座標指定
	pPVIf.SetProjection(mpFixedPointCamera->GetProjectionMatrix());
	pPVIf.SetView(mpFixedPointCamera->GetViewMatrix());

	mDefenceBackFlag = false;

	//確認画面
	mConfirmationFlag = false;

	//ワイプ処理
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.SetWipeUseFlag(true);
	pSTI.GetWipe()->SetOpen();
}

/*================================
描画処理
引数：なし
返り値：なし
================================*/
void PScenePhaseWeaponShop::Draw()
{
	//背景の描画
	mpBackGroundTexture->Draw();

	//カーソルの描画
	mpShopCursor->Draw(true);

	//展示見本モデルの描画処理
	mpRotWeaponSample->Draw();

	//所持金の描画
	PlayScenePhaseBase::GetUI()->DrawMoneyTexture();


	//値段の描画
	Utility::DrawString(mSelectWeaponPrice, STRING_PRICENUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//攻撃力値の描画
	Utility::DrawString(mSelectWeaponAttackNum, STRING_ATTACKNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//弾数の描画
	Utility::DrawString(mSelectWeaponBulletNum, STRING_BULLETNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//説明文の描画
	mpWeaponExplanatory->Draw();
	 
	if (mpTextureBlinking->GetBlinkingFlag())
	{
		mpBackTexture->Draw();
	}


	//確認画面の更新処理
	if (mConfirmationFlag)
	{
		mpConfirmationScreen->Draw(mpTextureBlinking->GetBlinkingFlag());

	}

}

/*===============================
入力機器判定処理:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseWeaponShop::ChackControl()
{
	//ゲームパッド使用状況を取得
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	RECT rect = BACK_TEX_INIT_RECT;

	//使用中の処理
	if (pGamePadTracker->GetUseFlag())
	{
		rect.top = BACK_TEX_INIT_RECT.bottom;
		rect.bottom *= Utility::SHIFT_SPRITE_TEXTURE;
		mpBackTexture->SetRect(rect);
	}
	//パッド未使用時の処理
	else
	{
		mpBackTexture->SetRect(rect);
	}
}

/*===============================
武器を選択する:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseWeaponShop::SelectWeapon()
{
	//確認画面ではない場合のみ選択処理を行う
	if (!mConfirmationFlag)
	{
		//カーソルを下げる
		this->ShopCursorDown();

		//カーソルを上げる
		this->ShopCursorUp();
	}

	//武器を買う
	this->BuyWeapon();
}


/*=================================
カーソルをあげる:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseWeaponShop::ShopCursorUp()
{

	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver()|| pGamePad->ChangeCursorUp())
	{
		//最大ステージ数ではないなら処理を通す
		if (mSelectWeaponNum - 1 != static_cast<int>(eWeaponType::NONE))
		{
			//画像を上へ
			mpShopCursor->CursorUp();
			mSelectWeaponNum--;

			//対象のモデルを展示モデルへ
			DirectX::Model* model= 
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//情報を対応した武器に切り替える
			this->ChangeInfoSelectWeapon();

			//紹介文の変更
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));

		}
	}
}

/*=================================
カーソルをさげる:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseWeaponShop::ShopCursorDown()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectUnder()|| pGamePad->ChangeCursorDown())
	{
		//最小ステージ数ではないなら処理を通す
		if (mSelectWeaponNum + 1 != static_cast<int>(eWeaponType::NUM))
		{
			//画像を下へ
			mpShopCursor->CursorDown();
			mSelectWeaponNum++;

			//対象のモデルを展示モデルへ
			DirectX::Model* model =
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//情報を対応した武器に切り替える
			this->ChangeInfoSelectWeapon();

			//紹介文の変更
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));
		}
	}
}


/*========================================
武器を買う:private
引数：なし
返り値：なし
=========================================*/
void PScenePhaseWeaponShop::BuyWeapon()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//もし決定ボタンが押されたら
	if (pKey->Decision()|| pGamePad->Decision())
	{
		//確認画面でなければ
		if (!mConfirmationFlag)
		{
			//確認画面描画
			mConfirmationFlag = true;

			return;
		}
		//確認画面の(Yes)なら
		else if (mpConfirmationScreen->GetSelectFlag())
		{
			//お金が足りるかどうかチェック
			Money& pM = Money::GetMoneyInstance();
			int money = pM.GetMoney();

			//金額を持ってくる
			int weaponprice =
				mpWeaponManager->
				GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				GetWeaponPrice();

			//所持金のほうが多かったら処理をする
			if (!(money >= weaponprice))
			{
				//確認画面描画
				mConfirmationFlag = false;
				return;
			}

			//所持金分減らして
			pM.ReduceMoney(weaponprice);

			PlayScenePhaseBase::GetUI()->CreateMoneyEffect(weaponprice);

			//プレイヤーの武器状態を変更しておく
			PlayScenePhaseBase::GetPlayer()->ChangePlayerActionStateStrongWeapon();

			//武器を持ち変える
			PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->ChangeStrongWeapon
			(
				static_cast<eWeaponType>(mSelectWeaponNum)
			);

			//武器画像を変更する
			PlayScenePhaseBase::GetUI()->ChangeActionInfoTexture(ePlayerActionState::STRONG_WEWPON);
			PlayScenePhaseBase::GetUI()->
				ChangeActionInfoTexture(static_cast<eWeaponType>(mSelectWeaponNum));	
		
		}
		//確認画面用カーソルのタイマーをリセットする
		mpConfirmationScreen->Reset();
		//確認画面描画
		mConfirmationFlag = false;

	}
}

/*========================================
情報を対応した武器に切り替える:private
引数：なし
返り値：なし
=========================================*/
void PScenePhaseWeaponShop::ChangeInfoSelectWeapon()
{

	//対象の武器の総弾数を取得
	mSelectWeaponBulletNum = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetBulletNum();

	//対象の武器の金額を取得
	mSelectWeaponPrice = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetWeaponPrice();

	//対象の武器の攻撃力を取得
	mSelectWeaponAttackNum = PlayScenePhaseBase::GetBulletManager()->GetBulletType()->
		GetBulletInfomation(static_cast<eWeaponType>(mSelectWeaponNum))->mBulletAttackNum;
}
