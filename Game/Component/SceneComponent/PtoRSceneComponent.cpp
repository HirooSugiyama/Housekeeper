/*
プレイシーンからリザルトシーンへ情報を渡すためのインターフェース
作成者：杉山
作成日：2021/10/21
*/

#include"pch.h"
#include"PtoRSceneComponent.h"

//外部で初期化
std::unique_ptr<PtoRSceneComponent> PtoRSceneComponent::sPtoRComponent = nullptr;

/*================
コンストラクタ
引数：なし
================*/
PtoRSceneComponent::PtoRSceneComponent()
	:mScoreNum()
{
}


/*========================
インスタンスの取得
引数：なし
返り値：自身のポインタ
==========================*/
PtoRSceneComponent& PtoRSceneComponent::GetPtoRIFInstance()
{
	if (sPtoRComponent == nullptr)
	{
		sPtoRComponent.reset(new PtoRSceneComponent());
	}
	return *sPtoRComponent;
}
