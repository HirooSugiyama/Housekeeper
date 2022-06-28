/*
数字が浮く表現を行うクラスの基底クラス
作成者：杉山
作成日：2021/10/22
*/

#pragma once


class NumberBase
{
private:

	//透明度初期値
	static const float INIT_ALPHA;
	//数字の数の最大数
	static const int MAX_NUMTYPE_NUM;


	//透明度管理変数
	float mTextureAlpha;

	//画像キー
	int mTextureKey;


protected:
	//コンストラクタ
	NumberBase();

	//デストラクタ
	virtual ~NumberBase();

public:

	//更新処理
	virtual void Update() {}

	//描画処理
	virtual void Draw() = 0;

	//画像キーのアクセサ
	void SetTextureKey(int key) { mTextureKey = key; }
	int GetTextureKey()const { return mTextureKey; }


protected:

	//取得した数字から必要な数字を選び出す
	std::vector<int> ChooseNum(int num);

	//アクセサ
	//透明度管理変数
	float GetTextureAlpha() const { return mTextureAlpha; }
	void SetTextureAlpha(float alpha) { mTextureAlpha = alpha; }

	float GetInitAlpha()const { return INIT_ALPHA; }
	int GetMaxNumTypeNum()const { return MAX_NUMTYPE_NUM; }

};
