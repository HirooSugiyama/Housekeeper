/*
地面上にあるオブジェクトを統括するクラス
作成者：杉山
作成日：2021/08/19
*/


#include"pch.h"
#include "GroundObjectManager.h"

//前方宣言
#include"../Enemy/EnemyManager.h"

//関数内部を使用
#include"IGroundObject.h"
#include"../Player/Player.h"
#include"../ObjectModel/BoxModel.h"
#include"../Enemy/DetectNormalEnemy.h"

#include"../Player/PStateWalk.h"

//CSVファイル原点の座標
const DirectX::SimpleMath::Vector2 GroundObjectManager::GOMANAGER_INIT_CSV_POSITION(-19.f, -40.f);
/*======================
コンストラクタ
引数：ファイルのパス
======================*/
GroundObjectManager::GroundObjectManager(const std::string& filepath)
	:
	mpConifer{},
	mConiferPosition(),
	mpConiferGroup{},
	mConiferGroupPosition(),
	mpShop{},
	mShopPosition(),
	mGroundObject(),
	mGroundObjectMapChip{},
	mSaveInfo{},
	mGroundObjectCollider{},
	mCorresColliderObject{},
	mPlayerShopTouchFlag(false)
{
	//ファイル読み込み処理
	this->LoadMapChip(filepath);

	//針葉樹の配列数を調節する
	this->AdjustmentConiferVector();
	//針葉樹の配列数を調節する
	this->AdjustmentConiferGroupVector();
	//ショップの配列数を調節する
	this->AdjustmentShopVector();

	//CSVファイルからある程度のまとまりのオブジェクトを探し出す
	this->SeekLoadMapChipCohesive();

	//情報をもとに当たり判定を作成する
	this->CreateCollider();
}

/*======================
デストラクタ
======================*/
GroundObjectManager::~GroundObjectManager()
{
}

/*======================
初期化
引数：なし
返り値：なし
======================*/
void GroundObjectManager::Initialize()
{
	//針葉樹の初期化処理
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Initialize();

		//座標を設定する
		this->ConfigConiferVectorPosition();
	}
	//針葉樹グループの初期化処理
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Initialize();

		//座標を設定する
		this->ConfigConiferGroupVectorPosition();
	}	
	//ショップの初期化処理
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Initialize();

		//座標を設定する
		this->ConfigShopVectorPosition();
	}	
}

/*====================
描画処理
引数：なし
返り値：なし
======================*/
void GroundObjectManager::Draw()
{
	//針葉樹の描画処理
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Draw();
	}
	//針葉樹グループの描画処理
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Draw();
	}
	//ショップの描画処理
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Draw();
	}
}

/*======================================
敵の当たり判定を回す
引数：ファイルのパス
返り値：なし
======================================*/
void GroundObjectManager::RoolNormalEnemyChackHit(DetectNormalEnemy* pEnemy)
{
	//当たり判定の数だけ繰り返す
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{
		pEnemy->ChackHitGroundObjectEnemy(&mGroundObjectCollider[i]);
	}
}

/*=====================================
プレイヤーとの当たり判定処理
引数：プレイヤーのポインタ
返り値：なし
======================================*/
void GroundObjectManager::ChackHitPlayerGroundObject(Player* pPlayer)
{
	//判定用変数の宣言
	bool hitflag = false;

	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//簡略化
	AABB* playerCollider = pPlayer->GetStateWalk()->GetDestinationPlayerCollider();

	AABB customCollider = *playerCollider;

	//当たり判定の数だけ行う
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{	
		//もし当たっていたら処理を行う
		if (pC.Intersect(playerCollider,&mGroundObjectCollider[i]))
		{

			hitflag = true;

			//もしショップにぶつかったら
			if (mCorresColliderObject[i] == eGroundObject::SHOP &&
				!mPlayerShopTouchFlag)
			{
				//フラグを建てる
				mPlayerShopTouchFlag = true;
				//ワイプ処理
				auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
				pSTI.SetWipeUseFlag(true);
				pSTI.GetWipe()->SetClose();
			}
			else
			{
				bool xFlag = false;
				bool zFlag = false;

				customCollider = *playerCollider;
				customCollider.mMax.x = pPlayer->GetPlayerModel()->GetPosition().x;
				customCollider.mMin.x = pPlayer->GetPlayerModel()->GetPosition().x;
				if (pC.Intersect(&customCollider, &mGroundObjectCollider[i]))
				{
					zFlag = true;
				}

				customCollider = *playerCollider;
				//X側を削除
				customCollider.mMax.z = pPlayer->GetPlayerModel()->GetPosition().z;
				customCollider.mMin.z = pPlayer->GetPlayerModel()->GetPosition().z;
				if (pC.Intersect(&customCollider, &mGroundObjectCollider[i]))
				{
					xFlag = true;			
				}
				if (xFlag && zFlag)
				{
					pPlayer->GetStateWalk()->SetGroundObjectXHitFlag(true);
					pPlayer->GetStateWalk()->SetGroundObjectZHitFlag(true);
				}
				else if (xFlag)
				{
					pPlayer->GetStateWalk()->SetGroundObjectXHitFlag(true);
					pPlayer->GetStateWalk()->SetGroundObjectZHitFlag(false);
				}
				else if (zFlag)
				{
					pPlayer->GetStateWalk()->SetGroundObjectXHitFlag(false);
					pPlayer->GetStateWalk()->SetGroundObjectZHitFlag(true);
				}	
			}
		}
	}
	//もし現在の入力で移動しても衝突しないならば
	if(hitflag==false)
	{
		//地上オブジェクトとは当たっていないことにする
		pPlayer->GetStateWalk()->SetGroundObjectXHitFlag(false);
		pPlayer->GetStateWalk()->SetGroundObjectZHitFlag(false);

		//ショップとも当たってないこととする
		mPlayerShopTouchFlag = false;
	}
}

