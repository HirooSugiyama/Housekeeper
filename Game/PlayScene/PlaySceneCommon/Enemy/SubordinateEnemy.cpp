/*
配下敵クラス
作成者：杉山
作成日：2022/02/11
*/
#include"pch.h"

#include"SubordinateEnemy.h"

//前方宣言
#include"State/EnemyMainStateBase.h"


//配下敵のHP
const int SubordinateEnemy::SUBORDINATE_ENEMY_HP = 5;

/*===================================
コンストラクタ
引数：なし
===================================*/
SubordinateEnemy::SubordinateEnemy()
	:
	IEnemy(),
	mpState(),
	mState(),
	mpCrateBefore(),
	mpMove(),
	mpDisappearance()
{
	mpCrateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpMove = std::make_unique<SubordinateEnemyMainStateMove>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();

	//使用フラグをおろしておく
	IEnemy::GetEnemyModel()->SetModelUseFlag(false);

	//リソースマネージャの準備
	//高さに合わせたモデルを設定する
	auto pRM = ResourceManager::GetInstance();

	//敵種に合わせたモデルを設定する
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ZONBI));

	//設定する
	IEnemy::GetEnemyModel()->SetModel(model);

	//影の初期化処理
	IEnemy::GetShadow()->WrapInitialize();
}

/*===================================
デストラクタ
===================================*/
SubordinateEnemy::~SubordinateEnemy()
{
}

/*===================================
初期化処理
引数：生成座標
返り値：なし
===================================*/
void SubordinateEnemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//使用状態とする
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);
	
	
	//各種座標を設定
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	
	//モデル生成時ミスの修正
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());
	
	//影の拡大率を決める
	IEnemy::GetShadow()->SetScale
	(
		DirectX::SimpleMath::Vector2
		(
			IEnemy::GetEnemyScale().x,
			IEnemy::GetEnemyScale().z
		)
	);	//XZ平面
	
	
	//各状態の初期化処理
	mpCrateBefore->Initialize(this);
	mpMove->Initialize(this);
	mpDisappearance->Initialize(this);
	
	//初期状態を設定
	this->ChangeStateCreateBefore();
	this->GetStateCrateBefore()->ChangeState();	

	//移動量の初期化
	IEnemy::GetEnemyModel()->Move(DirectX::SimpleMath::Vector3::Zero);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemy::Update()
{

	//現在の状態の更新処理
	mpState->Update();
	
	//当たり判定設定処理
	this->SetCollider();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemy::Draw()
{
	//現在の状態の更新処理
	mpState->Draw();

	//影の初期化処理
	IEnemy::GetShadow()->Draw(IEnemy::GetEnemyModel()->GetPosition());
}

/*==================================
当たり判定設定:private
引数：なし
返り値：なし
===================================*/
void SubordinateEnemy::SetCollider()
{
	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(IEnemy::GetEnemyScale());
	//座標を取得
	DirectX::SimpleMath::Vector3 position = IEnemy::GetEnemyModel()->GetPosition();

	//モデルの形に合わせてサイズ調整
	halfsize.y *= IEnemy::GetEnemyColliderExtendY();
	halfsize.z *= IEnemy::GetEnemyColliderExtendZ();

	//設定
	IEnemy::GetEnemyModel()->SetAABBCollider(position - halfsize, position + halfsize);
}

