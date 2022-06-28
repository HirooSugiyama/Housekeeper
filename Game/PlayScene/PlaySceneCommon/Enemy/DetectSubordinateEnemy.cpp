/*
配下敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#include"pch.h"

#include"DetectSubordinateEnemy.h"

//前方宣言
//所持
#include"SubordinateEnemy.h"

//当たり判定
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Player/ActionStateAttackEnemy.h"
#include"../Bullet/BulletManager.h"

//関数の使用
#include"Game/PlayScene/PlaySceneCommon/Administrator/Administrator.h"
#include"EnemyCommonFunction.h"


//配下敵のスコア
const int DetectSubordinateEnemy::SUBORDINATE_ENEMY_SCORE = 100;

/*===================================
コンストラクタ
引数：なし
===================================*/
DetectSubordinateEnemy::DetectSubordinateEnemy()
	:
	mpChackColliderSubordinateEnemy(),
	mEnemySize()
{
}

/*===================================
デストラクタ
===================================*/
DetectSubordinateEnemy::~DetectSubordinateEnemy()
{
}

/*=======================================================================================================
敵の回数分だけ当たり判定を回す処理(配下敵)
引数：弾管理クラスのアドレス
返り値：なし
========================================================================================================*/
void DetectSubordinateEnemy::RoolBulletManagerChackhitSubordinateEnemy(BulletManager* pBulletManager)
{
	for (int i = 0; i < mEnemySize; i++)
	{
		//当たり判定の処理を通す
		int breaknum = pBulletManager->ChackHitBulletSubordinateEnemy(mpChackColliderSubordinateEnemy[i]);

		//スコア増加
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(SUBORDINATE_ENEMY_SCORE * breaknum);
	}
}

/*===================================
ブロックと配下敵の衝突判定
引数：ブロックのアドレス
返り値：なし
===================================*/
void DetectSubordinateEnemy::ChackHitBlocklSubordinateEnemy(Block* pBlock)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//移動状態でない配下敵も処理をしない
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//衝突判定
		if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//ブロックを破壊する
			pBlock->SelfDestroy();

			//エフェクトの設定
			EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
		}
	}
}

/*===================================
プレイヤーと配下敵の衝突判定
引数：プレイヤーのアドレス
返り値：接触フラグ
===================================*/
bool DetectSubordinateEnemy::ChackHitPlayerSubordinateEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		if (mpChackColliderSubordinateEnemy[i]->GetStateMove()->GetState() == SubordinateEnemyMoveState::STAND)//立ち状態で								
		{
			if (pPlayer->GetPlayerState() == ePlayerState::WALK)//プレイヤが歩き状態ならば
			{
				//状態変更処理
				mpChackColliderSubordinateEnemy[i]->GetStateMove()->GetStand()->SetStandIntervalActiveFlag(true);
			}
			continue;
		}

		//移動状態でない配下敵も処理をしない
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//衝突判定
		if (pC.Intersect(pPlayer->GetPlayerCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//プレイヤーにダメージを与える
			pPlayer->ChangeStateDamage();

			//使用している配下敵を停止させる
			this->AllSubordinateEnemyStop();

			return true;
		}
	}
	return false;
}

/*=======================================
弱攻撃状態のプレイヤーと配下敵の衝突判定
引数：プレイヤーのアドレス
返り値：なし
========================================*/
void DetectSubordinateEnemy::ChackHitNormalAttackPlayerSubordinateEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();


	//選択肢にnullが入る可能性があるためチェックする
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return;
	//もしプレイヤーが弱攻撃状態でないならば通らない
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return;

	for (int i = 0; i < mEnemySize; i++)
	{
		//移動状態でない配下敵も処理をしない
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//衝突判定
		if (pC.Intersect(pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//弱攻撃のダメージを与える
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge = mpChackColliderSubordinateEnemy[i]->Damage(damageNum, mpChackColliderSubordinateEnemy[i]->GetEnemyHP());

			//もし敵を倒していたら
			if (breakjuge)
			{
				//スコアを増やして
				DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(SUBORDINATE_ENEMY_SCORE);
			}

			//エフェクトを設定する
			EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetPosition());
		}
	}
}

/*================================================
使用している配下敵全てを停止させる:private
引数：なし
返り値：なし
=================================================*/
void DetectSubordinateEnemy::AllSubordinateEnemyStop()
{
	for (int i = 0; i < mEnemySize; i++)
	{
		mpChackColliderSubordinateEnemy[i]->GetStateMove()->ChangeStateStand();
	}
}

