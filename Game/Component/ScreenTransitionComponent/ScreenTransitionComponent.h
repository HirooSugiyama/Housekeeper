
/*
画面遷移管理クラス(Singleton)
作成者：杉山
作成日：2021/12/28
*/
#pragma once
#include "Libraries/MyLibraries/Wipe.h"
#include "Libraries/MyLibraries/Fade.h"

#include"../../Common/ObjectTexture.h"

class ScreenTransitionComponent
{
private:
	//自分自身
	static std::unique_ptr <ScreenTransitionComponent> sTransitionInterface;

	//ワイプ
	std::unique_ptr<Wipe> mpWipe;
	//使用フラグ
	bool mWipeUseFlag;

	//フェード
	std::unique_ptr<Fade> mpFade;
	//使用フラグ
	bool mFadeUseFlag;


	//コピーコンストラクタ、コピー代入演算子をdelete。
	ScreenTransitionComponent(const ScreenTransitionComponent& sti) = delete;
	ScreenTransitionComponent operator=(const ScreenTransitionComponent& sti) = delete;

	//コンストラクタ
	ScreenTransitionComponent();

public:
	//生成処理
	static ScreenTransitionComponent& GetScreenTransitionInstance();

	//ワイプの取得
	Wipe* GetWipe()const { return mpWipe.get(); }
	//使用フラグのアクセサ
	bool GetWipeUseFlag() const { return mWipeUseFlag; }
	void SetWipeUseFlag(bool flag) { mWipeUseFlag = flag; }

	//フェードの取得
	Fade* GetFade()const { return mpFade.get(); }
	//使用フラグのアクセサ
	bool GetFadeUseFlag()const { return mFadeUseFlag; }
	void SetFadeUseFlag(bool flag) { mFadeUseFlag = flag; }

};
