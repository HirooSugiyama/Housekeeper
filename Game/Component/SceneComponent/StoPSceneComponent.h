/*
ステージセレクト画面からプレイシーンへ情報を渡すためのインターフェース
作成者：杉山
作成日：2021/10/21
*/
#pragma once

class StoPSceneComponent
{
private:
	//自分自身
	static std::unique_ptr<StoPSceneComponent> sStoPComponent;


	//読み込むステージCSVファイル
	std::string mCSVFileName;

	//ステージ番号
	std::string mStageNumber;	//後々String型で使用するためあらかじめString型で準備

	//コピーコンストラクタ、コピー代入演算子をdelete。
	StoPSceneComponent(const StoPSceneComponent& dr) = delete;
	StoPSceneComponent operator=(const StoPSceneComponent& dr) = delete;

	//コンストラクタ
	StoPSceneComponent();
public:
	//自身のインスタンス
	static StoPSceneComponent& GetStoPIFInstance();


	//各種アクセサ
	//CSVファイル
	void SetStageCSV(const std::string& filepath) { mCSVFileName = filepath; }
	std::string GetStageCSV() const { return mCSVFileName; }

	//ステージ番号
	void SetStageNumber(const std::string& number) { mStageNumber = number; }
	std::string GetStageNumber()const { return mStageNumber; }
};
