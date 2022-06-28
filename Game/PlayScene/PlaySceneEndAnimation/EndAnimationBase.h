/*
終了時アニメーション処理基底クラス
作成者：杉山
作成日：2021/11/10
*/
#pragma once

//列挙型の使用
#include"EndAnimationState.h"

//所持
#include"Libraries/MyLibraries/Camera.h"

class EndAnimationBase 
{
private:

	std::unique_ptr<Camera> mpCamera;

protected:
	//コンストラクタ
	EndAnimationBase() 
		:mpCamera(nullptr)
	{
		mpCamera = std::make_unique<Camera>(); 
	}
	//デストラクタ
	virtual ~EndAnimationBase() = default;

public:

	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual bool Update() = 0;
	//描画
	virtual void Draw() = 0;

protected:
	Camera* GetCamera()const { return mpCamera.get(); }

};
