/*
基本的な弾の移動処理
作成者：杉山
作成日：2021/10/16
*/

#include"pch.h"
#include "BulletStateBoomerang.h"

//前方宣言
#include"Bullet.h"

//関数の使用
#include"../ObjectModel/SphereModel.h"
#include"../Player/Player.h"
#include"../ObjectModel/BoxModel.h"

//飛んでいく距離
const float BulletStateBoomerang::BOOMERANG_FLY_DISTANCE = 20.f;

//停滞時間
const int BulletStateBoomerang::BOOMERANG_STAGNATION = 1;

//座標最小値
const float BulletStateBoomerang::BULLET_MIN_POSITION_Z = 16.f;

//回転速度
const float BulletStateBoomerang::BULLET_ROT_VELOCITY = 12.f;

//速度減退割合
const float BulletStateBoomerang::BULLET_VELOCITY_DECLINE = 0.98f;

//最低速度
const float BulletStateBoomerang::BULLET_MIN_VELOCITY = -0.1f;


/*==================
更新処理
引数：なし
==================*/
BulletStateBoomerang::BulletStateBoomerang()
	:
	BulletStateBase(),
	mState(eBoomerangState::NONE),
	mFlyDistance(0.f),
	mBoomerangAngle(DirectX::SimpleMath::Vector3::Zero),
	mpPlayer(nullptr),
	mpTimer(nullptr),
	mOutOfRangeFlag(false),
	mFlyDistanceNum(0)
{
	mpTimer = std::make_unique<Timer>();
}

/*===============================
移動処理
引数：なし
返り値：座標限界値
(true:超えた	false ：まだ)
===============================*/
bool BulletStateBoomerang::Move()
{
	//回転処理
	this->RotBullet();

	//状態に応じて処理を変更する
	switch (mState)
	{
		case eBoomerangState::NONE:
		{
			//リセット処理
			this->Reset();

			mBoomerangVelocity = -BulletStateBase::GetBullet()->GetBulletVelocity();
			mBoomerangAngle = DirectX::SimpleMath::Vector3(0.f,0.f, mBoomerangVelocity);

			//放つ処理へ
			mState = eBoomerangState::SHOT;

			break;
		}
		case eBoomerangState::SHOT:
		{
			//設定の距離飛ぶまでは
			if (mFlyDistance < mFlyDistanceNum)
			{
				//距離を増やす
				mFlyDistance += -mBoomerangVelocity;

				//速度減退処理
				this->SlowDown();

				//座標へ反映
				BulletStateBase::GetBullet()->GetBulletModel()->Move(mBoomerangAngle);
			}
			//距離に到達したら
			else
			{
				mFlyDistanceNum = 0;

				//停滞処理へ
				mState = eBoomerangState::CALCULATION;
			}


			break;
		}
		case eBoomerangState::CALCULATION:		//プレイヤーとの向きを計算する
		{
			//調整用変数を宣言
			DirectX::SimpleMath::Vector3 distanceAngle = DirectX::SimpleMath::Vector3::Zero, position1, position2;

			//計算
			position1 = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
			position2 = mpPlayer->GetPlayerModel()->GetPosition();
			distanceAngle = position1 - position2;

			//正規化
			distanceAngle.Normalize();			

			//タイマーの更新
			mpTimer->Update();

			//最大時間となったら
			if (mpTimer->GetMainTimer() == mpTimer->GetMaxTime())
			{
				mBoomerangAngle = distanceAngle * DirectX::SimpleMath::Vector3(mBoomerangVelocity, mBoomerangVelocity, mBoomerangVelocity);
				//返ってくる処理へ
				mState = eBoomerangState::RETURN;
			}
		
			break;
		}
		case eBoomerangState::RETURN:
		{
			//速度減退処理
			this->SlowDown();

			//座標へ反映
			BulletStateBase::GetBullet()->GetBulletModel()->Move(mBoomerangAngle);

			//もし最大値を迎えたら
			if (BulletStateBase::GetBullet()->GetBulletModel()->GetPosition().z >= BULLET_MIN_POSITION_Z)
			{
				//返ってくる処理へ
				mState = eBoomerangState::NONE;
				mOutOfRangeFlag = true;
				return true;
			}

			break;
		}
		case eBoomerangState::CATCH:
		{

			//リセット処理を回す
			this->Reset();

			//プレイヤーに持たせる
			BulletStateBase::GetBullet()->GetBulletModel()->
				SetPosition(mpPlayer->GetPlayerModel()->GetPosition());

			break;
		}
	}
	return false;
}

/*==================
リセット処理
引数：なし
返り値：なし
==================*/
void BulletStateBoomerang::Reset()
{
	//停滞時間の初期化
	mpTimer->SetMaxTime(BOOMERANG_STAGNATION);
	mpTimer->ResetMainTimer();
	mFlyDistance = 0.f;
	mOutOfRangeFlag = false;
	mBoomerangAngle = DirectX::SimpleMath::Vector3::Zero;
	mBoomerangVelocity = 0.f;
	if (BulletStateBase::GetBullet() != nullptr)
	{
		BulletStateBase::GetBullet()->GetBulletModel()->SetRotationY(0);
	}	
}

/*=================================
弾衝突時の通常敵の処理
引数:通常敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateBoomerang::HitNormalEnemy(Enemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
弾衝突時のボス敵の処理
引数：ボス敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateBoomerang::HitBossEnemy(BossEnemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
弾衝突時の配下敵の処理
引数：配下敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateBoomerang::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}


/*=========================
飛距離追加:private
引数：なし
返り値：なし
==========================*/
void BulletStateBoomerang::DistanceAddValue()
{
	if (BulletStateBase::GetBullet() == nullptr)
	{
		return;
	}

	if (mState == eBoomerangState::SHOT || mState == eBoomerangState::NONE)
	{
		mFlyDistanceNum += BulletStateBase::GetBullet()->GetBulletVelocity();
	}

	//最大距離は定数
     mFlyDistanceNum = std::min(mFlyDistanceNum, BOOMERANG_FLY_DISTANCE);

}

/*==========================
弾の回転処理:private
引数：なし
返り値：なし
==========================*/
void BulletStateBoomerang::RotBullet()
{
	if (mState != eBoomerangState::CATCH)
	{
		//弾の回転処理
		BulletStateBase::GetBullet()->GetBulletModel()->SetRotationY
		(
			BulletStateBase::GetBullet()->GetBulletModel()->GetRotAngleY() + BULLET_ROT_VELOCITY
		);
	}
}

/*========================
速度減退処理:private
引数：なし
返り値：なし
==========================*/
void BulletStateBoomerang::SlowDown()
{
	//もし小さくなければ
	if (mBoomerangAngle.z<BULLET_MIN_VELOCITY)
	{
		//速度の距離減退処理
		mBoomerangAngle *= BULLET_VELOCITY_DECLINE;
	}
}
