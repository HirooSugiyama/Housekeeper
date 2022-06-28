/*
壁を置く判定用ラインをまとめるクラス
作成者：杉山
作成日：2021/08/28
*/
#pragma once


//前方宣言
class GridLine;

class Player;			//当たり判定で使用
class PreparingBlock;	//当たり判定で使用


class GridLineManager
{
private:
	//定数
	//判定用ラインの数(仮)
	static const int VERTICAL_GRID_LINE_NUM;
	static const int HORIZONTAL_GRID_LINE_NUM;

	//縦幅最大数
	static const float VERTICAL_WIDTH_MAX_NUM;
	//横幅最大数
	static const float HORIZONTAL_WIDTH_MAX_NUM;

	//縦幅最小値
	static const float VERTICAL_MIN_NUM;
	//横幅最小値
	static const float HORIZONTAL_MIN_NUM;

	//2乗する
	static const int SQUARE;


	//縦線
	std::vector<std::unique_ptr<GridLine>> mpVerticalGridLine;
	//横線
	std::vector<std::unique_ptr<GridLine>> mpHorizontalGridLine;

	//交差点保存用変数
	std::vector<DirectX::SimpleMath::Vector2> mIntersectionNum;


public:

	//コンストラクタ
	GridLineManager();
	//デストラクタ
	~GridLineManager();
	//初期化
	void Initialize();
	//描画処理
	void Draw();

	//見本用ブロックとの衝突判定
	void ChackHitPreparingBlockGridLine(Player* pPlayer, PreparingBlock* pPreparingBlock);


	//渡された座標から最も近い交点を算出する
	DirectX::SimpleMath::Vector2 GetIntersectionNearPosition
		(const DirectX::SimpleMath::Vector2& basePosition);


private:

	//縦線の初期化処理
	void InitVerticalGridLine();
	//横線の初期化処理
	void InitHorizontalGridLine();

	//縦線と横線の交差判定
	void ChackHitVerticalLineHorizontalLine();


};