/*
地面上にあるオブジェクトを統括するクラス
作成者：杉山
作成日：2021/08/19
*/
#pragma once


//所持
#include"GroundObjectConifer.h"
#include"GroundObjectConiferGroup.h"
#include"GroundObjectShop.h"

struct AABB;					//所持
class EnemyManager;				//当たり判定を回す
class Player;					//当たり判定処理
class DetectNormalEnemy;		//引数

class GroundObjectManager
{
private:

	//オブジェクトの種類を指定
	enum class eGroundObject
	{
		NONE,
		CONIFER,
		CONIFER_GROUP,
		SHOP
	};

	//数保存用構造体
	struct GroundObjectNum
	{
		int mConiferNum;
		int mConiferGroupNum;
		int mShopNum;
	};

	//当たり判定算出用構造体
	struct ColliderInfo
	{
		//現在の状態
		enum class eColliderInfoState	//現在当たり判定を算出しているかそのものを表す状態列挙
		{
			NONE,
			ACTIVE,
		};

		enum class eColliderStateMode	//現在どの座標を求めているかを表す状態列挙
		{
			NONE,
			MIN_XY_MAX_X,
			MAX_Y,
		};

		//現在のオブジェクトの種類
		eGroundObject mObjectType;

		//最小値
		DirectX::SimpleMath::Vector2 mMinPosition;
		//最大値
		DirectX::SimpleMath::Vector2 mMaxPosition;

		//実態化
		eColliderInfoState mFlag;
		eColliderStateMode mState;

		//コンストラクタ
		ColliderInfo()
			:mObjectType()
			,mMinPosition(DirectX::SimpleMath::Vector2(-1.f, -1.f))
			,mMaxPosition(DirectX::SimpleMath::Vector2(-1.f, -1.f))
			,mFlag()
			,mState()
		{}
	};


	//当たり判定保存用構造体
	struct SaveColliderInfo
	{
		//現在のオブジェクトの種類
		eGroundObject mObjectType;
		//最小値
		DirectX::SimpleMath::Vector2 mMinPosition;
		//最大値
		DirectX::SimpleMath::Vector2 mMaxPosition;

		SaveColliderInfo
		(eGroundObject objectType,
			DirectX::SimpleMath::Vector2 minPosition,
			DirectX::SimpleMath::Vector2 maxPosition)
			:mObjectType(objectType)
			,mMinPosition(minPosition)
			,mMaxPosition(maxPosition)
		{}

	};


	//座標
	//CSVファイル原点の座標
	static const DirectX::SimpleMath::Vector2 GOMANAGER_INIT_CSV_POSITION;

	//最大数
	static const int GOMANAGER_CSV_MAX_X = 39;
	static const int GOMANAGER_CSV_MAX_Y = 53;

	//針葉樹モデル
	std::vector<std::unique_ptr<GroundObjectConifer>> mpConifer;
	std::vector <DirectX::SimpleMath::Vector2> mConiferPosition;

	//針葉樹グループモデル
	std::vector<std::unique_ptr<GroundObjectConiferGroup>> mpConiferGroup;
	std::vector <DirectX::SimpleMath::Vector2> mConiferGroupPosition;

	//ショップモデル
	std::vector<std::unique_ptr<GroundObjectShop>> mpShop;
	std::vector <DirectX::SimpleMath::Vector2> mShopPosition;

	//構造体を実体化
	GroundObjectNum mGroundObject;

	//MapChip保存用変数
	int mGroundObjectMapChip[GOMANAGER_CSV_MAX_X][GOMANAGER_CSV_MAX_Y];

	//座標仮保存用変数の宣言
	std::vector<SaveColliderInfo> mSaveInfo;

	//当たり判定
	std::vector<AABB> mGroundObjectCollider;

	//当たり判定に対応したモデル管理用変数
	std::vector<eGroundObject> mCorresColliderObject;

	//プレイヤーがショップに触れた際のフラグ
	bool mPlayerShopTouchFlag;

public:

	//コンストラクタ
	GroundObjectManager(const std::string & filepath);

	//デストラクタ
	~GroundObjectManager();


	//初期化
	void Initialize();

	//描画
	void Draw();

	//敵の当たり判定を回す
	void RoolNormalEnemyChackHit(DetectNormalEnemy* pEnemy);

	//プレイヤーとの当たり判定処理
	void ChackHitPlayerGroundObject(Player* pPlayer);

	//プレイヤーがショップに触れた際のフラグ
	bool GetPlayerShopTouchFlag()const { return mPlayerShopTouchFlag; }

private:
	//CSVファイル読み込み
	void LoadMapChip(const std::string & filepath);

	//針葉樹の配列数を調節する
	void AdjustmentConiferVector();
	//針葉樹の座標を設定する
	void ConfigConiferVectorPosition();

	//針葉樹グループの配列数を調節する
	void AdjustmentConiferGroupVector();
	//針葉樹グループの座標を設定する
	void ConfigConiferGroupVectorPosition();

	//ショップの配列数を調節する
	void AdjustmentShopVector();
	//ショップの座標を設定する
	void ConfigShopVectorPosition();


	//CSVファイルからある程度のまとまりのオブジェクトを探し出す
	void SeekLoadMapChipCohesive();

	//情報をもとに当たり判定を作成する
	void CreateCollider();

	//探索
	void Search(int& chipX,int& chipY,int objectNum);

	//当たり判定の重なりをチェックする
	bool OverlapCheck(int x, int y);
};
