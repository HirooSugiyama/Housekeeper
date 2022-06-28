/*
エフェクトマネージャー
作成者：杉山
作成日：2021/09/19
*/

#include"pch.h"
#include"EffectManager.h"
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"DeviceResources.h"

//関数の使用
#include"Libraries/MyLibraries/Camera.h"
#include"Effect.h"

//一種類当たりのエフェクトの数
const int EffectManager::EFFECT_NUM = 70;

/*=========================================
コンストラクタ
引数：なし
=========================================*/
EffectManager::EffectManager()
	:mpEffectDB{}
	, mpCamera(nullptr)
{
}

/*=========================================
デストラクタ
=========================================*/
EffectManager::~EffectManager()
{
	//全てのリソース情報を破棄
	this->DeleteAllData();
}

/*=========================================
初期化
引数：ファイルのパス
返り値：なし
=========================================*/
void EffectManager::Initialize(const wchar_t* filepath)
{
	setlocale(LC_CTYPE, "");


	//とりあえず初期化忘れ防止の初期化
	this->DeleteAllData();

	//ファイル読み込み
	this->LoadCSV(filepath);
}

/*=======================================
更新処理
引数：なし
返り値：なし
=========================================*/
void EffectManager::Update()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//使用中でないなら通さない
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag() == false)
			{
				continue;
			}

			mpEffectDB[static_cast<eEffectType>(key)][i]->Update();
		}
	}	
}

/*========================================
描画処理
引数：なし
返り値：なし
=========================================*/
void EffectManager::Draw()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//使用中でないなら通さない
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag() == false)
			{
				continue;
			}

			//カメラの位置を取得
			mpEffectDB[static_cast<eEffectType>(key)][i]->
				SetCameraEyePosition(mpCamera->GetEyePosition());

			mpEffectDB[static_cast<eEffectType>(key)][i]->ExtendDraw();
		}
	}
}

/*=========================================
終了処理
引数：なし
返り値：なし
=========================================*/
void EffectManager::Finalize()
{
	//一旦最後なのですべて初期化
	this->DeleteAllData();
}

/*=========================================
エフェクトの取得
引数：エフェクトの識別名
返り値：使用予定のエフェクトのポインタ
=========================================*/
EffectSpriteTexture* EffectManager::GetEffect(const eEffectType& key)
{
	//使用中でなら通さない
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		if (mpEffectDB[key][i]->GetSpriteFlag() == true)
		{
			continue;
		}
		return mpEffectDB[key][i].get();
	}

	return nullptr;
}

/*=========================================================
全エフェクトの稼働フラグ
引数：なし
返り値：稼働フラグ(true…使用中のエフェクトあり)
==========================================================*/
bool EffectManager::ChackAllEffect()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//使用中でないなら通さない
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag())
			{
				return true;
			}
		}
	}

	return false;
}

/*========================
ファイル読み込み処理
引数：ファイルのパス
返り値：なし
=========================*/
void EffectManager::LoadCSV(const wchar_t* filepath)
{
	//例外処理
	Utility::FileError(filepath);

	//ファイル名取得
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;

		//保存用変数
		EffectSpriteTexture texture;
		std::string filename = "none";			//ファイル名
		wchar_t* wcs = L"none";					//変換用変数
		const wchar_t* texturename = L"none";	//テクスチャの相対パス

		//拡大率用変数
		DirectX::SimpleMath::Vector2 scale= DirectX::SimpleMath::Vector2::Zero;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//ファイル名の保存
			if (j == static_cast<int>(eEffectFileReading::FILE_NAME))
			{
				std::string omission = "Resources/Textures/Play/Effect/";
				filename = omission + tileBuf;
				//マルチバイト文字をワイド文字に変換
				wcs = new wchar_t[filename.length() + 1];
				size_t size;
				mbstowcs_s(&size,wcs, filename.length() + 1,filename.c_str(), filename.length() + 1);
				texturename = wcs;


				texture.SetFileName(texturename);
				texture.Initialize();
			}
			//スプライトのタイマー値を保存
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SPRITE_TIMER))
			{
				texture.SetConstTimer(atoi(tileBuf.c_str()));
			}
			//横分割数の保存
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_HORIZONTAL_SIZE))
			{
				texture.SetHorizontalCutNum(atoi(tileBuf.c_str()));
			}
			//拡大率の保存
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SCALE_X))
			{
				scale.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SCALE_Y))
			{
				scale.y = static_cast<float>(atof(tileBuf.c_str()));
				texture.SetScale(scale);
			}

		}

		//情報を保存する
		mpEffectDB[static_cast<eEffectType>(i + 1)].resize(EFFECT_NUM);

		for (int j = 0; j<EFFECT_NUM; j++)
		{
			//情報を保存する
			mpEffectDB[static_cast<eEffectType>(i + 1)][j] = std::make_unique<EffectSpriteTexture>();
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->Initialize();
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->SetTexture(texture.GetTexture());
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->SetConstTimer(texture.GetConstTimer());
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->
				SetHorizontalCutNum(texture.GetHorizontalCutNum());
		}		
		delete[] wcs;
	}
}

/*=========================================
全てのリソースの削除
引数：なし
返り値：なし
=========================================*/
void EffectManager::DeleteAllData()
{
	mpEffectDB.clear();	
}
