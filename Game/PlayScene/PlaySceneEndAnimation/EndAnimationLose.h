/*
終了時アニメーション処理
負けクラス
作成者：杉山
作成日：2021/11/10
*/
#pragma once


#include"EndAnimationBase.h"


//所持
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../../Common/ObjectTexture.h"

class Protecter;
class ObjectTexture;

class EndAnimationLose :public EndAnimationBase
{
private:

	//定数

	//爆破処理座標
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_FIRST;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_SECOND;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_THIRD;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_FORTH;

	//爆発サイズ
	static const DirectX::SimpleMath::Vector2 EXPLOSION_SCALE_SMALL;
	static const DirectX::SimpleMath::Vector2 EXPLOSION_SCALE_BIG;

	//カメラのターゲット
	static const DirectX::SimpleMath::Vector3 ENDANIM_LOSE_CAMERA_TARGET;
	static const DirectX::SimpleMath::Vector3 ENDANIM_LOSE_CAMERA_EYE;

	//カメラY値最大値
	static const float CAMERA_MAX_POSITION_Y;

	//大爆発の途中
	static const int EXPLOSION_FORTH_MIDDLE;

	//待機時間
	static const int WAIT_TIME;


	//現在の状態
	eLoseAnimStep mState;

	//エフェクトアドレス保存用変数
	bool* mEffectAddress;

	//タイマー
	std::unique_ptr<Timer> mpTimer;

	int mMiniTimer;

	//ポインタ保存用変数
	Protecter* mpProtecter;

	//負け画像
	std::unique_ptr<ObjectTexture> mpLoseTexture;

	//BGMのID
	int mBGMID;

public:

	//コンストラクタ
	EndAnimationLose();
	//デストラクタ
	~EndAnimationLose();


	//初期化
	void Initialize()override;
	//更新
	bool Update()override;
	//描画
	void Draw()override;

	void SetProtecterPointer(Protecter* pProtecter) { mpProtecter = pProtecter; }

	//現在の状態の取得
	eLoseAnimStep GetState()const { return mState; }

private:

	//エフェクト設定
	void SetEffect(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Vector2 scale);

};