/*
敵クラス
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>
#include "Enemy.h"

//前方宣言
#include"../../../Common/ObjectTexture.h"

//関数の使用
#include"../Block/Block.h"

//関数の使用
#include"EnemyCommonFunction.h"


//定数

//移動速度
const float Enemy::ENEMY_MOVE_SPEED = 0.01f;


//モデル描画範囲指定
const float Enemy::ENEMY_MDEL_DROW_AREA = -70.f;

//ブロック番号例外数字
const int Enemy::ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM = -1;

//敵モデルを強制的に横に向ける(向き反転する際に使用)
const float Enemy::ENEMY_MODEL_FORCED_BESIDE = 270.f;

//敵のHP
const int Enemy::ENEMY_HP = 20;

//反転数
const int Enemy::REVERSE_NUM = 2;

//攻撃力
const int Enemy::ENEMY_ATTACK_NUM = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
Enemy::Enemy()
	: 
	IEnemy(),
	mMovePhaseNumber(),

	mpMainState(nullptr),
	mpCreateBefore(nullptr),
	mpMove(nullptr),
	mpDamage(nullptr),
	mpDisappearance(nullptr),
	mState(EnemyMainState::CREATE_BEFORE),
	mEnemyModelAngle(eAngleEnemy::STRAIGHT)
	
{
	//モデルを設定する
	this->SetEnemyModel();

	mpCreateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpMove = std::make_unique<EnemyMainStateMove>();
	mpDamage = std::make_unique<EnemyMainStateDamage>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();

}

/*===================================
デストラクタ
===================================*/
Enemy::~Enemy()
{
}

/*=================================
初期化
引数：初期座標
返り値：なし
===================================*/
void Enemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//未使用状態とする
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);

	//各種座標を設定
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());	//モデル生成時ミスの修正

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(IEnemy::GetEnemyScale());
	//モデルの形に合わせてサイズ調整
	halfsize.y *= IEnemy::GetEnemyColliderExtendY();
	halfsize.z *= IEnemy::GetEnemyColliderExtendZ();

	//設定
	IEnemy::GetEnemyModel()->SetAABBCollider(position - halfsize, position + halfsize);

	//影の初期化処理
	IEnemy::GetShadow()->WrapInitialize();
	//影の拡大率を決める
	IEnemy::GetShadow()->SetScale
	(
		DirectX::SimpleMath::Vector2
		(
			IEnemy::GetEnemyScale().x,
			IEnemy::GetEnemyScale().z
		)
	);	//XZ平面

	//それぞれの状態の初期化
	mpCreateBefore->Initialize(this);
	mpMove->Initialize(this);
	mpDamage->Initialize(this);
	mpDisappearance->Initialize(this);


	//最初の状態は待機処理
	this->ChangeStateCreateBefore();

}

/*===================================
更新
引数：なし
返り値：なし
===================================*/
void Enemy::Update()
{
	//使用中の時のみ通す
	if (IEnemy::GetEnemyModel()->GetModelUseFlag())
	{
		//Stateで管理された移動処理を行う
		mpMainState->Update();

		/*当たり判定の更新*/
		//ここでは保存してないためモデルから呼び出す。
		DirectX::SimpleMath::Vector3 modelPosition, modelscale;
		modelPosition = IEnemy::GetEnemyModel()->GetPosition();
		modelscale = IEnemy::GetEnemyModel()->GetScale();
		//拡大率の半分の値を生成
		DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(modelscale);
		//モデルの形に合わせてサイズ調整
		halfsize.y *= IEnemy::GetEnemyColliderExtendY();
		halfsize.z *= IEnemy::GetEnemyColliderExtendZ();
		//設定
		IEnemy::GetEnemyModel()->SetAABBCollider(modelPosition - halfsize, modelPosition + halfsize);
	}

	//ダメージ数値エフェクトの更新処理
	IEnemy::GetFloatNumber3D()->Update();
}

