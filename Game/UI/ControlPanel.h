/*
操作方法描画UI
作成者：杉山
作成日：2022/01/30
*/
#pragma once

#include"Game/Common/ObjectSpriteTexture.h"

class ControlPanel
{
private:

	//移動
	std::unique_ptr<ObjectSpriteTexture> mpMove;
	//攻撃
	std::unique_ptr<ObjectSpriteTexture> mpAttack;
	//切り替え
	std::unique_ptr<ObjectSpriteTexture> mpChange;
	//ポーズ
	std::unique_ptr<ObjectSpriteTexture> mpPause;
	//リスタート
	std::unique_ptr<ObjectSpriteTexture> mpReStart;

	//描画フラグ
	bool mDrawFlag;


public:

	//コンストラクタ
	ControlPanel();
	//デストラクタ
	~ControlPanel();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw();

	//ゲームパッドとキーを切り替え
	void ChangeControl();

	//描画フラグのアクセサ
	void SetDrawFlag(const bool& flag) { mDrawFlag = flag; }
	bool GetDrawFlag()const { return mDrawFlag; }

};
