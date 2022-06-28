/*
プレイシーン
作成者：杉山
作成日：2021/10/21
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

#include"PlaySceneCommon/Wall/WallManager.h"
#include"PlaySceneCommon/Player/Player.h"
#include"PlaySceneCommon/Enemy/EnemyManager.h"
#include"PlaySceneCommon/Protecter.h"
#include"PlaySceneCommon/Administrator/Administrator.h"
#include"PlaySceneDefence/PreparingBlock.h"
#include"PlaySceneCommon/Ground.h"
#include"PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"PlaySceneCommon/GridLine/GridLineManager.h"
#include"PlaySceneCommon/Weapon/WeaponManager.h"
#include"PlaySceneCommon/Bullet/BulletManager.h"
#include"PlaySceneCommon/DamageTimer.h"
#include"PlaySceneCommon/Block/BlockManager.h"
#include"../UI/UI.h"
#include"Libraries/MyLibraries/FixedPointCamera.h"
#include"Libraries/MyLibraries/Camera.h"
#include"Libraries/MyLibraries/RotationCamera.h"
#include"PlayScenePhase/Pause.h"

//状態切り替え基底クラス
#include"PlayScenePhase/PlayScenePhaseBase.h"

//状態切り替え派生クラス
#include"PlayScenePhase/PScenePhaseDefense.h"
#include"PlayScenePhase/PScenePhaseCountDown.h"
#include"PlayScenePhase/PScenePhaseRotationCamera.h"
#include"PlayScenePhase/PScenePhaseResult.h"
#include"PlayScenePhase/PScenePhaseWeaponShop.h"
#include"PlayScenePhase/PScenePhaseEndAnimation.h"	
#include"PlayScenePhase/Pause.h"	



//ステート管理
#include"PlayScenePhase/PlayScenePhase.h"

//前方宣言
namespace DirectX
{
	class BasicEffect;
}

//オブジェクト関係
class WallManager;


//状態基底クラス
class PlayScenePhaseBase;
//カメラ基底クラス
class CameraBase;

class PlayScene : public IScene
{
private:

	//ライトが照らす方向
	static const DirectX::SimpleMath::Vector3 LIGHT_DIRECTION;

	//カメラ
	CameraBase* mpCamera;
	std::unique_ptr<FixedPointCamera> mpFixedCamera;
	std::unique_ptr<Camera> mpMainCamera;
	std::unique_ptr<RotationCamera> mpRotCamera;

	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mpInputLayout;

	//どのフェーズでも使用するゲームオブジェクト
	//壁管理
	std::unique_ptr<WallManager> mpWallManager;
	//プレイヤー
	std::unique_ptr<Player>	mpPlayer;
	//敵管理
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//ブロック管理
	std::unique_ptr<BlockManager> mpBlockManager;
	//家
	std::unique_ptr<Protecter> mpProtecter;
	//管理者クラス
	std::unique_ptr<Administrator> mpAdministrator;
	//地上
	std::unique_ptr<Ground> mpGround;
	//地上オブジェクト管理
	std::unique_ptr<GroundObjectManager> mpGroundObjectManager;
	//グリッド線管理
	std::unique_ptr<GridLineManager> mpGridLineManager;
	//武器管理
	std::unique_ptr<WeaponManager> mpWeaponManager;
	//弾管理
	std::unique_ptr <BulletManager> mpBulletManager;
	//UI管理
	std::unique_ptr <UI> mpUI;

	//state
	std::vector<std::unique_ptr<PlayScenePhaseBase>> mpPhaseVector;

	//Phaseパターンのため生ポインタ
	PlayScenePhaseBase* mpPSPhase;
	//管理用変数
	ePlayScenePhase mPlayScenePhase;

	//フェーズカウント
	int mPhaseCount;

	//累計フェーズ数
	int mAllPhaseNum;

	//クリアフラグ
	bool mClearFlag;

	//Retryフラグ
	bool mRetryFlag;

	//ステージ番号
	std::string mStageNumber;

	//BGMのID
	int mBGMID;

	//ポーズ中
	bool mPauseFlag;

	//ポーズ処理
	std::unique_ptr<Pause> mpPause;

public:

	/*===========================基底クラスで宣言済みの関数===========================*/

	// コンストラクタ
	PlayScene();

	// デストラクタ
	~PlayScene();

	// 初期化
	void Initialize() override;

	// 更新
	eGameScene Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

	//クリアフラグを建てる
	void SetClearFlag(bool flag) { mClearFlag = flag; }
	void SetRetryFlag(bool flag) { mRetryFlag = flag; }
	bool GetPauseFlag()const { return mPauseFlag; }


	/*===========================State関係の関数===========================*/
private:
	//Phase切り替え用アクセサ
	void ChangePhaseToRotationCamera()
	{
		mPlayScenePhase = ePlayScenePhase::ROTATION_CAMERA;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
public:
	void ChangePhaseToEndAnimation()
	{ 
		mPlayScenePhase = ePlayScenePhase::END_ANIMATION;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToCountDown() 
	{
		mPlayScenePhase = ePlayScenePhase::COUNTDOWN;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToDefence() 
	{ 
		mPlayScenePhase = ePlayScenePhase::DEFENCE;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToResult()
	{
		mPlayScenePhase = ePlayScenePhase::RESULT;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToWeaponShop() 
	{
		mPlayScenePhase = ePlayScenePhase::WEAPON_SHOP;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	PlayScenePhaseBase* GetPhase() const { return mpPSPhase; }

	//ステージ番号の取得
	int GetStageNum() { return atoi(mStageNumber.c_str()); }

	//カメラ変更処理
	void ChangeMainCamera() { mpCamera = (CameraBase*)mpMainCamera.get(); }
	void ChangeRotCamera() { mpCamera = (CameraBase*)mpRotCamera.get(); }
	void ChangeFixedCamera() { mpCamera = (CameraBase*)mpFixedCamera.get(); }
	//カメラを取得
	CameraBase* GetCameraPointer() const { return mpCamera; }

	PScenePhaseEndAnimation* GetEndAnimation()
	{
		return  (PScenePhaseEndAnimation*)mpPhaseVector[static_cast<int>(ePlayScenePhase::END_ANIMATION)].get();
	}

	//最大フェーズ数の取得
	int GetMaxPhaseNum()const { return mAllPhaseNum; }


	//BGMを止める
	void StopBGM()override;


	/*===========================関数内を分割した関数===========================*/
private:

	//インターフェースから情報を取得
	void IntarfaceGetInfomation();

	//オブジェクトの初期化
	void InitializeObject();
	//オブジェクトの更新、描画関係の処理はState先にて

	//共通の描画処理
	void DrawCommon();

	//オブジェクトの終了処理
	void FinalizeObject();

	//読み込む地形オブジェクトを管理するCSVファイルを指定する関数
	std::string CreateLoadGroundObjectFileName(std::string stagenum);

	//FPS表示
	void DEBUGString();

	//BGMを流す
	void PlayBGM()override;

	//ポーズ処理
	void PauseUpdate();

	//リスタート
	void ReStart();

};