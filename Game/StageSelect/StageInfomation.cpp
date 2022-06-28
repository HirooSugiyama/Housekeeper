/*
各ステージの情報を管理するクラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"StageInfomation.h"

//ステージ画像の座標
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_POSITION(655.f,144.f);

//ステージ画像の拡大率
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_SCALE(0.43f,0.36f);

//ステージのPhase数の描画位置
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_PHASENUM_POSITION(860.f, 525.f);

//ステージ情報を管理するCSVファイルのパス
const std::string StageInfomation::STAGE_INFO_CSV_FILEPATH =
	"Resources/CSV/StageInfomation.csv";


/*===================================
コンストラクタ
引数：なし
===================================*/
StageInfomation::StageInfomation()
	:
	mpStageMapTexture(),
	mpStageLevel(),
	mStageTextureTag{},
	mStagePhaseNum{},
	mStageLevelNum{}
{
	mpStageMapTexture = std::make_unique<ObjectTexture>();
	mpStageLevel = std::make_unique<StageLevel>();
	mpPhaseSpriteNum = std::make_unique<SpriteNumber2D>();
	//ファイル読み込み
	this->LoadStageInfoCSV();
}

/*===================================
デストラクタ
===================================*/
StageInfomation::~StageInfomation()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void StageInfomation::Initialize()
{
	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__CURSOR));
	//画像初期化処理
	mpStageMapTexture->Initialize();

	//画像を設定する
	mpStageMapTexture->SetTexture(textute);

	//拡大率の設定
	mpStageMapTexture->SetPosition(STAGE_INFO_TEXTURE_POSITION);

	//拡大率の設定
	mpStageMapTexture->SetScale(STAGE_INFO_TEXTURE_SCALE);

	//ステージレベル管理クラスの初期化処理
	mpStageLevel->Initialize();

	//スコアのフォントを指定
	mpPhaseSpriteNum->SetTextureKey(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGENUMBERFONT));
	mpPhaseSpriteNum->Initialize();
	mpPhaseSpriteNum->SetAlign(eAlign::LEFT);
	mpPhaseSpriteNum->SetScale(Utility::STRING_SIZE_SMALL);
}


/*===================================
描画処理
引数：選択しているステージ番号
返り値：なし
===================================*/
void StageInfomation::Draw(const int& selectStageNum)
{
	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(mStageTextureTag[selectStageNum]);
	//画像を設定する
	mpStageMapTexture->SetTexture(textute);
	mpStageMapTexture->Draw();

	//ステージレベル管理クラスの描画処理
	int starnum = mStageLevelNum[selectStageNum];
	mpStageLevel->Draw(starnum);


	//フェーズ数の描画
	mpPhaseSpriteNum->Create(mStagePhaseNum[selectStageNum], STAGE_INFO_PHASENUM_POSITION);
	mpPhaseSpriteNum->Draw();
}

/*===================================
ステージ情報をファイルから取得する
引数：なし
返り値：なし
===================================*/
void StageInfomation::LoadStageInfoCSV()
{
	//例外処理
	Utility::FileError(STAGE_INFO_CSV_FILEPATH);

	//ファイル変換
	std::ifstream ifs(STAGE_INFO_CSV_FILEPATH);
	//1行の情報を保存する変数
	std::string lineBuf;

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
			//ステージ画像のタグを保存
			if (j == static_cast<int>(FILE_INFO::TEXTURE_TAG))
			{
				mStageTextureTag[i] = this->TextureSet(tileBuf);	
			}
			//フェーズ番号を保存
			if (j == static_cast<int>(FILE_INFO::PHASE_NUM))
			{
				mStagePhaseNum[i] = atoi(tileBuf.c_str());
			}
			//フェーズのレベルを保存
			if (j == static_cast<int>(FILE_INFO::LEVELOCITY))
			{
				mStageLevelNum[i] = atoi(tileBuf.c_str());
			}
		}
	}
}

/*===================================
キーに応じて設定画像を変更する:private
引数：取得したファイルのキー
返り値：リソース番号
===================================*/
int StageInfomation::TextureSet(const std::string & fileKey)
{
	if (fileKey == "Stage1")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE1);
	}
	else if (fileKey == "Stage2")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE2);
	}
	else if (fileKey == "Stage3")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE3);
	}
	else if (fileKey == "Stage5")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE5);
	}
	else if (fileKey == "Stage6")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE6);
	}
	else if (fileKey == "Stage7")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE7);
	}
	else if (fileKey == "Stage8")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE8);
	}
	else if (fileKey == "Stage9")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE9);
	}
	else if (fileKey == "Stage10")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE10);
	}

	return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE1);
}




