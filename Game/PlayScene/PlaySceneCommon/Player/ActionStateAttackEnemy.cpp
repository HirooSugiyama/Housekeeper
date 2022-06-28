/*
プレイヤーの行動状態分けステートパターン
作成者：杉山
作成日：2021/09/14
*/

#include"pch.h"
#include "ActionStateAttackEnemy.h"


//前方宣言
#include"../Weapon/WeaponBase.h"
#include"../Weapon/WeaponManager.h"
#include"../Bullet/BulletManager.h"
#include"../../../UI/UI.h"

//関数内部の閲覧のため使用
#include"../ObjectModel/BoxModel.h"
#include"../Bullet/BulletStateBoomerang.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//プレイヤーの座標と武器モデルの座標の差
const DirectX::SimpleMath::Vector3 ActionStateAttackEnemy::WEPON_MODEL_PLAYER_SHIFT_POSITION(0.5f, 0.f, 1.f);


/*=====================================
コンストラクタ
引数：なし
=====================================*/
ActionStateAttackEnemy::ActionStateAttackEnemy()
	:
	ActionStateBase(),
	mpHand(nullptr),
	mpStrongWeapon(nullptr),
	mpPlayer(nullptr),
	mpWeaponManager(nullptr),
	mpBulletManager(nullptr),
	mUseWeapon(eWeaponType::NONE),
	mAttackFlag(false),
	mMachinGunSEID(Utility::EXCEPTION_NUM)
{
	//弱攻撃は固定武器
	mpHand = std::make_unique<WeaponHand>();
}

/*=====================================
デストラクタ
=====================================*/
ActionStateAttackEnemy::~ActionStateAttackEnemy()
{

}

/*=====================================
初期化処理
引数：プレイヤーのポインタ
返り値：なし
=====================================*/
void ActionStateAttackEnemy::Initialize(Player* pPlayer)
{
	//ポインタの保存
	mpPlayer = pPlayer;
	mpHand->SetPlayerPointer(mpPlayer);

	//各攻撃処理の初期化
	mpHand->Initialize();
}

/*=====================================
更新処理
引数：なし
返り値：なし
=====================================*/
void ActionStateAttackEnemy::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	//現在の状態に応じた処理を行う
	switch (mpPlayer->GetActionState())
	{
		case ePlayerActionState::BLOCK_CREATE: {break;}

		//弱攻撃の場合
		case ePlayerActionState::ATTACK_ENEMY:
		{
			//もし弱攻撃の入力があり、待機状態なら
			if ((pKey->ActionWeekAttack()|| pGamePad->ActionPlayer()) && mpHand->GetAttackFlag()== eHandState::STAND_BY)
			{	
				//各攻撃処理の更新処理
				mpHand->SetAttackFlag(eHandState::ATTACK);
				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_ATTACK_NORMALATTACK);
			}
			//更新処理は常時通す
			mpHand->Update();

			break;
		}
		//強攻撃の場合
		case ePlayerActionState::STRONG_WEWPON:
		{
			//強い攻撃の処理を行う
			this->StrongWeaponAttack();

			if (mpStrongWeapon == nullptr)
			{
				//プレイヤー側の変更
				mpPlayer->ChangePlayerActionStateAttackEnemy();

				//Ui側の変更
				mpPlayer->GetUIPointer()->ChangeActionInfoTexture(eWeaponType::NONE);
				mpPlayer->GetUIPointer()->ChangeActionInfoTexture(ePlayerActionState::ATTACK_ENEMY);

			}

			mpHand->SetCollider(true);

			break;
		}

	}
}

/*=====================================
State開始時の初期化処理
引数：なし
返り値：なし
=====================================*/
void ActionStateAttackEnemy::Reset()
{
	
}

/*===================================
描画処理
引数：なし
返り値：なし
=====================================*/
void ActionStateAttackEnemy::Draw()
{
	//現在の状態に応じた処理を行う
	switch (mpPlayer->GetActionState())
	{
		case ePlayerActionState::BLOCK_CREATE: {break; }

		//弱攻撃の場合					
		case ePlayerActionState::ATTACK_ENEMY:
		{
			mpHand->Draw();

			break;
		}
		//強攻撃の場合
		case ePlayerActionState::STRONG_WEWPON:
		{
			if (mpStrongWeapon != nullptr)
			{
				//武器描画
				mpStrongWeapon->SetPosition(mpPlayer->GetPlayerModel()->GetPosition() + WEPON_MODEL_PLAYER_SHIFT_POSITION);
				mpStrongWeapon->Draw();
			}

			break;
		}
	}
}

