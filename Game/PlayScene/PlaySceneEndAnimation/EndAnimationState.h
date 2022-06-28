/*
終了時アニメーション処理で使用する列挙型
作成者：杉山
作成日：2021/11/10
*/
#pragma once




//使用するアニメーション
enum class eUseEndAnim
{
	NONE,		//なし
	LOSE,		//負け
	WIN_TIME,	//時間経過の勝利
	WIN_EXTERM,	//敵殲滅の勝利
};



//アニメーションの段階

//負けアニメーション
enum class eLoseAnimStep
{
	NONE,				//なし
	PREPARATION,		//準備
	ROTATION_ANGLE,		//カメラ回転
	FIRST_EXPLOSION,	//1発目爆発
	SECOND_EXPLOSION,	//2発目爆発
	THIRD_EXPLOSION,	//3発目爆発
	FORTH_EXPLOSION,	//4発目爆発
	LOSE_TEXTURE,		//負け画像描画
	END,				//終了
};



//勝ちアニメーション
enum class eWinAnimStep
{
	NONE,			//なし
	PREPARATION,	//準備
	SUNRISE,		//日の出
	ROTATION_ANGLE1,//カメラ回転
	EXTERM_ENEMY,	//敵全滅
	END,			//終了
};					