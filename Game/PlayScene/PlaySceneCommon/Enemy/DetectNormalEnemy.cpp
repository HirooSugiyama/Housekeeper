/*
通常敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#include"pch.h"

#include"DetectNormalEnemy.h"
#include"Enemy.h"

//当たり判定
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"../../PlaySceneDefence/DangerousLine.h"
#include"../Bullet/BulletManager.h"
#include"../Player/ActionStateAttackEnemy.h"
#include "EnemyCommonFunction.h"

//敵のプレイヤー捕捉範囲
const float DetectNormalEnemy::ENEMY_CAPTURE_RANGE = 5.f;

//スコア値
const int DetectNormalEnemy::NORMAL_ENEMY_SCORE = 100;

/*=================================
コンストラクタ
引数：なし
===================================*/
DetectNormalEnemy::DetectNormalEnemy()
	:
	DetectEnemy(),
	mpChackColliderEnemy{},
	mEnemySize(),
	mBossEnemyUseFlag()
{
}

/*==================================
デストラクタ
===================================*/
DetectNormalEnemy::~DetectNormalEnemy()
{
}

/*==================================================
敵の回数分だけ当たり判定を回す処理
引数：弾管理クラスのアドレス
返り値：敵の撃破数
====================================================*/
int DetectNormalEnemy::RoolBulletManagerChackhit(BulletManager* pBulletManager)
{
	//返り値用変数
	int returnNum = 0;
	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たり判定の処理を通す
		int breaknum = pBulletManager->ChackHitBulletEnemy(mpChackColliderEnemy[i]);

		if (!mBossEnemyUseFlag)
		{
			//撃破した数だけ増加させる
			returnNum += breaknum;
		}

		//スコア増加
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(NORMAL_ENEMY_SCORE * breaknum);
	}
	return returnNum;
}

/*=======================================================================================================
ブロックと敵の衝突判定関数
引数	：pBlock(使用するブロックのアドレス)
返り値：なし
========================================================================================================*/
void DetectNormalEnemy::ChackHitBlocklEnemy(Block* pBlock)
{
	//簡略化用変数の宣言
	bool colliderFlag = false;
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が出現状態ならば通さない
		if (mpChackColliderEnemy[i]->GetEnemyMainState() == EnemyMainState::CREATE_BEFORE)continue;

		//攻撃状態の場合 
		if (mpChackColliderEnemy[i]->GetStateMove()->GetMoveState() == EnemyMoveState::WALL_ATTACK)
		{
			//攻撃している壁の場合のみ処理を行う
			if (mpChackColliderEnemy[i]->GetStateMove()->GetFirstHitBlock() == pBlock)
			{
				//攻撃処理
				mpChackColliderEnemy[i]->AttackBlock(pBlock);
			}
		}
		//攻撃状態以外の場合
		else
		{
			//敵行動Stateの当たり判定で衝突判定を取る
			colliderFlag = pC.Intersect
			(
				mpChackColliderEnemy[i]->GetStateMove()->GetAABBCollider(),
				pBlock->GetBoxModel()->GetAABBCollider()
			);

			//当たっていなかったら処理をしない
			if (!colliderFlag)continue;

			//衝突フラグを建てる
			if (mpChackColliderEnemy[i]->GetStateMove()->GetBlockHitFlag() != EnemyMainStateMove::EnemyBlockHit::HIT)
			{
				mpChackColliderEnemy[i]->GetStateMove()->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::HIT);
			}

			//壁の回避処理
			mpChackColliderEnemy[i]->AvoidanceBlock(pBlock);
		}
	}
}

/*==================================================
プレイヤーと敵の衝突判定関数
引数：プレイヤーのアドレス
返り値：接触フラグ
====================================================*/
bool DetectNormalEnemy::ChackHitPlayerEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//プレイヤーがダメージ状態なら処理をしない
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return false;

	//敵の数だけ処理を回す
	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(), pPlayer->GetPlayerCollider()))
		{
			//プレイヤーにダメージを与える
			pPlayer->ChangeStateDamage();

			return true;
		}
	}

	return false;
}

