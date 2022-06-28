/*
タイマーを管理するインターフェース
作成者：杉山
作成日：2021/10/14
*/
#pragma once

class TimerComponent
{
private:

	//自分自身
	static std::unique_ptr<TimerComponent> sTimerComponent;

	//タイマー
	DX::StepTimer mTimer;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	TimerComponent(const  TimerComponent& pv) = delete;
	TimerComponent operator=(const  TimerComponent& pv) = delete;

	//コンストラクタ
	TimerComponent();
public:
	//自身のインスタンス
	static TimerComponent& GetTimerInstance();

	//タイマーのアクセサ
	DX::StepTimer GetTimer() const { return mTimer; }
	void SetTimer(const DX::StepTimer& timer) { mTimer = timer; }

};
