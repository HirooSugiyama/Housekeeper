/*
ボス敵クラス
作成者：杉山
作成日：2022/02/11
*/
#include"pch.h"

#include"BossEnemy.h"

//前方宣言
#include"State/EnemyMainStateBase.h"

//関数の使用
#include"SubordinateEnemy.h"

//認識範囲の拡大率
const float BossEnemy::RECOGITION_RANGE_SCALE = 3.f;

//ボス敵のHP
const int BossEnemy::BOSS_ENEMY_HP = 40;


/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemy::BossEnemy()
	:
	IEnemy(),
	mpPlayerRecognitionRange(),
	mpSaveSubordinateEnemy{},
	mPlayerRecognitionRangeCollider(),
	mActiveFlag(),
	mpMainState(),
	mState(),
	mpCreateBefore(),
	mpDisappearance(),
	mpMove(),
	mpAttack(),
	mpCreate()
{
	mpPlayerRecognitionRange = std::make_unique<FlatPolygon>();
	mpCreateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();
	mpMove = std::make_unique<BossEnemyMainStateMove>();
	mpAttack = std::make_unique<BossEnemyMainStateAttack>();
	mpCreate = std::make_unique<BossEnemyMainStateCreate>();
}

/*===================================
デストラクタ
===================================*/
BossEnemy::~BossEnemy()
{
}

/*===================================
初期化処理
引数：生成座標
返り値：なし
===================================*/
void BossEnemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//使用フラグを建てる
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);

	//リソースマネージャの準備
	//高さに合わせたモデルを設定する
	auto pRM = ResourceManager::GetInstance();

	//敵種に合わせたモデルを設定する
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__BOSSENEMY));

	//設定する
	IEnemy::GetEnemyModel()->SetModel(model);

	//各種座標を設定
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());	//モデル生成時ミスの修正

	//当たり判定設定
	this->SetCollider();

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


	//各状態の初期化処理
	mpCreateBefore->Initialize(this);
	mpDisappearance->Initialize(this);
	mpMove->Initialize(this);
	mpAttack->Initialize(this);
	mpCreate->Initialize(this);

	//最初は生成前状態
	this->ChangeStateCreateBefore();

	//認識範囲の初期化処理
	mpPlayerRecognitionRange->Initialize();
	mpPlayerRecognitionRange->SetScale
	(
		DirectX::SimpleMath::Vector2(RECOGITION_RANGE_SCALE, RECOGITION_RANGE_SCALE)
	);
	mpPlayerRecognitionRange->SetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__CIRCLE));
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void BossEnemy::Update()
{
	//現在の状態の更新処理
	mpMainState->Update();

	//当たり判定設定
	this->SetCollider();

	//アドレス削除処理
	this->DeleteSubordinateEnemyAddress();

	//ダメージ数値エフェクトの更新処理
	IEnemy::GetFloatNumber3D()->Update();

}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void BossEnemy::Draw()
{
	//認識範囲の描画処理
	mpPlayerRecognitionRange->Draw(IEnemy::GetEnemyModel()->GetPosition());

	//現在の状態の描画処理
	mpMainState->Draw();

	//ダメージ数値エフェクトの描画処理
	IEnemy::GetFloatNumber3D()->Draw();
}

/*==================================
配下敵のアドレス管理用変数のアクセサ
引数：配下敵の可変長配列
返り値：なし
===================================*/
void BossEnemy::SetSaveSubordinateEnemy(std::vector<SubordinateEnemy*> pSubordinateEnemy)
{
	//サイズが0なら直接挿入
	int arraySize = mpSaveSubordinateEnemy.size();

	if (arraySize == 0)
	{
		mpSaveSubordinateEnemy = pSubordinateEnemy;
	}
	else
	{
		//サイズ拡張
		mpSaveSubordinateEnemy.resize(arraySize + pSubordinateEnemy.size());
		arraySize = mpSaveSubordinateEnemy.size();
		
		//挿入
		int argumentArray = 0;
		int i = 0;
		for (i; i < arraySize && argumentArray< static_cast<int>(pSubordinateEnemy.size()); i++)
		{
			//使用中のところには入れない
			if (mpSaveSubordinateEnemy[i]!=nullptr&&mpSaveSubordinateEnemy[i]->GetUseFlag())continue;
			mpSaveSubordinateEnemy[i] = pSubordinateEnemy[argumentArray];
			argumentArray++;
		}
		
		//サイズ再設定
		mpSaveSubordinateEnemy.resize(i);
	}
}

/*==================================
当たり判定設定:private
引数：なし
返り値：なし
===================================*/
void BossEnemy::SetCollider()
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

	//認識範囲の更新
	mPlayerRecognitionRangeCollider.mCenter = position;
	mPlayerRecognitionRangeCollider.mRadius = RECOGITION_RANGE_SCALE;
}

/*==================================
ポインタ削除処理:private
引数：なし
返り値：なし
===================================*/
void BossEnemy::DeleteSubordinateEnemyAddress()
{
	//サイズが0なら直接挿入
	int arraySize = mpSaveSubordinateEnemy.size();

	for (int i = 0; i < arraySize ; i++)
	{
		if (mpSaveSubordinateEnemy[i] == nullptr)continue;

		//未使用の要素があったらnullで初期化する
		if (!mpSaveSubordinateEnemy[i]->GetUseFlag())
		{
			mpSaveSubordinateEnemy[i] = nullptr;
		}
	}
}
