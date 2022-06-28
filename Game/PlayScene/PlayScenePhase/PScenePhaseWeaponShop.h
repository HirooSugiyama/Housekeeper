/*
武器購入フェーズ
作成者：杉山
作成日：2021/09/30
*/
#pragma once

//基底クラス
#include"PlayScenePhaseBase.h"

//所持
#include"../PlaySceneCommon/Weapon/WeaponManager.h"
#include"../../Common/ObjectTexture.h"
#include"../../Common/ObjectSpriteTexture.h"
#include"../PlaySceneShop/RotWeaponSample.h"
#include"Libraries/MyLibraries/FixedPointCamera.h"
#include"../PlaySceneShop/WeaponExplanatory.h"
#include"../../Common/Cursor.h"
#include"../../Common/Blinking.h"

#include"../../Common/ConfirmationScreen.h"


//前方宣言

class BulletManager;			//ポインタ保存用変数
class ActionStateAttackEnemy;	//ポインタ保存用変数
class Cursor;
class Blinking;

class PScenePhaseWeaponShop :public PlayScenePhaseBase
{
private:

	//背面画像の初期座標
	static const DirectX::SimpleMath::Vector2 BACKGROUND_TEXTURE_INIT_POSITION;
	//背面画像の拡大率
	static const DirectX::SimpleMath::Vector2 BACKGROUND_TEXTURE_SCALE;

	//カーソルの拡大率
	static const DirectX::SimpleMath::Vector2 CURSOR_INIT_POSITION;
	//カーソルの座標
	static const DirectX::SimpleMath::Vector2 CURSOR_SCALE;
	//カーソルの移動幅
	static const float CURSOR_SHIFT;

	//点滅画像の拡大率
	static const DirectX::SimpleMath::Vector2 BACK_TEX_SCALE;
	//点滅画像の座標
	static const DirectX::SimpleMath::Vector2 BACK_TEX_POSITION;
	//点滅画像の初期切り取り座標
	static const RECT BACK_TEX_INIT_RECT;

	//定点カメラの座標
	static const DirectX::SimpleMath::Vector3 PIXED_CAMERA_POSITION;

	//各文字の色
	static const DirectX::SimpleMath::Vector4 STRING_COLOR;

	//各文字の描画座標
	//値段
	static const DirectX::SimpleMath::Vector2 STRING_PRICENUM_POSITION;
	//攻撃力
	static const DirectX::SimpleMath::Vector2 STRING_ATTACKNUM_POSITION;
	//弾数
	static const DirectX::SimpleMath::Vector2 STRING_BULLETNUM_POSITION;


	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//武器管理クラス
	std::unique_ptr<WeaponManager> mpWeaponManager;

	//戻るキー描画画像
	std::unique_ptr<ObjectSpriteTexture> mpBackTexture;

	//現在選択している武器番号
	int mSelectWeaponNum;

	//カーソル
	std::unique_ptr<Cursor> mpShopCursor;

	//背景画像
	std::unique_ptr<ObjectTexture> mpBackGroundTexture;

	//展示見本モデル
	std::unique_ptr<RotWeaponSample> mpRotWeaponSample;

	//定点カメラ
	std::unique_ptr<FixedPointCamera> mpFixedPointCamera;

	//点滅クラス
	std::unique_ptr<Blinking> mpTextureBlinking;

	//現在選択している武器の総弾数
	int mSelectWeaponBulletNum;
	//現在選択している武器の値段
	int mSelectWeaponPrice;
	//現在選択している武器の威力
	int mSelectWeaponAttackNum;

	//武器解説文
	std::unique_ptr<WeaponExplanatory> mpWeaponExplanatory;

	//確認画面
	std::unique_ptr<ConfirmationScreen> mpConfirmationScreen;

	//防衛状態に戻るフラグ
	bool mDefenceBackFlag;

	//確認画面描画フラグ
	bool mConfirmationFlag;

public:


	//コンストラクタ
	PScenePhaseWeaponShop();

	//デストラクタ
	~PScenePhaseWeaponShop();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override ;

	//更新
	void Update()override; 

	//State変更前のリセット処理
	void Reset()override;

	//描画
	void Draw()override;

private:
	//入力機器判定処理
	void ChackControl();

	//武器を選択する
	void SelectWeapon();

	//カーソルをあげる
	void ShopCursorUp();

	//カーソルをさげる
	void ShopCursorDown();

	//武器を買う
	void BuyWeapon();

	//情報を対応した武器に切り替える
	void ChangeInfoSelectWeapon();
};