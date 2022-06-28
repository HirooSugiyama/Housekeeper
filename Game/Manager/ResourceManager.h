/*
リソースマネージャー
リソース全般を管理するクラスライブラリ
(現状、オーディオは別ライブラリを使用するため独立させています。)
作成者：杉山
作成日：2021/10/21
*/
#pragma once

//リソース管理ファイル
#include"Libraries/MyLibraries/Resouce.h"

//読み込み分け
enum class eLoadScene
{
	NONE = -1,
	TITLE = 1,
	MODE_SELECT,
	STAGE_SELECT,
	PLAY,
};

//ファイルの順番をまとめた列挙体
enum class eFileReading
{
	READ_TIMING,
	IDENTIFIER,
	FILE_NAME,
	FILE_MAPKEY,
};


//アニメーションモデル用構造体
struct AnimModel
{
	//モデル情報
	std::unique_ptr<DirectX::Model> mModel;

	//アニメーション情報
	DX::AnimationCMO mAnim;
};

//リソースマネージャ
class ResourceManager
{
public:
	//インスタンスの取得
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}
private:

	//変数
	//テクスチャ保持用マップ
	std::unordered_map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mpTextureDB;

	//CMOモデル保持用マップ
	std::unordered_map<int, std::unique_ptr<DirectX::Model>> mpCmoModelDB;

	//アニメーションCMOモデル保持用マップ
	std::unordered_map<int, AnimModel> mpAnimationCmoModelDB;

	//読み込みタイミング保存用文字列変数
	eLoadScene mReadTiming;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	ResourceManager(const ResourceManager& rm) = delete;
	ResourceManager operator=(const ResourceManager& rm) = delete;


	//コンストラクタ
	ResourceManager();
	//デストラクタ
	~ResourceManager();



public:

	//終了処理
	void Finalize();

	//リソースの取得
	ID3D11ShaderResourceView* GetTexture(const int& key);
	DirectX::Model* GetCmoModel(const int& key);
	AnimModel* GetAnimationCmoModel(const int& key);


	//指定の範囲のリソースのみ読み込み
	void Load(ReadRange range);

private:
	//リソースの登録
	void RegisterTexture(const wchar_t* path,  const int& key);
	void RegisterCmoModel(const wchar_t* path, const int& key);
	void RegisterAnimationModel(const wchar_t* path, const int& key);

	//すべてのリソースの削除
	void DeleteAllData();
};