/*===================================
描画
引数：なし
返り値：なし
===================================*/
void Enemy::Draw()
{
	//未使用時は処理をしない
	if (!IEnemy::GetEnemyModel()->GetModelUseFlag())return;


	//モデルが指定範囲に入っていたら描画する
	if (IEnemy::GetEnemyModel()->GetPosition().z >= ENEMY_MDEL_DROW_AREA)
	{
		//影の描画
		IEnemy::GetShadow()->Draw(IEnemy::GetEnemyModel()->GetPosition());

		//State先の描画
		mpMainState->Draw();
	}

	//ダメージ数値エフェクトの描画処理
	IEnemy::GetFloatNumber3D()->Draw();
}


/*=================================================
ブロック攻撃処理:private
引数：ブロックのポインタ
返り値：なし
===================================================*/
void Enemy::AttackBlock(Block* pBlock)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//衝突判定
	bool flag = false;
	flag = pC.Intersect
	(
		mpMove->GetAABBCollider(),
		pBlock->GetBoxModel()->GetAABBCollider()
	);

	//当たっていない場合の処理
	if (!flag)
	{
		//初めて当たった壁情報を削除する
		mpMove->SetFirstHitBlock(nullptr);
		//衝突フラグを初期化
		mpMove->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NONE);
		//当たっていない壁は攻撃できないため、移動処理とする
		mpMove->ChangeStateWalk();
		return;
	}

	//攻撃するタイミングではなかったら
	if (!mpMove->AttackFlag())return;

	//ブロックにダメージを与える
	bool blockHP = pBlock->BlockDamage(ENEMY_ATTACK_NUM);

	//エフェクトを設定する
	EnemyCommonFunction::SetEnemyEffect(eEffectType::CLAW, pBlock->GetBoxModel()->GetPosition());

	//もしブロックのHPがなかったら
	if (blockHP)
	{
		//ブロックを破壊する
		pBlock->SelfDestroy();

		//初めて当たった壁情報を削除する
		mpMove->SetFirstHitBlock(nullptr);

		//衝突フラグを初期化
		mpMove->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NONE);

		//エフェクトの設定
		EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
ブロック回避処理:private
引数：ブロックのポインタ
返り値：なし
===================================================*/
void Enemy::AvoidanceBlock(Block* pBlock)
{
	//ブロック番号を取得
	Block* block = mpMove->GetFirstHitBlock();

	//2度反転しており、対象のブロックが最初に触れたブロックならば
	if (block == pBlock && mpMove->GetReverseNum() >= REVERSE_NUM)
	{
		//攻撃状態とする
		mpMove->ChangeStateWallAttack();

		//ブロックの使用情報を保存する
		mpMove->SetAttackBlock(pBlock->GetBlockUseFlagAddress());
	}

	//その他の内容が入っていたら処理をしない
	else if (block != nullptr)return;

	//もし敵が歩行していたら
	if (mpMove->GetMoveState() == EnemyMoveState::WALK)
	{
		//回転に切り替える
		mpMove->ChangeStateRotation();

		//壁のアドレスを保存する
		mpMove->SetFirstHitBlock(pBlock);
	}
}



/*===================================
移動処理
引数：なし
返り値：なし
===================================*/
void Enemy::Move()
{
	DirectX::SimpleMath::Vector3 vel;
	vel.z = ENEMY_MOVE_SPEED;

	IEnemy::GetEnemyModel()->Move(vel);
}


/*===================================
モデルを設定する:private
引数：なし
返り値：なし
===================================*/
void Enemy::SetEnemyModel()
{
	//リソースマネージャの準備
	//高さに合わせたモデルを設定する
	auto pRM = ResourceManager::GetInstance();

	//敵種に合わせたモデルを設定する
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ZONBI));

	//設定する
	IEnemy::GetEnemyModel()->SetModel(model);
}