/*======================================
オブジェクト配置用のMapChip読み込み
引数：ファイルのパス
返り値：なし
======================================*/
void GroundObjectManager::LoadMapChip(const std::string & filepath)
{
	//例外処理
	Utility::FileError(filepath);

	//ファイル変換
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;
		//変換用変数
		DirectX::SimpleMath::Vector2 position;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//要素がなかったら
			if (atoi(tileBuf.c_str()) == static_cast<int>(eGroundObject::NONE))
			{
				continue;
			}

			//以下は要素がある場合のみ通る処理
			int tile = atoi(tileBuf.c_str());
			

			//要素を保存
			mGroundObjectMapChip[j][i] = tile;

			//座標を保存
			position.x = static_cast<float>(j);
			position.y = static_cast<float>(i);

			//座標をワールド座標に変換
			position += GOMANAGER_INIT_CSV_POSITION;

			//要素によって処理を変える
			switch (tile)
			{
				case static_cast<int>(eGroundObject::CONIFER):
				{
					mConiferPosition.push_back(position);

					//確保数を増やす
					mGroundObject.mConiferNum++;

					break;
				}
				case static_cast<int>(eGroundObject::CONIFER_GROUP):
				{
					mConiferGroupPosition.push_back(position);

					//確保数を増やす
					mGroundObject.mConiferGroupNum++;

					break;
				}
				case static_cast<int>(eGroundObject::SHOP):
				{
					mShopPosition.push_back(position);

					//確保数を増やす
					mGroundObject.mShopNum++;

					break;
				}
			}
		}

	}
}

/*======================================
針葉樹の配列数を調節する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::AdjustmentConiferVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpConifer.resize(mGroundObject.mConiferNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i] = std::make_unique<GroundObjectConifer>();
	}
}

/*======================================
針葉樹の座標を設定する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::ConfigConiferVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		position.x = mConiferPosition[i].x;
		position.y = mpConifer[i]->GetConiferModelPositionY();
		position.z = mConiferPosition[i].y;
		mpConifer[i]->
			SetConiferModelPosition(position);
	}
}

/*======================================
針葉樹グループの配列数を調節する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::AdjustmentConiferGroupVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpConiferGroup.resize(mGroundObject.mConiferGroupNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i] = std::make_unique<GroundObjectConiferGroup>();
	}
}

/*======================================
針葉樹のグループ座標を設定する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::ConfigConiferGroupVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		position.x = mConiferGroupPosition[i].x;
		position.y = mpConiferGroup[i]->GetConiferModelPositionY();
		position.z = mConiferGroupPosition[i].y;
		mpConiferGroup[i]->
			SetConiferModelPosition(position);
	}
}


/*======================================
ショップの配列数を調節する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::AdjustmentShopVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpShop.resize(mGroundObject.mShopNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i] = std::make_unique<GroundObjectShop>();
	}
}

/*====================================
ショップの座標を設定する
引数：なし
返り値：なし
======================================*/
void GroundObjectManager::ConfigShopVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		position.x = mShopPosition[i].x;
		position.y = mpShop[i]->GetShopModelPositionY();
		position.z = mShopPosition[i].y;
		mpShop[i]->SetShopModelPosition(position);
	}
}

