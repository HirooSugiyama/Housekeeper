/*
地面の上にあるオブジェクトの基底クラス
作成者：杉山
作成日：2021/08/19
*/
#pragma once



class IGroundObject
{

protected:
	//コンストラクタ
	IGroundObject() = default;
	//デストラクタ
	virtual ~IGroundObject() = default;
public:
	//初期化
	virtual void Initialize() = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;
};