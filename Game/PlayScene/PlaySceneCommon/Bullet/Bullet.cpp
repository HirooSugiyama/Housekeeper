/*
弾クラス
作成者：杉山
作成日：2021/09/17
*/
#include"pch.h"
#include"Bullet.h"

//前方宣言
#include"BulletType.h"
#include"BulletStateBase.h"

#include"../Enemy/Enemy.h"
#include"../Enemy/BossEnemy.h"
#include"../Enemy/SubordinateEnemy.h"

//呼び出し
#include "Game/PlayScene/Effect/EffectManager.h"


//当たり判定の半径
const float Bullet::COLLIDER_RADIUS = 1.f;
//当たり判定拡大係数
const float Bullet::COLLIDER_RADIUS_EXPANSION = 2.5f;

/*===================================
コンストラクタ
引数：なし
===================================*/
Bullet::Bullet()
	:
	mpBulletModel(),
	mBulletAttackNum(),
	mBulletVelocity(),
	mWeaponType(eWeaponType::NONE),
	mpStateBase(nullptr),
	mpNormalBullet(nullptr),
	mpExplosion(nullptr),
	mpBoomerangBullet(nullptr),
	mExplosionFlag(false)
{
	mpBulletModel = std::make_unique<SphereModel>();

	//状態分け
	mpNormalBullet = std::make_unique<BulletStateNormalBullet>();
	mpExplosion = std::make_unique<BulletStateExplosion>();
}

/*===================================
デストラクタ
===================================*/
Bullet::~Bullet()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void Bullet::Initialize()
{
	//未使用状態で初期化
	mpBulletModel->SetModelUseFlag(false);

	//状態分け先にポインタを保存
	mpNormalBullet->SetBuletPointer(this);
	mpExplosion->SetBuletPointer(this);
}

/*=================================
更新処理
引数：なし
返り値：なし
===================================*/
void Bullet::Update()
{
	//状態毎の移動処理を行う
	bool deleteflag = mpStateBase->Move();

	//もし範囲外に出たら
	if (deleteflag)
	{
		//ブーメランを削除する
		//アクセス権を消すだけなのでdeleteはしない。
		mpBoomerangBullet = nullptr;
		this->SelfDestroy();
	}

	//当たり判定反映処理
	this->SetCollider();

}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void Bullet::Draw()
{
	mpBulletModel->Draw();
}

/*=================================
弾作成処理
引数：出現座標、弾の種類
返り値：なし
===================================*/
void Bullet::Create(const DirectX::SimpleMath::Vector3& position, const eWeaponType& type)
{
	//使用状態にする
	mpBulletModel->SetModelUseFlag(true);

	//座標の設定
	mpBulletModel->SetPosition(position);

	//弾の種類の保存
	mWeaponType = type;

	//弾の種類によって処理を変える
	switch (mWeaponType)
	{
		case eWeaponType::MACHINE_GUN:
		case eWeaponType::PISTOL:			//NoBreak
		case eWeaponType::ROCKET_LAUNCHER://NoBreak
		{
			//通常弾の設定
			this->ChangeStateNormalBullet();

			break;
		}
		case eWeaponType::BOMB:
		{
			//爆発弾の設定
			this->ChangeStateExplosion();
			break;
		}
		case eWeaponType::BOOMERANG:
		{
			this->ChangeStateBoomerang();

			break;
		}

	}
}

/*=================================
未使用状態への変更関数
引数：なし
返り値：なし
===================================*/
void Bullet::SelfDestroy()
{
	if (mpBulletModel->GetModelUseFlag())
	{
		//当たり判定を初期値に
		mpBulletModel->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);

		//未使用状態にする
		mpBulletModel->SetModelUseFlag(false);

		//爆発フラグを下す
		mExplosionFlag = false;
	}
}

/*=================================
使用中かどうかを返すアクセサ
引数：なし
返り値：使用フラグ
===================================*/
bool Bullet::GetUseFlag()const
{
	return mpBulletModel->GetModelUseFlag();
}

/*===================================
Z座標を返す
返り値：モデルのZ座標
===================================*/
float Bullet::GetBulletPositionZ()const
{
	return mpBulletModel->GetPosition().z;
}

/*===================================
弾情報保存用関数
引数：弾情報
返り値：なし
===================================*/
void Bullet::SetBulletInfomation(const BulletInfomation& pBulletInfomation)
{
	//モデルの取得
	mpBulletModel->SetModel(pBulletInfomation.mBulletModel);

	//攻撃力の設定
	mBulletAttackNum = pBulletInfomation.mBulletAttackNum;

	//拡大率の設定
	mpBulletModel->SetScale(pBulletInfomation.mBulletScale);

	//弾の速度の設定
	mBulletVelocity = pBulletInfomation.mBulletVelocityZ;
}

/*===================================
移動処理
引数：なし
返り値：当たり判定
===================================*/
Sphere* Bullet::GetBulletModelCollider()const
{
	return mpBulletModel->GetSphereCollider();
}

/*==================================
当たり判定生成処理
引数：なし
返り値：なし
===================================*/
void Bullet::SetCollider()
{
	//簡略化用変数の宣言
	DirectX::SimpleMath::Vector3 position = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS;

	//当たり判定を設定する
	mpBulletModel->SetSphereCollider(position,scale);
}

/*=================================
当たり判定を倍にする
引数：なし
返り値：なし
===================================*/
void Bullet::SetDoubleCollider()
{
	//簡略化用変数の宣言
	DirectX::SimpleMath::Vector3 position = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS* COLLIDER_RADIUS_EXPANSION;

	//当たり判定を設定する
	mpBulletModel->SetSphereCollider(position, scale);
}


/*=================================
弾衝突時の通常敵の処理
引数：通常敵のポインタ
返り値：敵撃破フラグ
===================================*/
bool Bullet::HitNormalEnemy(Enemy* pEnemy)
{
	//撃破フラグ
	bool breakflag = false;

	//エフェクト変更用変数
	eEffectType type = eEffectType::NONE;

	//敵にダメージを与える
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());


	//弾種に応じた処理
	type = mpStateBase->HitNormalEnemy(pEnemy);


	//エフェクトを設定する
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}

/*=================================
弾衝突時のボス敵の処理
引数：ボス敵のポインタ
返り値：敵撃破フラグ
===================================*/
bool Bullet::HitBossEnemy(BossEnemy* pEnemy)
{
	//撃破フラグ
	bool breakflag = false;

	//エフェクト変更用変数
	eEffectType type = eEffectType::NONE;

	//敵にダメージを与える
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());

	//弾種に応じた処理
	type = mpStateBase->HitBossEnemy(pEnemy);

	//エフェクトを設定する
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}

/*=================================
弾衝突時の配下敵の処理
引数：配下敵のポインタ
返り値：敵撃破フラグ
===================================*/
bool Bullet::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//撃破フラグ
	bool breakflag = false;

	//エフェクト変更用変数
	eEffectType type = eEffectType::NONE;

	//敵にダメージを与える
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());

	//弾種に応じた処理
	type = mpStateBase->HitSubordinateEnemy(pEnemy);

	//エフェクトを設定する
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}



/*=================================
エフェクトを設定する:private
引数：エフェクトの種類、座標
返り値：なし
===================================*/
void Bullet::SetEffect(const eEffectType& type, const DirectX::SimpleMath::Vector3& position)
{
	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(position + DirectX::SimpleMath::Vector3::UnitY);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
}
