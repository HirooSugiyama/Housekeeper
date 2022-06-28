/*
武器モデルを回転させるだけのクラス
作成者：杉山
作成日：2021/10/15
*/


//所持
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class RotWeaponSample
{
private:
	//座標
	static const DirectX::SimpleMath::Vector3 ROTMODEL_POSITION;
	//拡大率
	static const DirectX::SimpleMath::Vector3 ROTMODEL_SCALE;

	//回転速度
	static const float ROT_SPEED;


	//回転させるモデル
	std::unique_ptr<ObjectModel> mpRotModel;

	//現在の角度
	float mModelRot;
	

public:

	//コンストラクタ
	RotWeaponSample();
	//デストラクタ
	~RotWeaponSample();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//リセットする
	void Reset();

	//モデル情報を取得する
	void SetWeaponModel(DirectX::Model* model);

};

