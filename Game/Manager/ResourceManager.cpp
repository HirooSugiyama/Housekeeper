/*
リソースマネージャー
リソース全般を管理するクラスライブラリ
(現状、オーディオは別ライブラリを使用するため独立させています。)
作成者：杉山
作成日：2021/10/21
*/

#include"pch.h"
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"DeviceResources.h"


#pragma warning(disable : 4996)

/*=========================================
コンストラクタ
引数：なし
=========================================*/
ResourceManager::ResourceManager()
	:mReadTiming(eLoadScene::NONE)
{
}

/*=========================================
デストラクタ
=========================================*/
ResourceManager::~ResourceManager()
{
	//全てのリソース情報を破棄
	this->DeleteAllData();
}

/*=========================================
終了処理
引数：なし
返り値：なし
=========================================*/
void ResourceManager::Finalize()
{
	//一旦最後なのですべて初期化
	this->DeleteAllData();
}


/*=======================================
テクスチャの取得
引数：テクスチャの識別名
返り値：なし
=========================================*/
ID3D11ShaderResourceView* ResourceManager::GetTexture(const int& key)
{
	return mpTextureDB[key].Get();
}


/*=========================================
CMOモデルの取得
引数：CMOモデルの識別名
返り値：なし
=========================================*/
DirectX::Model* ResourceManager::GetCmoModel(const int& key)
{
	return mpCmoModelDB[key].get();
}

/*=========================================
アニメーションモデルの取得
引数：アニメーションモデルの識別名
返り値：なし
=========================================*/
AnimModel* ResourceManager::GetAnimationCmoModel(const int& key)
{
	return &mpAnimationCmoModelDB[key];
}


/*=========================================
リソース読み込み
引数：読み込むリソース群の幅
返り値：なし
=========================================*/
void ResourceManager::Load(ReadRange range)
{
	int min{ 0 };
	int max{ 0 };
	//範囲を指定する
	min = ResouceDatabase::mEnumClassRange[static_cast<int>(range)].mMin;
	max = ResouceDatabase::mEnumClassRange[static_cast<int>(range)].mMax;

	std::string filePath = "Resources/";

	//マルチバイト文字をワイド文字に変換
	wchar_t* wcs = L"none";//変換用変数
	const wchar_t* wideFilePath = L"none";	//テクスチャの相対パス

	//範囲内のみ読み込む
	for (int i = min; i < max+1; i++)
	{
		//ファイル名を設定する
		filePath += ResouceDatabase::mFilePath[i];

		wcs = new wchar_t[filePath.length() + 1];
		mbstowcs(wcs, filePath.c_str(), filePath.length() + 1);
		wideFilePath = wcs;

		//もしCMOの文字がなかったら(テクスチャならば)
		if (static_cast<int>(filePath.rfind(".cmo")) == Utility::EXCEPTION_NUM)
		{
			this->RegisterTexture(wideFilePath,i);
		}
		//アニメーションモデルなら
		else  if(static_cast<int>(filePath.rfind("AnimationModel")) != Utility::EXCEPTION_NUM)
		{
			this->RegisterAnimationModel(wideFilePath, i);
		}
		//アニメーションモデルなら
		else 
		{
			this->RegisterCmoModel(wideFilePath, i);
		}
		filePath = "Resources/";
		delete[] wcs;
	}	
}


/*==================================================================================
テクスチャの登録
引数：path(テクスチャの相対パス(ワイド文字列型))、Key(テクスチャの識別名(文字列))
返り値：なし
==================================================================================*/
void ResourceManager::RegisterTexture(const wchar_t* path, const int& key)
{
	//デバイスリソースの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//テクスチャの読み込み	:SRVの作成
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	//DB(Map)にテクスチャを追加
	mpTextureDB[key] = std::move(texture);

}


/*==========================================================================
CMOモデルの登録
引数：path(CMOモデルの相対パス(ワイド文字列型))、Key(CMOモデルの識別名(文字列))
返り値：なし
==========================================================================*/
void ResourceManager::RegisterCmoModel(const wchar_t* path, const int& key)
{
	//デバイスリソースの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//モデルの保存座標等を保持するインスタンスの生成
	std::unique_ptr<DirectX::EffectFactory> factory =
		std::make_unique<DirectX::EffectFactory>(device);

	factory->SetDirectory(L"Resources/Models/Play");
	std::unique_ptr<DirectX::Model> model = DirectX::Model::
		CreateFromCMO(device, path, *factory);

	//DB(Map)にテクスチャを追加
	mpCmoModelDB[key] = std::move(model);
}


/*===============================================================================================
アニメーションCMOモデルの登録
引数：path(CMOモデルの相対パス(ワイド文字列型))、Key(CMOモデルの識別名(文字列))
返り値：なし
===============================================================================================*/
void ResourceManager::RegisterAnimationModel(const wchar_t* path, const int& key)
{
	//デバイスリソースの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//モデルの保存座標等を保持するインスタンスの生成
	std::unique_ptr<DirectX::EffectFactory> factory =
		std::make_unique<DirectX::EffectFactory>(device);



	factory->SetDirectory(L"Resources/Models");
	std::unique_ptr<DirectX::Model> model = DirectX::Model::
		CreateFromCMO(device, path, *factory);

	//オフセット準備
	size_t animsOffset;

	model = DirectX::Model::CreateFromCMO(device, path,
		*factory,
		DirectX::ModelLoaderFlags::ModelLoader_CounterClockwise |
		DirectX::ModelLoaderFlags::ModelLoader_IncludeBones,
		&animsOffset);


	//DB(Map)にモデルを追加
	mpAnimationCmoModelDB[key].mModel = std::move(model);

	//DBにアニメーションを追加
	DX::ThrowIfFailed(
		mpAnimationCmoModelDB[key].mAnim.Load(path, animsOffset)
	);
}


/*=========================================
全てのリソースの削除
引数：なし
返り値：なし
=========================================*/
void ResourceManager::DeleteAllData()
{
	mpTextureDB.clear();
	mpCmoModelDB.clear();
}
