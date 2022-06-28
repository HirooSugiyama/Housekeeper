/*
指定された物体の影を表示するクラス
作成者：杉山
作成日：2021/09/23
*/
#pragma once


//派生元クラス
#include"FlatPolygon.h"

namespace DirectX
{
	class BasicEffect;
	struct VertexPositionTexture;
}

class Shadow:public FlatPolygon
{
private:
	//変数============================

	//関数============================

public:
	//コンストラクタ	
	Shadow();								

	//デストラクタ
	~Shadow()override;

	//ラップした初期化処理
	void WrapInitialize();

};
