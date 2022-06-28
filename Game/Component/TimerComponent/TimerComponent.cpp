/*
タイマーを管理するインターフェース
作成者：杉山
作成日：2021/10/14
*/
#include"pch.h"

//クラス外部で初期化
std::unique_ptr<TimerComponent> TimerComponent::sTimerComponent = nullptr;

/*===================================
コンストラクタ
引数：なし
===================================*/
TimerComponent::TimerComponent()
	:
	mTimer()
{
}


/*===================================
初期化処理
引数：なし
返り値：自身のポインタ
===================================*/
TimerComponent& TimerComponent::GetTimerInstance()
{

	if (sTimerComponent == nullptr)
	{
		sTimerComponent.reset(new TimerComponent());
	}
	return *sTimerComponent;
}

