/*
敵生成前State	～出現～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyCreateBeforeStateAppearance.h"

//前方宣言
#include"../../Enemy.h"
#include"Game/PlayScene/Effect/Effect.h"

//関数の使用
#include"Game/PlayScene/Effect/EffectManager.h"

//モデル移動スピード
const float EnemyCreateBeforeStateAppearance::ENEMY_MODEL_MOVE_VELOCITY = 0.02f;
//モデルY軸最大値
const float EnemyCreateBeforeStateAppearance::ENEMY_MODEL_MAX_POSITION_Y = 0.8f;

//エフェクト座標
const float EnemyCreateBeforeStateAppearance::ENEMY_APPERANCE_POSITION_Y = 0.9f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyCreateBeforeStateAppearance::EnemyCreateBeforeStateAppearance()
	:
	EnemyCreateBeforeStateBase(),
	mpCamera(nullptr),
	mpAppearanceEffect(nullptr)
{
}

/*===================================
デストラクタ
===================================*/
EnemyCreateBeforeStateAppearance::~EnemyCreateBeforeStateAppearance()
{
}
/*=================================
初期化処理
引数：敵の行動State、敵のポインタ
返り値：なし
===================================*/
void EnemyCreateBeforeStateAppearance::Initialize
(
	EnemyMainStateCreateBefore* pEnemyMainState,
	IEnemy* pEnemy
)
{
	//ポインタを保存
	EnemyCreateBeforeStateBase::SetEnemy(pEnemy);
	EnemyCreateBeforeStateBase::SetEnemyMainState(pEnemyMainState);

	//エフェクトの設定
	this->SetEffect();
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyCreateBeforeStateAppearance::Update()
{
	//型変換用変数の宣言
	DirectX::SimpleMath::Vector3 castPosition = DirectX::SimpleMath::Vector3::Zero;
	castPosition.y += ENEMY_MODEL_MOVE_VELOCITY;

	//モデルを移動させる
	EnemyCreateBeforeStateBase::GetEnemy()->GetEnemyModel()->Move(castPosition);

	//もしY軸が最大値となったら
	if (EnemyCreateBeforeStateBase::GetEnemy()->
		GetEnemyModel()->GetPosition().y >= ENEMY_MODEL_MAX_POSITION_Y)
	{
		//移動状態に変更
		EnemyCreateBeforeStateBase::GetEnemy()->ChangeStateMove();

		//エフェクト側のフラグを下す
		mpAppearanceEffect->SetSpriteFlag(false);
	}
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyCreateBeforeStateAppearance::Draw()
{
	//敵モデルの描画処理
	EnemyCreateBeforeStateBase::GetEnemy()->GetEnemyModel()->Draw();

}

/*==================================
エフェクト設定処理:private
引数：なし
返り値：なし
===================================*/
void EnemyCreateBeforeStateAppearance::SetEffect()
{
	DirectX::SimpleMath::Vector3 position = EnemyCreateBeforeStateBase::GetEnemy()->
		GetEnemyModel()->GetPosition();
	position.y = ENEMY_APPERANCE_POSITION_Y;

	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	mpAppearanceEffect = pEM->GetEffect(eEffectType::SPAWN);
	mpAppearanceEffect->SetPosition(position);
	mpAppearanceEffect->SetSpriteFlag(true);
}
