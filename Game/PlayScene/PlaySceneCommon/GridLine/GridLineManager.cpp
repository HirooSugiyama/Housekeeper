/*
壁を置く判定用ラインをまとめるクラス
作成者：杉山
作成日：2021/08/28
*/

#include"pch.h"
#include "GridLineManager.h"


//前方宣言
#include"GridLine.h"
//当たり判定内で使用
#include"../Player/Player.h"
#include"../../PlaySceneDefence/PreparingBlock.h"


//列挙型の使用
#include"GridLineType.h"


//呼び出し先の関数を使用する影響で使用
#include"../Player/ActionStateDefenseHouse.h"
#include"../Player/Defense/DefenseActionBlockCreate.h"



//定数
//判定用ラインの数(仮)
const int GridLineManager::VERTICAL_GRID_LINE_NUM = 25;
const int GridLineManager::HORIZONTAL_GRID_LINE_NUM = 25;

//縦幅最大数
const float GridLineManager::VERTICAL_WIDTH_MAX_NUM = 40.f;
//横幅最大数		 
const float GridLineManager::HORIZONTAL_WIDTH_MAX_NUM = 50.f;


//縦幅最小値
const float GridLineManager::VERTICAL_MIN_NUM = -40.f;
//横幅最小値
const float GridLineManager::HORIZONTAL_MIN_NUM= -19.f;

//2乗する
const int GridLineManager::SQUARE = 2;

/*====================
コンストラクタ
引数：なし
=======================*/
GridLineManager::GridLineManager()
	:
	mpVerticalGridLine{},
	mpHorizontalGridLine{}
{
	//縦線の準備
	mpVerticalGridLine.resize(VERTICAL_GRID_LINE_NUM);

	int size = static_cast<int>(mpVerticalGridLine.size());
	for (int i = 0; i < size; i++)
	{
		mpVerticalGridLine[i] = std::make_unique<GridLine>();
	}

	//横線の準備
	mpHorizontalGridLine.resize(HORIZONTAL_GRID_LINE_NUM);

	size = static_cast<int>(mpHorizontalGridLine.size());

	for (int i = 0; i < size; i++)
	{
		mpHorizontalGridLine[i] = std::make_unique<GridLine>();
	}
}

/*====================
デストラクタ
=======================*/
GridLineManager::~GridLineManager()
{
}

/*====================
初期化処理
引数：なし
返り値：なし
=======================*/
void GridLineManager::Initialize()
{
	//縦線の初期化処理
	this->InitVerticalGridLine();
	//横線の初期化処理
	this->InitHorizontalGridLine();


	this->ChackHitVerticalLineHorizontalLine();

}

/*====================
描画処理
引数：なし
返り値：なし
=======================*/
void GridLineManager::Draw()
{
	//サイズの指定
	int size = static_cast<int>(mpVerticalGridLine.size());
	for (int i = 0; i < size; i++)
	{
		mpVerticalGridLine[i]->Draw();
	}


	//サイズの指定
	size = static_cast<int>(mpHorizontalGridLine.size());
	for (int i = 0; i < size; i++)
	{
		mpHorizontalGridLine[i]->Draw();
	}
}

/*======================================================
見本用ブロックとの衝突判定
引数：プレイヤーのポインタ、見本用ブロックのポインタ
返り値：なし
=========================================================*/
void GridLineManager::ChackHitPreparingBlockGridLine(Player* pPlayer, PreparingBlock* pPreparingBlock)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//編集の簡略化
	int crossnum = static_cast<int>(mIntersectionNum.size());

	pPlayer->GetDefenseHouse()->GetBlockCreate()->SetGridLineFlag(false);

	//敵の数だけ処理を回す
	for (int j = 0; j < crossnum; j++)
	{
		//当たっていたら処理をする
		if (pC.Intersect(*pPreparingBlock->GetCircleCollider(),mIntersectionNum[j]))
		{
			//ブロックを建てられないようにする
			pPlayer->GetDefenseHouse()->GetBlockCreate()->SetGridLineFlag(true);

			break;
		}

		//どの点とも触れていなかったら
		if (j == crossnum-1)
		{
			//ブロックを建てられるようにする
			pPlayer->GetDefenseHouse()->GetBlockCreate()->SetGridLineFlag(false);

			//建てられない見本モデルの壁モデルを切り替える
			pPreparingBlock->ChangeNotUseBlock();
		}
		
	}
}

