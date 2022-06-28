/*
壁を置く判定用ラインのクラス
作成者：杉山
作成日：2021/08/28
*/
#pragma once





//列挙型の使用
#include"GridLineType.h"

//所持
#include"../ObjectModel/ObjectModel.h"

class GridLine
{
private:
	//定数

	//ラインの座標
	//X座標(盤面中心座標)
	static const float LINE_MODEL_CENTER_POSITION_X;
	//Y座標(高さ)
	static const float LINE_MODEL_POSITION_Y;
	//Z座標(盤面中心座標)
	static const float LINE_MODEL_CENTER_POSITION_Z;

	//ラインモデルの拡大率
	//共通拡大率
	static const float LINE_MODEL_SCALE_Y;
	static const DirectX::SimpleMath::Vector3 VERTICAL_LINE_MODEL_SCALE;
	static const DirectX::SimpleMath::Vector3 HORIZONTAL_LINE_MODEL_SCALE;


	//線のモデル
	std::unique_ptr<ObjectModel> mpLineModel;

	//ラインの当たり判定
	std::unique_ptr<LineSegment> mpLineCollider;


public:
	
	//コンストラクタ
	GridLine();
	//デストラクタ
	~GridLine();
	//初期化
	void Initialize(const eGridLineType& lineType);
	//描画処理
	void Draw();

	//座標を設定する
	void SetLineModelPosition(eGridLineType const& lineType,const float& position);

	//当たり判定のアクセサ
	LineSegment* GetLineCollider()const { return mpLineCollider.get(); };

private:

	//当たり判定を設定する
	void ColliderSet();

	//縦線の座標設定処理
	void SetModelPositionX(const float& positionX);
	//横線の座標設定処理
	void SetModelPositionZ(const float& positionZ);

};
