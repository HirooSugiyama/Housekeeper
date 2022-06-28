/*
シーンインターフェース
作成者：杉山
作成日：2021/10/21
*/
#pragma once

#include "StepTimer.h"
#include "GameMain.h"


class IScene
{
public:

	virtual ~IScene() = default;

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual eGameScene Update() = 0;

	// 描画
	virtual void Draw() = 0;

	// 終了処理
	virtual void Finalize() = 0;

protected:
	//BGMを流す
	virtual void PlayBGM() = 0;

	//BGMを止める
	virtual void StopBGM() = 0;
};