/*==============================================
渡された座標から最も近い交点を算出する
引数：基準となる座標
返り値：引数に最も近い座標
=================================================*/
DirectX::SimpleMath::Vector2 GridLineManager::GetIntersectionNearPosition(const DirectX::SimpleMath::Vector2& basePosition)
{
	//返り値用変数の宣言
	DirectX::SimpleMath::Vector2 returnPosition = mIntersectionNum[0];	//最初はエラー回避のため初番を入れておく
	//算出用変数の宣言
	float calculationPosition1, calculationPosition2;

	//基点からのベクトルの長さを算出
	calculationPosition1 = 
		std::sqrtf
		(
			(std::abs(mIntersectionNum[0].x - basePosition.x)) * SQUARE +
			(std::abs(mIntersectionNum[0].y - basePosition.y)) * SQUARE
		);

	//要素数保存用変数の宣言
	int saveindex = 0;

	//簡略化用変数の宣言
	int size = static_cast<int>(mIntersectionNum.size());


	//交点群から対象に最も近い交点の座標を保存する
	for (int i = 1; i < size; i++)
	{
		//算出
		calculationPosition2 =
			std::sqrtf(
				(std::abs(mIntersectionNum[i].x - basePosition.x)) * SQUARE +
				(std::abs(mIntersectionNum[i].y - basePosition.y)) * SQUARE
			);

		//もし現段階で最も近い交点よりも距離が近い場合は
		if (calculationPosition2 < calculationPosition1)
		{
			//更新する
			calculationPosition1 = calculationPosition2;
			saveindex = i;//要素数を保存する
		}
	}

	//最も近い交点の情報を返す
	return mIntersectionNum[saveindex];
}

/*==============================
縦線の初期化処理:private
引数：なし
返り値：なし
=================================*/
void GridLineManager::InitVerticalGridLine()
{
	//サイズの省略
	int size = static_cast<int>(mpVerticalGridLine.size());
	//開始座標の設定
	float linePositionX = HORIZONTAL_MIN_NUM;
	//種類の指定
	eGridLineType lineType = eGridLineType::VERTICAL;

	for (int i = 0; i < size; i++)
	{
		mpVerticalGridLine[i]->Initialize(lineType);
		mpVerticalGridLine[i]->SetLineModelPosition(lineType,linePositionX);

		//1本の間隔=幅最大数/本数
		linePositionX += VERTICAL_WIDTH_MAX_NUM / size;
	}
}

/*==============================
横線の初期化処理:private
引数：なし
返り値：なし
=================================*/
void GridLineManager::InitHorizontalGridLine()
{
	//サイズの省略
	int size = static_cast<int>(mpHorizontalGridLine.size());
	//開始座標の設定
	float linePositionZ = VERTICAL_MIN_NUM;
	//種類の指定
	eGridLineType lineType = eGridLineType::HORIZONTAL;


	for (int i = 0; i < size; i++)
	{
		mpHorizontalGridLine[i]->Initialize(lineType);

		//1本の間隔=幅最大数/本数
		linePositionZ += HORIZONTAL_WIDTH_MAX_NUM/size;
		mpHorizontalGridLine[i]->SetLineModelPosition(lineType,linePositionZ);
	}
}

/*==============================
縦線と横線の交差判定:private
引数：なし
返り値：なし
=================================*/
void GridLineManager::ChackHitVerticalLineHorizontalLine()
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//サイズの省略
	int hSize = static_cast<int>(mpHorizontalGridLine.size());
	int vSize = static_cast<int>(mpVerticalGridLine.size());
	//保存用変数の宣言
	DirectX::SimpleMath::Vector2 savePosition = DirectX::SimpleMath::Vector2::Zero;


	//敵の数だけ処理を回す
	for (int i = 0; i < vSize; i++)
	{
		//敵の数だけ処理を回す
		for (int j = 0; j < hSize; j++)
		{
			//当たっていたら処理をする
			if (pC.Intersect(
				*mpHorizontalGridLine[j]->GetLineCollider(),
				*mpVerticalGridLine[i]->GetLineCollider(), savePosition))
			{
				mIntersectionNum.push_back(savePosition);
			}
		}
	}
}