/*================================================================
CSVファイルからある程度のまとまりのオブジェクトを探し出す:private
引数：なし
返り値：なし
==================================================================*/
void GroundObjectManager::SeekLoadMapChipCohesive()
{
	mSaveInfo.clear();

	//一時保存用構造体を実体化
	SaveColliderInfo colliderInfo
		(eGroundObject::NONE, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2::Zero);

	//Y軸の処理
	for (int y = 0; y < GOMANAGER_CSV_MAX_Y; y++)
	{
		//変換用変数
		int chipX = 0, chipY = 0;

		//X軸の処理
		for (int x = 0; x < GOMANAGER_CSV_MAX_X; x++)
		{
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::NONE))continue;
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::CONIFER_GROUP))continue;
			if (this->OverlapCheck(x, y))continue;	//重複チェック

			//オブジェクトがあったら再帰開始
			chipX = x;
			chipY = y;
			this->Search(chipX, chipY, mGroundObjectMapChip[x][y]);

			eGroundObject object(static_cast<eGroundObject>(mGroundObjectMapChip[x][y]));
			colliderInfo.mObjectType = object;


			colliderInfo.mMinPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y));
			colliderInfo.mMaxPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(chipX), static_cast<float>(chipY));
			mSaveInfo.push_back(colliderInfo);
		}
	}
}

/*======================================
情報をもとに当たり判定を作成する:private
引数：なし
返り値：なし
=========================================*/
void GroundObjectManager::CreateCollider()
{
	int num = static_cast<int>(mSaveInfo.size());

	//情報の数だけ容量を増やす
	mGroundObjectCollider.resize(num);
	mCorresColliderObject.resize(num);

	//簡略化変数の宣言
	DirectX::SimpleMath::Vector3 basePosition, minPosition, maxPosition, halfScale;


	//情報の数だけ行う
	for (int i = 0; i < num; i++)
	{
		//オブジェクトの種類によって処理を変える
		//拡大率をもとに当たり判定用座標を求める
		switch (mSaveInfo[i].mObjectType)
		{
			case eGroundObject::CONIFER:
			{
				/*==================最小値を計算==================*/
				//算出した座標+world座標変換
				basePosition.x = mSaveInfo[i].mMinPosition.x+ GOMANAGER_INIT_CSV_POSITION.x;

				//共通の座標を使用(代表して0番目の定数を使用)
				basePosition.y = mpConifer[0]->GetConiferModelPositionY();

				//算出した座標+world座標変換
				basePosition.z = mSaveInfo[i].mMinPosition.y+ GOMANAGER_INIT_CSV_POSITION.y;

				//拡大率の半分を取得
				halfScale = mpConifer[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//最小値を算出
				minPosition = basePosition - halfScale;
				/*==================ここまで=================*/

				/*==================最大値を計算==================*/
				//算出した座標+world座標変換
				basePosition.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//算出した座標+world座標変換
				basePosition.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//最大値を算出
				maxPosition = basePosition + halfScale;

				/*==================ここまで=================*/

				break;
			}
			case eGroundObject::SHOP:
			{
				/*==================最小値を計算==================*/
				//算出した座標+world座標変換
				basePosition.x = mSaveInfo[i].mMinPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//共通の座標を使用(代表して0番目の定数を使用)
				basePosition.y = mpShop[0]->GetShopModelPositionY();

				//算出した座標+world座標変換
				basePosition.z = mSaveInfo[i].mMinPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//拡大率の半分を取得
				halfScale = mpShop[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//最小値を算出
				minPosition = basePosition - halfScale;
				/*==================ここまで=================*/

				/*==================最大値を計算==================*/
				//算出した座標+world座標変換
				basePosition.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//算出した座標+world座標変換
				basePosition.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//最大値を算出
				maxPosition = basePosition + halfScale;

				/*==================ここまで=================*/

				break;
			}
		}
		//情報を設定する
		mGroundObjectCollider[i].SetCollider(minPosition, maxPosition);
		mCorresColliderObject[i] = mSaveInfo[i].mObjectType;
	}
}

/*================================================================
オブジェクトのサイズを測定する再帰関数:private
引数：マップチップX、マップチップY、オブジェクトの種類番号
返り値：なし
==================================================================*/
void GroundObjectManager::Search(int& chipX, int& chipY, int objectNum)
{
	//横隣が同じオブジェクトなら
	if (mGroundObjectMapChip[chipX + 1][chipY] == objectNum)
	{
		chipX++;
		this->Search(chipX, chipY, objectNum);

	}
	//縦を見る
	if(mGroundObjectMapChip[chipX][chipY + 1] == objectNum)
	{
		chipY++;
		this->Search(chipX, chipY, objectNum);
	}
}
/*================================================================
既に当たり判定にあるかをチェックする関数:private
引数：現在のマップチップ座標
返り値：true[既にある]　false[ない]
==================================================================*/
bool GroundObjectManager::OverlapCheck(int x, int y)
{
	//型変換
	DirectX::SimpleMath::Vector2 position
		(DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y)));

	//設定した当たり判定の内容を走査する
	for (int i = 0; i < static_cast<int>(mSaveInfo.size()); i++)
	{
		if (mSaveInfo[i].mMinPosition.x<= position.x && mSaveInfo[i].mMaxPosition.x >= position.x&&
			mSaveInfo[i].mMinPosition.y <= position.y && mSaveInfo[i].mMaxPosition.y >= position.y)
		{
			return true;
		}
	}
	return false;
}
