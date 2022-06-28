/*
終了演出フェーズ
作成者：杉山
作成日：2021/10/11
*/
#pragma once


//基底クラス
#include"PlayScenePhaseBase.h"

//列挙型の使用
#include"../PlaySceneEndAnimation/EndAnimationState.h"

//所持
#include"../PlaySceneEndAnimation/EndAnimationLose.h"
#include"../PlaySceneEndAnimation/EndAnimationWin.h"

//前方宣言
class EndAnimationBase;

class PScenePhaseEndAnimation :public PlayScenePhaseBase
{
private:

	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//使用するアニメーションの種類
	eUseEndAnim mUseAnim;

	//アニメーション種類
	std::unique_ptr<EndAnimationWin> mpWinAnim;
	std::unique_ptr<EndAnimationLose> mpLoseAnim;


public:
	//コンストラクタ
	PScenePhaseEndAnimation();

	//デストラクタ
	~PScenePhaseEndAnimation();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//リセット処理
	void Reset()override;


	//アクセサ
	void SetUseAnim(eUseEndAnim anim) { mUseAnim = anim; }

	

};