/*===================================================
プレイヤー攻撃時のプレイヤーと敵の衝突判定関数
引数：プレイヤーのアドレス
返り値：撃破数
====================================================*/
int DetectNormalEnemy::ChackHitNormalAttackPlayerEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//選択肢にnullが入る可能性があるためチェックする
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return false;
	//もしプレイヤーが弱攻撃状態でないならば通らない
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return false;

	//返り値用変数の宣言
	int returnNum{ 0 };

	//敵の数だけ処理を回す
	for (int i = 0; i < mEnemySize; i++)
	{

		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{

			//弱攻撃のダメージを与える
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge = mpChackColliderEnemy[i]->Damage(damageNum, mpChackColliderEnemy[i]->GetEnemyHP());

			//もし敵を倒していたら
			if (breakjuge)
			{
				//撃破数追加
				returnNum++;

				//スコアを増やして
				DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(NORMAL_ENEMY_SCORE);
			}
			//倒してなかったらダメージ値を表示する
			else
			{
				//エフェクトをリセットして
				mpChackColliderEnemy[i]->ResetNumberEffect();

				mpChackColliderEnemy[i]->CreateNumberEffect(mpChackColliderEnemy[i]->GetEnemyDamage());
			}

			//エフェクトを設定する
			EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition());

			//ノックバックの方向を算出する
			DirectX::SimpleMath::Vector3 knockBackVelocity =
				pPlayer->GetAttackEnemy()->GetHand()->GetColliderPosition() - pPlayer->GetPlayerModel()->GetPosition();

			//ダメージ状態に移行
			mpChackColliderEnemy[i]->ChangeStateDamage();
			//最初の状態は反動状態
			mpChackColliderEnemy[i]->GetStateDamage()->ChangeStateKnockBack();
			mpChackColliderEnemy[i]->GetStateDamage()->MoveVectorScaling(knockBackVelocity);

			//追いかけ状態とする
			mpChackColliderEnemy[i]->GetStateMove()->SetChasePlayerFlag(true);
		}
	}
	return returnNum;
}

/*===================================================
拠点と敵の衝突判定関数
引数：拠点のアドレス
返り値：なし
====================================================*/
void DetectNormalEnemy::ChackHitProtecterEnemy(Protecter* pProtecter)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たっていたら処理をする
		if (
			pC.Intersect(
				mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),
				pProtecter->GetProtecterModel()->GetAABBCollider())
			)
		{
			//敵を破壊する
			mpChackColliderEnemy[i]->SelfDestroy();


			//家の耐久値を減らす
			pProtecter->SetDamageFlag(true);
		}
	}
}

/*======================================================================
地上オブジェクトと敵の当たり判定
引数：地上オブジェクト管理クラス内の当たり判定ひとつのアドレス
返り値：なし
=======================================================================*/
void DetectNormalEnemy::ChackHitGroundObjectEnemy(AABB* pObjectCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),	//敵の当たり判定
			pObjectCollider)												//地上オブジェクトの当たり判定
			)								
		{
			//反転させる
			mpChackColliderEnemy[i]->GetStateMove()->ReverseAngle();
		}
	}
}

/*======================================================================
柵と敵の当たり判定
引数：柵の当たり判定アドレス
返り値：なし
=======================================================================*/
void DetectNormalEnemy::ChackHitWallNormalEnemy(AABB* pWallCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),	//敵の当たり判定
			pWallCollider))													//地上オブジェクトの当たり判定
		{
			//反転させる
			mpChackColliderEnemy[i]->GetStateMove()->ReverseAngle();
		}
	}
}

/*========================================
危険信号ラインと敵の当たり判定
引数：危険信号ラインのアドレス
返り値：ライン接触フラグ
=========================================*/
bool DetectNormalEnemy::ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine)
{
	//簡略化用変数の宣言
	float enemyPositionZ = 0.f, linePositionZ = 0.f;


	//発動判定用フラグの宣言
	bool effectMoveFlag = false;

	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//座標を設定する
		enemyPositionZ = mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().z;
		linePositionZ = pDangerousLine->GetLinePositionZ();

		//もし敵がラインより家側にいたらフラグを建てる
		if (enemyPositionZ > linePositionZ)
		{
			effectMoveFlag = true;
			//いる数は関係ないので抜ける
			break;
		}
	}

	return effectMoveFlag;
}

/*========================================
対象と敵の距離判定
引数：対象の座標
返り値：なし
=========================================*/
void DetectNormalEnemy::ChackDistanceTargetEnemy(const DirectX::SimpleMath::Vector3& position)
{
	//算出用変数
	float distance(0);

	//向きベクトル保存用変数
	DirectX::SimpleMath::Vector3 distanceVelocity(DirectX::SimpleMath::Vector3::Zero);

	for (int i = 0; i < mEnemySize; i++)
	{
		//敵の現在の状態が移動状態以外ならば
		if (!mpChackColliderEnemy[i]->GetStateMove()->GetChasePlayerFlag())continue;

		//距離を計測する
		distance = std::sqrtf((std::abs(position.x - mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().x)) * 2 +
			(std::abs(position.z - mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().z)) * 2);

		//一定距離におらず、追いかけ状態なら
		if (distance > ENEMY_CAPTURE_RANGE)
		{
			//通常に戻す
			mpChackColliderEnemy[i]->GetStateMove()->SetChasePlayerFlag(false);
		}
	}
}
