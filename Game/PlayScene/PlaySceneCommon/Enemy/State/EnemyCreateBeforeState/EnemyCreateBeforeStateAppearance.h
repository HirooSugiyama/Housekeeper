/*
敵生成前State	～出現～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyCreateBeforeStateBase.h"


//前方宣言
class EffectSpriteTexture;
class Camera;

class EnemyCreateBeforeStateAppearance : public EnemyCreateBeforeStateBase
{
private:
	//モデル移動スピード
	static const float ENEMY_MODEL_MOVE_VELOCITY;
	//モデルY軸最大値
	static const float ENEMY_MODEL_MAX_POSITION_Y;

	//エフェクト座標
	static const float ENEMY_APPERANCE_POSITION_Y;



	//ポインタ保存用変数
	Camera* mpCamera;

	//フラグ管理用変数
	EffectSpriteTexture* mpAppearanceEffect;


public:

	//コンストラクタ
	EnemyCreateBeforeStateAppearance();
	//デストラクタ
	~EnemyCreateBeforeStateAppearance()override;
	//初期化処理
	void Initialize
	(
		EnemyMainStateCreateBefore* pEnemyMainState,
		IEnemy* pEnemy
	)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw();

private:
	//エフェクトの設定
	void SetEffect();

};
