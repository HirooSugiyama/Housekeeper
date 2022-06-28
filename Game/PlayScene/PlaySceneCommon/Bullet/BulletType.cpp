/*
弾情報管理ファイル
作成者：杉山
作成日：2021/10/10
*/
#include"pch.h"

#include"BulletType.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
BulletType::BulletType()
	:
	mpBulletInfomation()
{
	//領域確保
	for (int i = 0; i < static_cast<int>(eWeaponType::NUM); i++)
	{
		mpBulletInfomation[static_cast<eWeaponType>(i)] = std::make_unique<BulletInfomation>();
	}

}

/*===================================
デストラクタ
===================================*/
BulletType::~BulletType()
{
}

/*=================================
情報を読み込む
引数：ファイルパス
返り値：なし
===================================*/
void BulletType::SetCSV(const std::string& filepath)
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();

	//例外処理
	Utility::FileError(filepath);

	//ファイル変換
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;
	//一時的に保存用

	//1行の読み込み処理_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			switch (j)
			{
				case eReadInfo::MODEL_TAG:
				{
					DirectX::Model* model{ nullptr };
					if (tileBuf == "MachineGunBullet")
					{
						model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__MACHINEGUN));
					}
					else if (tileBuf == "Grenade")
					{
						model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__GRENADE));
					}
					else
					{
						
						model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__BOOMERANG));
					}

					
					//対応した情報のマップに対応したモデルを保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletModel = model;
					break;
				}
				case eReadInfo::SPEED:
				{
					//対応した情報のマップに対応した弾の速度を保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletVelocityZ
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_X:
				{
					//対応した情報のマップに対応した弾の拡大率を保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.x
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_Y:
				{
					//対応した情報のマップに対応した弾の拡大率を保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.y
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_Z:
				{
					//対応した情報のマップに対応した弾の拡大率を保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.z
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::ATTACK_NUM:
				{
					//対応した情報のマップに対応した弾の攻撃力を保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletAttackNum
						= std::stoi(tileBuf);

					break;
				}
				case eReadInfo::INTERVAL:
				{
					//対応した情報のマップに対応した弾インターバルを保存
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletIntervalNum
						= atoi(tileBuf.c_str());

					break;
				}
			}
		}
	}
}