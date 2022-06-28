/*
スプライトシートの数字を２D描画するクラス
作成者：杉山
作成日：2021/12/11
*/
#pragma once


//前方宣言
#include"../ObjectSpriteTexture.h"
#include"NumberBase.h"

enum class eAlign
{
	LEFT,
	RIGHT
};

class SpriteNumber2D :public NumberBase
{
private:

	//描画できる最大桁数
	static const int MAX_DIGIT_NUM = 5;

	//数字1枚当たりの画像サイズ
	static const RECT SPRITE_SIZE;

	//画像の拡大率
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//文字間
	static const int STRING_SPACE;


	//使用する数字のスプライト画像
	std::unique_ptr<ObjectSpriteTexture> mpNumberTexture[MAX_DIGIT_NUM];

	//対応する使用フラグ
	bool mUseFlag[MAX_DIGIT_NUM];

	//始点座標
	DirectX::SimpleMath::Vector2 mInitPosition;

	//画像中心位置
	eAlign mAlign;

	//画像のずらす幅
	float mNumShift;

	//画像拡大率
	DirectX::SimpleMath::Vector2 mTextureScale;

public:

	//コンストラクタ
	SpriteNumber2D();
	//デストラクタ
	~SpriteNumber2D()override;
	//初期化処理
	void Initialize();
	//作成処理
	void Create(const int& num, const DirectX::SimpleMath::Vector2& position);

	//描画処理
	void Draw()override;

	//各変数、定数のアクセサ
	int GetMaxDigitNum()const { return MAX_DIGIT_NUM; }

	RECT GetSpriteSize()const { return SPRITE_SIZE; }

	ObjectSpriteTexture* GetNumberTexture(int index)const { return mpNumberTexture[index].get(); }

	void SetUseFlag(int index, bool flag) { mUseFlag[index] = flag; }
	int GetUseFlag(int index)const { return mUseFlag[index]; }

	DirectX::SimpleMath::Vector2 GetInitPosition() const { return mInitPosition; }

	//拡大率を設定する
	void SetScale(float scale);

	//画像中心位置を指定する
	void SetAlign(eAlign align) { mAlign = align; }


private:
	//各変数にほしい番号を入れる
	void CreateNumber(const std::vector<int>& num);

	//文字間生成処理
	void CreateStringShift();
};
