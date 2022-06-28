/*
モデルインターフェース
作成者：杉山
作成日：2021/04/18
*/
#pragma once



class IModel
{
protected:
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw(DirectX::SimpleMath::Matrix* world = nullptr) = 0;
};