/*
敵基本State　　～生成前～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMainStateCreateBefore.h"

//前方宣言
#include"../Enemy.h"

//生成前の高さ
const float EnemyMainStateCreateBefore::ENEMY_INIT_POSITION_Y = -1.5f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMainStateCreateBefore::EnemyMainStateCreateBefore()
	:EnemyMainStateBase()
	, mpState()
	, mState(EnemyCreateBeforeState::SINKING)
	, mpSinking()
	, mpAppearance()
{
	mpSinking = std::make_unique<EnemyCreateBeforeStateSinking>();
	mpAppearance = std::make_unique<EnemyCreateBeforeStateAppearance>();
}

/*===================================
デストラクタ
===================================*/
EnemyMainStateCreateBefore::~EnemyMainStateCreateBefore()
{
}

/*===================================
初期化処理
引数：敵のポインタ
返り値：なし
===================================*/
void EnemyMainStateCreateBefore::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);

	//各種状態の初期化処理
	mpSinking->Initialize(this, pEnemy);
	mpAppearance->Initialize(this, pEnemy);

	//高さ設定
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Move
	(
		DirectX::SimpleMath::Vector3(0.f, ENEMY_INIT_POSITION_Y, 0.f)
	);

	//最初は沈没状態
	this->ChangeStateSinking();
}

/*=================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateCreateBefore::Update()
{
	//現在の状態の処理
	mpState->Update();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateCreateBefore::Draw()
{
	//現在の状態の処理
	mpState->Draw();

	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

/*===================================
状態を変更する
引数：なし
返り値：なし
===================================*/
void EnemyMainStateCreateBefore::ChangeState()
{
	//沈没状態ならば
	if (mState == EnemyCreateBeforeState::SINKING)
	{
		//出現状態とする
		this->ChangeStateAppearance();
	}
}
