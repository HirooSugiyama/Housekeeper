/*
拠点クラス
作成者：杉山
作成日：2021/05/21
*/
#pragma once

//所持
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

class Protecter
{
private:
	//定数
		//モデルの座標
	static const float PROTECTER_MODEL_POSITION_X;
	static const float PROTECTER_MODEL_POSITION_Y;
	static const float PROTECTER_MODEL_POSITION_Z;

		//モデルの拡大率
		//見た目用
	static const float PROTECTER_MODEL_SCALE_X;
	static const float PROTECTER_MODEL_SCALE_Y;
	static const float PROTECTER_MODEL_SCALE_Z;
	//モデル生成ミスの角度調整
	static const float PROTECTER_DEBUG_SHIFT_ANGLE;

	//変数
	//モデル描画クラス
	std::unique_ptr<BoxModel> mpProtecterModel;

	//HP減少フラグ
	bool mDamageFlag;


	//関数
public:
	//コンストラクタ
	Protecter();
	//デストラクタ
	~Protecter();

	//初期化
	void Initialize();
	//描画
	void Draw();

	//当たり判定を返す
	BoxModel* GetProtecterModel()const {return mpProtecterModel.get();}

	//HP減少フラグのアクセサ
	bool GetDamageFlag() const { return mDamageFlag; }
	void SetDamageFlag(const bool& flag) { mDamageFlag = flag; }

	//ぼろ家に切り替え
	void ChangeOldHouse();

};
