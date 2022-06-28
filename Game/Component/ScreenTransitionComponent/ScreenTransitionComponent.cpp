/*
画面遷移管理クラス(Singleton)
作成者：杉山
作成日：2021/12/28
*/

#include"pch.h"

//クラス外部で初期化
std::unique_ptr <ScreenTransitionComponent> 
	ScreenTransitionComponent::sTransitionInterface = nullptr;

/*===================================
コンストラクタ
引数：なし
===================================*/
ScreenTransitionComponent::ScreenTransitionComponent()
	:
	mpWipe(),
	mWipeUseFlag(false),
	mpFade(),
	mFadeUseFlag(false)
{
	mpWipe = std::make_unique<Wipe>();
	mpFade = std::make_unique<Fade>();
}



/*===================================
初期化処理
引数：なし
返り値：自身のポインタ
===================================*/
ScreenTransitionComponent& ScreenTransitionComponent::GetScreenTransitionInstance()
{

	if (sTransitionInterface == nullptr)
	{
		sTransitionInterface.reset(new ScreenTransitionComponent());
	}
	return *sTransitionInterface;
}