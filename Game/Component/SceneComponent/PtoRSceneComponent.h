/*
プレイシーンからリザルトシーンへ情報を渡すためのインターフェース
作成者：杉山
作成日：2021/10/21
*/
#pragma once

class PtoRSceneComponent
{
private:
	//自分自身
	static std::unique_ptr<PtoRSceneComponent> sPtoRComponent;

	//スコア
	int mScoreNum;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	PtoRSceneComponent(const PtoRSceneComponent& pr) = delete;
	PtoRSceneComponent operator=(const PtoRSceneComponent& pr) = delete;


	//コンストラクタ
	PtoRSceneComponent();
public:
	//自身のインスタンス
	static PtoRSceneComponent& GetPtoRIFInstance();


	//スコアのアクセサ
	void SetScoreNum(int score) { mScoreNum = score; }
	int GetScoreNum()const { return mScoreNum; }
};