/*===========================
強い武器を持ち変える
引数：武器種番号
返り値：なし
=============================*/
void ActionStateAttackEnemy::ChangeStrongWeapon(const eWeaponType& weapon)
{
	//装備している武器を変える
	mUseWeapon = weapon;
	mpStrongWeapon = mpWeaponManager->GetWeapon(weapon);

	//武器をリセットする
	mpStrongWeapon->Reset();

	mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());

	//弾を対応した弾に変更する
	mpBulletManager->SetWeaponType(mUseWeapon);

	mpBulletManager->GetBoomerangBullet()->ChangeBoomerangState(eBoomerangState::NONE);
	mpBulletManager->GetBoomerangBullet()->Reset();


}

/*=====================================
強い攻撃の攻撃処理:private
引数：なし
返り値：なし
=====================================*/
void ActionStateAttackEnemy::StrongWeaponAttack()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//サウンド再生情報を取得する
	ADX2& pSound = ADX2::GetInstance();

	bool shotFlag = false;

	switch (mUseWeapon)
	{
		case eWeaponType::NONE:
		{
			//何もしない
			break;
		}
		case eWeaponType::MACHINE_GUN:
		{
			//スペースが押しされていたら
			if (pKey->PressActionStrongAttack()|| pGamePad->ActionPlayer())
			{
				//弾を作成する
				shotFlag = true;
				if (pSound.ChackPlay(mMachinGunSEID))
				{
					//mMachinGunSEID = pSound.Play(CRI_CUESHEET_0_SE_SHOT_MACHINEGUN);
				}			
			}

			//再生中の場合音を停止する
			else //if (pSound.ChackPlay(mMachinGunSEID))
			{
				pSound.Stop(mMachinGunSEID);
			}

			break;
		}
		case eWeaponType::BOMB:
		{
			//スペースが単発押しされたら
			if (pKey->PushActionStrongAttack()||pGamePad->AttackStrongPlayer())
			{
				//弾を作成する
				shotFlag = true;	

			}

			break;
		}
		case eWeaponType::ROCKET_LAUNCHER:
		{
			//スペースが単発押しされたら
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//弾を作成する
				shotFlag = true;

			}
			break;
		}
		case eWeaponType::PISTOL:
		{
			//スペースが単発押しされたら
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//弾を作成する
				shotFlag = true;
			}

			break;
		}
		case eWeaponType::BOOMERANG:
		{
			//スペースが単発押しされたら
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//弾を作成する
				shotFlag = true;
			}
			//ブーメラン専用処理
			this->BoomerangUpdate();

			break;
		}
	}
	if (shotFlag)
	{
 		mpStrongWeapon->Shot();

		//残弾数表示を更新
		mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());

		//ブーメラン以外なら
		if (mUseWeapon != eWeaponType::BOOMERANG)
		{
			//もし弾切れならば
			if (mpStrongWeapon->Destroy())
			{
				//削除する
				mpStrongWeapon = nullptr;

				//再生中の場合音を停止する
				if (mMachinGunSEID != Utility::EXCEPTION_NUM && mUseWeapon == eWeaponType::MACHINE_GUN)
				{
					pSound.Stop(mMachinGunSEID);
					mMachinGunSEID = Utility::EXCEPTION_NUM;
				}
			}
		}		
	}
	
}

/*====================================
ブーメラン専用処理：private
引数：なし
返り値：なし
=====================================*/
void ActionStateAttackEnemy::BoomerangUpdate()
{
	//もしブーメランが場外に出たら
	if (mpBulletManager->GetBoomerangBullet()->GetOutOfRangeFlag())
	{
		//削除する
		dynamic_cast<WeaponBoomerang*>(mpStrongWeapon)->DownSecondFlag();
		mpStrongWeapon = nullptr;
		mpBulletManager->GetBoomerangBullet()->Reset();
		
	}

	if (mpBulletManager->GetBoomerangBullet()->GetBoomerangState() == eBoomerangState::CATCH)
	{
		//武器をリセットする
		mpStrongWeapon->Reset();
		mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());
	}
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->PressActionStrongAttack()|| pGamePad->ActionPlayer())
	{
		mpBulletManager->GetBoomerangBullet()->DistanceAddValue();
	}
}
