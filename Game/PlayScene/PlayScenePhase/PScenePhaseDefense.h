/*
防衛フェーズ
作成者：杉山
作成日：2021/06/16
*/
#pragma once

//基底クラス
#include"PlayScenePhaseBase.h"

//所持
#include"../PlaySceneDefence/DangerousLine.h"
#include"../PlaySceneDefence/PreparingBlock.h"

#include"../PlaySceneCommon/Enemy/DetectNormalEnemy.h"
#include"../PlaySceneCommon/Enemy/DetectSubordinateEnemy.h"
#include"../PlaySceneCommon/Enemy/DetectBossEnemy.h"

class PScenePhaseDefense :public PlayScenePhaseBase
{
private:
	//現在の状態
	enum class eDefenseState
	{
		MOVE,	//移動状態
		PIXED,	//定点カメラ視点状態
	};


	//定点カメラの座標
	static const DirectX::SimpleMath::Vector3 PIXED_CAMERA_POSITION;


	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//オブジェクト
	std::unique_ptr<DangerousLine> mpDangerousLine;
	std::unique_ptr <PreparingBlock> mpSampleBlock;

	//衝突判定処理
	std::unique_ptr<DetectNormalEnemy> mpDetectNormalEnemy;
	std::unique_ptr<DetectSubordinateEnemy> mpDetectSubordinateEnemy;
	std::unique_ptr<DetectBossEnemy> mpDetectBossEnemy;

	//赤色点滅フラグ
	bool mRedAssertFlag;

	//フェーズカウント
	int mPhaseCount;

	//累計フェーズ数
	int mAllPhaseNum;

	//ショップ起動フラグ
	bool mShopOpenFlag;

	//列挙型の実体化
	eDefenseState mDefenseState;

	//移動カメラ座標保存用変数
	DirectX::SimpleMath::Vector3 mMoveCameraSavePosition;

	//ワイプフラグ
	bool mWipeFlag;

public:
	//コンストラクタ
	PScenePhaseDefense();
	//デストラクタ
	~PScenePhaseDefense();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override;

	//更新
	void Update()override;

	//State変更前のリセット処理
	void Reset()override;

	//描画
	void Draw()override;

private:

	//オブジェクトの更新処理
	void ObjectUpdate();
	//当たり判定の処理
	void ColliderUpdate();
	//オブジェクトの描画処理
	void ObjectDraw();

	//赤色点滅エフェクトをつけるかどうか
	void RedAssertSet();

	//フェーズ更新処理
	void PhaseToUpdate();

	//カメラ視点切り替え処理
	void ChangeCamera();
};