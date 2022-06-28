/*
ステージセレクト画面からプレイシーンへ情報を渡すためのインターフェース
作成者：杉山
作成日：2021/10/21
*/

#include"pch.h"
#include"StoPSceneComponent.h"

//外部で初期化
std::unique_ptr<StoPSceneComponent> StoPSceneComponent::sStoPComponent = nullptr;


/*================
コンストラクタ
引数：なし
================*/
StoPSceneComponent::StoPSceneComponent()
	:
	mCSVFileName("none"),
	mStageNumber("-1")
{
}


/*================================
インスタンスの取得
引数：なし
返り値：自身のポインタ
================================*/
StoPSceneComponent& StoPSceneComponent::GetStoPIFInstance()
{
	if (sStoPComponent == nullptr)
	{
		sStoPComponent.reset(new StoPSceneComponent());
	}
	return *sStoPComponent;
}
