/*
弾情報管理ファイル
作成者：杉山
作成日：2021/10/10
*/
#pragma once


//列挙型の使用
#include"../Weapon/WeaponeType.h"


//前方宣言
namespace DirectX
{
	class Model;	//構造体で所持
}

//弾情報構造体
struct BulletInfomation
{
	//弾のモデル
	DirectX::Model* mBulletModel;
	//弾の速度
	float mBulletVelocityZ;
	//弾の拡大率
	DirectX::SimpleMath::Vector3 mBulletScale;
	//弾の攻撃力
	int mBulletAttackNum;
	//弾のインターバル
	int mBulletIntervalNum;

};

class BulletType
{
private:

	//読み込む情報
	enum eReadInfo
	{
		MODEL_TAG,
		SPEED,
		SCALE_X,
		SCALE_Y,
		SCALE_Z,
		ATTACK_NUM,
		INTERVAL
	};

	//弾の種類ごとの情報管理用変数
	std::unordered_map<eWeaponType, std::unique_ptr<BulletInfomation>> mpBulletInfomation;

public:

	//コンストラクタ
	BulletType();
	//デストラクタ
	~BulletType();

	//種類に応じた弾の情報を返す関数
	BulletInfomation* GetBulletInfomation(const eWeaponType& weaponType)
	{
		return mpBulletInfomation[weaponType].get();
	}


	//CSVファイル読み込み
	void SetCSV(const std::string & filepath);

};
