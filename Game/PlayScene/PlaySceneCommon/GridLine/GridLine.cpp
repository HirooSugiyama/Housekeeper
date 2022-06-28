/*
壁を置く判定用ラインのクラス
作成者：杉山
作成日：2021/08/28
*/

#include"pch.h"
#include "GridLine.h"



//ラインの座標
//X座標(盤面中心座標)
const float GridLine::LINE_MODEL_CENTER_POSITION_X = 0.f;
//Y座標(高さ)
const float GridLine::LINE_MODEL_POSITION_Y = 0.75f;
//Z座標(盤面中心座標)
const float GridLine::LINE_MODEL_CENTER_POSITION_Z = -15.f;


//ラインモデルの拡大率
//共通拡大率
const float GridLine::LINE_MODEL_SCALE_Y = 3.f;
//縦線
const DirectX::SimpleMath::Vector3 GridLine::VERTICAL_LINE_MODEL_SCALE(0.02f, LINE_MODEL_SCALE_Y, 25.f);
//横線
const DirectX::SimpleMath::Vector3 GridLine::HORIZONTAL_LINE_MODEL_SCALE(20.f, LINE_MODEL_SCALE_Y, 0.02f);


/*====================
コンストラクタ
引数：なし
=======================*/
GridLine::GridLine()
	:
	mpLineModel(nullptr),
	mpLineCollider(nullptr)
{
	mpLineModel = std::make_unique<ObjectModel>();
	mpLineCollider = std::make_unique<LineSegment>();
}



/*====================
デストラクタ
=======================*/
GridLine::~GridLine()
{
}

/*====================
初期化処理
引数：線のタイプ
返り値：なし
=======================*/
void GridLine::Initialize(const eGridLineType& lineType)
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__PIXELMODEL));
	mpLineModel->SetModel(model);


	//線の種類に応じて処理を行う
	switch (lineType)
	{
		case eGridLineType::VERTICAL:
		{
			//拡大率を設定する
			mpLineModel->SetScale(VERTICAL_LINE_MODEL_SCALE);
			break;
		}
		case eGridLineType::HORIZONTAL:
		{
			//拡大率を設定する
			mpLineModel->SetScale(HORIZONTAL_LINE_MODEL_SCALE);
			break;
		}
	}
}

/*====================
描画処理
引数：なし
返り値：なし
=======================*/
void GridLine::Draw()
{
	//描画する
	mpLineModel->Draw();
}

/*===============================
種類に合わせた座標設定処理
引数：判定用ラインの種類、座標
返り値：なし
================================*/
void GridLine::SetLineModelPosition(const eGridLineType& lineType, const float& position)
{
	//線の種類に応じて座標設定処理を行う
	switch (lineType)
	{
		case eGridLineType::VERTICAL:
		{
			this->SetModelPositionX(position);
			break;
		}
		case eGridLineType::HORIZONTAL:
		{
			this->SetModelPositionZ(position);
			break;
		}
	}

	//座標をもとに当たり判定を設定する
	this->ColliderSet();
}

/*================================
当たり判定を設定する
引数：なし
返り値：なし
================================*/
void GridLine::ColliderSet()
{
	//簡略化用変数の宣言
	DirectX::SimpleMath::Vector3 modelPosition(DirectX::SimpleMath::Vector3::Zero), modelscale(DirectX::SimpleMath::Vector3::Zero);

	//代入用変数の宣言
	DirectX::SimpleMath::Vector2 lineStart(DirectX::SimpleMath::Vector2::Zero), lineEnd(DirectX::SimpleMath::Vector2::Zero);

	//座標を簡略化
	modelPosition = mpLineModel->GetPosition();
	//拡大率を簡略化
	modelscale = mpLineModel->GetScale();

	//座標をもとに始点を求める
	lineStart.x = modelPosition.x - modelscale.x;
	lineStart.y = modelPosition.z - modelscale.z;

	//座標をもとに終点を求める
	lineEnd.x = modelPosition.x + modelscale.x;
	lineEnd.y = modelPosition.z + modelscale.z;


	mpLineCollider->mStart = lineStart;
	mpLineCollider->mEnd = lineEnd;
}

/*================================
縦線の座標設定処理:private
引数：モデルのX座標
返り値：なし
================================*/
void GridLine::SetModelPositionX(const float& positionX)
{
	//代入用変数の準備
	DirectX::SimpleMath::Vector3 modelPosition = DirectX::SimpleMath::Vector3::Zero;
	modelPosition.x = positionX;
	modelPosition.y = LINE_MODEL_POSITION_Y;
	modelPosition.z = LINE_MODEL_CENTER_POSITION_Z;

	//座標を設定する
	mpLineModel->SetPosition(modelPosition);
}

/*=================================
横線の座標設定処理:private
引数：モデルのZ座標
返り値：なし
================================*/
void GridLine::SetModelPositionZ(const float& positionZ)
{
	//代入用変数の準備
	DirectX::SimpleMath::Vector3 modelPosition = DirectX::SimpleMath::Vector3::Zero;
	modelPosition.x = LINE_MODEL_CENTER_POSITION_X;
	modelPosition.y = LINE_MODEL_POSITION_Y;
	modelPosition.z = positionZ;

	mpLineModel->SetPosition(modelPosition);
}
