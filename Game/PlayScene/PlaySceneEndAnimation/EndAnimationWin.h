/*
終了時アニメーション処理
勝ちクラス
作成者：杉山
作成日：2021/11/10
*/
#pragma once


#include"EndAnimationBase.h"

//所持
#include"../PlaySceneCommon/Administrator/Timer.h"


class EnemyManager;
class Administrator;

class EndAnimationWin :public EndAnimationBase
{
private:

	//カメラのターゲット
	static const DirectX::SimpleMath::Vector3 ENDANIM_WIN_CAMERA_TARGET;
	static const DirectX::SimpleMath::Vector3 ENDANIM_WIN_CAMERA_EYE;

	//カメラZ値最小値
	static const float CAMERA_MIN_POSITION_Z;


	//変数
	//現在の状態
	eWinAnimStep mState;

	//タイマー
	std::unique_ptr<Timer> mpTimer;

	//ポインタ保存用変数
	EnemyManager* mpEnemyManager;
	Administrator* mpAdministrator;

public:

	//コンストラクタ
	EndAnimationWin();
	//デストラクタ
	~EndAnimationWin();


	//初期化
	void Initialize()override;
	//更新
	bool Update()override;
	//描画
	void Draw()override;

	//ポインタ保存
	void SetPointer(EnemyManager* pEnemyManager, Administrator* pAdministrator)
	{
		mpEnemyManager = pEnemyManager; 
		mpAdministrator = pAdministrator;
	}

};