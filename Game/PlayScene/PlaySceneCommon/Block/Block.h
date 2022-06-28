/*
障害物クラス
作成者：杉山
作成日：2021/10/21
*/

#pragma once




//所持
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"
//State分け
#include"BKStateNormal.h"
#include"BKStateArchitecture.h"

class BlockKindBase;		//状態分け基底クラス

class Block
{
private:

	//定数
	//ブロックの耐久度
	static const int BLOCK_DURABILITY;


	//変数

	//モデル描画クラス
	std::unique_ptr<BoxModel> mpBlockModel;

	//使用フラグ
	bool mBlockUseFlag;

	//HP
	int mBlockHP;

	//重力フラグ
	bool mIsGravity;

	//型番によって切り替える
	std::unique_ptr<BKStateArchitecture> mpArchitecture;
	std::unique_ptr<BKStateNormal> mpNormal;

	//型番
	BlockKindBase* mpBlockKindBase;

public:
	//関数
	//コンストラクタ
	Block();
	//デストラクタ
	~Block();
	//初期化
	void Initialize();
	//更新
	void Update();

	//生成処理
	void Create(const DirectX::SimpleMath::Vector3& position,
				const DirectX::SimpleMath::Vector3& scale);

	//描画
	void Draw();
	//終了処理
	void Finalize();

	//モデルにアクセス(当たり判定など)
	BoxModel* GetBoxModel() const
	{
		return mpBlockModel.get();
	}

	//自身を削除(ポインタなどは消滅しない)
	void SelfDestroy();


	//使用フラグを返す関数
	bool GetBlockUseFlag() const { return mBlockUseFlag; }
	bool* GetBlockUseFlagAddress()  { return &mBlockUseFlag; }

		//壁にダメージを与える
	bool BlockDamage(const int& damagenum)
	{
		mBlockHP -= damagenum; 
		if (mBlockHP <= 0) 
		{
			return true;
		}
		return false;
	}

	//壁の耐久値のアクセサ
	int GetBlockHP()const { return mBlockHP; }

	//ブロックの型番を変える
	void ChangeStateNormal() { mpBlockKindBase = (BlockKindBase*)mpNormal.get(); }
	void ChangeStateArchitecture() { mpBlockKindBase = (BlockKindBase*)mpArchitecture.get(); }
};