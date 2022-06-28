/*
エフェクトマネージャー
作成者：杉山
作成日：2021/09/19
*/
#pragma once


//列挙型の使用
#include"EffectType.h"


//ファイルの順番をまとめた列挙体
enum class eEffectFileReading
{
	FILE_NAME,
	EFFECT_SPRITE_TIMER,
	EFFECT_HORIZONTAL_SIZE,
	EFFECT_SCALE_X,
	EFFECT_SCALE_Y,
};


//前方宣言
class EffectSpriteTexture;
class CameraBase;

//エフェクトマネージャ
class EffectManager
{
public:
	//インスタンスの取得
	static EffectManager* GetInstance()
	{
		static EffectManager instance;
		return &instance;
	}
private:

	//一種類当たりのエフェクトの数
	static const int EFFECT_NUM;


	//変数
	//エフェクト保持用マップ
	std::unordered_map <eEffectType,std::vector<std::unique_ptr<EffectSpriteTexture>>>
		mpEffectDB;

	//カメラのポインタ保存用変数
	CameraBase* mpCamera;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	EffectManager(const EffectManager& em) = delete;
	EffectManager operator=(const EffectManager& em) = delete;

	//コンストラクタ
	EffectManager();
	//デストラクタ
	~EffectManager();



public:

	//初期化
	void Initialize(const wchar_t* filepath);

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//終了処理
	void Finalize();

	//リソースの取得
	EffectSpriteTexture* GetEffect(const eEffectType& key);

	//カメラのポインタを保存する
	void SetCameraPointer(CameraBase* pCamera) { mpCamera = pCamera; }

	//全エフェクトの稼働フラグ
	bool ChackAllEffect();

private:

	//リソースデータを読み込む
	void LoadCSV(const wchar_t* filepath);

	//すべてのリソースの削除
	void DeleteAllData();

};