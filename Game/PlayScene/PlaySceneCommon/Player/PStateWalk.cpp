/*
プレイヤーの状態分けステートパターン：移動状態
作成者：杉山
作成日：2021/06/15
*/
#include"pch.h"

#include "PStateWalk.h"

//返り値からの関数の取得で使用。
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"

//移動速度の取得に使用
#include"../ObjectMove.h"

//ここで定義する。
const float MoveSpeed::MOVE_VELOCITY_X = 0.15f;
const float MoveSpeed::MOVE_VELOCITY_Y = 0.15f;
const float MoveSpeed::MOVE_VELOCITY_Z = 0.15f;


//ブロックの範囲
const float PStateWalk::MAX_POSITION_X = Utility::FIELD_MAX_SIZE_X;
const float PStateWalk::MAX_POSITION_Z = Utility::FIELD_MAX_SIZE_Z;
const float PStateWalk::MIN_POSITION_Z = Utility::FIELD_MIN_SIZE_Z;

//スプライトの数
const int PStateWalk::WALKPLAYER_SPRITE_NUM = 5;

//スプライトのサイクル(この時間周期でスプライトが回る)
const int PStateWalk::WALKPLAYER_SPRITE_CYCLE = 4;


//プレイヤーの移動量(X)
const float PStateWalk::PLAYER_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//プレイヤーの移動量(Y)					
const float PStateWalk::PLAYER_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//プレイヤーの移動量(Z)					 
const float PStateWalk::PLAYER_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;


//移動量の増加量
const float PStateWalk::PLAYER_MOVE_INCREASE_VELOCITY=0.1f;

//左
const int PStateWalk::PLAYER_CHARACTER_ANGLE_L = 90;
//右	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_R = -90;
//上	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_U = 0;
//下	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_D = 180;
//左上
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LU = 45;
//右上
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RU = -PLAYER_CHARACTER_ANGLE_LU;
//左下
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LD = 135;
//右下
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RD = -PLAYER_CHARACTER_ANGLE_LD;

//モデル角度修正
const float PStateWalk::PLAYER_FIX_MODEL_ROTATION_Y = 180.f;



/*========================
コンストラクタ
引数：なし
=========================*/
PStateWalk::PStateWalk()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpWalkAnimationModel(),
	mActualPlayerVelocity(DirectX::SimpleMath::Vector3::Zero),
	mpDestinationPlayerCollider(),
	mGroundObjectXHitFlag(false),
	mGroundObjectZHitFlag(false),
	mBlockHitFlag(false)
{
	mpWalkAnimationModel = std::make_unique<AnimationModel>();

	mpDestinationPlayerCollider = std::make_unique<AABB>();
}

/*=========================
初期化処理
引数：プレイヤーのポインタ
返り値：なし
=========================*/
void PStateWalk::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;

	//アニメーションモデルの設定
	mpWalkAnimationModel->Initialize(static_cast<int>(PlayModelsResouce::MODEL__ANIMATIONMODEL_STANDARD_RUN));

	//モデルの初期色は青色に
	DirectX::SimpleMath::Vector3 color = DirectX::Colors::Blue;
	mpWalkAnimationModel->SetColor(color);
}
/*=========================
更新処理
引数：なし
返り値：なし
=========================*/
void PStateWalk::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::WALK)
	{
		mpPlayer->SetState(ePlayerState::WALK);
	}

	//移動量増加処理
	this->ConstantAcceleration();

	//移動できるか判断する
	this->AllObjectHit();

	//タイマーの取得
	const auto& pTimerComponent = TimerComponent::GetTimerInstance();
	//プレイヤーのアニメーション処理
	mpWalkAnimationModel->Update(static_cast<float>(pTimerComponent.GetTimer().GetElapsedSeconds()));
}

/*=========================
描画処理
引数：なし
返り値：なし
=========================*/
void PStateWalk::Draw()
{
	//スプライトモデルの情報設定
	this->SetSpriteModelPosition();

	//角度を一時的に保存
	float rot = mpWalkAnimationModel->GetModel()->GetRotAngleY();

	//モデル生成時の向きのミスを修正
	mpWalkAnimationModel->GetModel()->SetRotationY(rot+ PLAYER_FIX_MODEL_ROTATION_Y);

	//アニメーションの描画
	mpWalkAnimationModel->Draw();

	//再設定
	mpWalkAnimationModel->GetModel()->SetRotationY(rot);
}

/*=====================================
移動ベクトルを算出を設定する
引数：なし
返り値：移動ベクトル
======================================*/
DirectX::SimpleMath::Vector3 PStateWalk::CalculationMoveVelocity()
{
	//返り値用変数の宣言
	DirectX::SimpleMath::Vector3 returnpos = DirectX::SimpleMath::Vector3::Zero;

	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward()|| pGamePad->MoveUp())	//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			returnpos.z = -mActualPlayerVelocity.z;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			returnpos.x = -mActualPlayerVelocity.x;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			returnpos.z = mActualPlayerVelocity.z;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			returnpos.x = mActualPlayerVelocity.x;
			side = true;
		}
	}

	//同時押しの処理(コントローラーは現実的に不可能なので処理は無し)
	//双方向への入力は移動量0とする。
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		returnpos.x = 0;
	}


	if(pKey->WalkForward() && pKey->WalkBack())
	{
		returnpos.z = 0;
	}

	//斜め方向の移動処理
	if (whith && side && returnpos.x != 0 || returnpos.z != 0)
	{

		//斜めに移動する際は縦横とは長さが異なる（少し長い）ので、それの追加の計算。
		//ベクトルの長さを取得
		float vl = sqrtf((returnpos.x * returnpos.x) + (returnpos.z * returnpos.z));

		//単位ベクトル（長さが１のベクトル）を計算
		returnpos.x /= vl;
		returnpos.z /= vl;

		//移動ベクトルを目的の大きさ（移動量）にスケーリング
		returnpos.x *= mActualPlayerVelocity.x;
		returnpos.z *= mActualPlayerVelocity.z;
	}

	return returnpos;
}


/*==================================================================
移動後のプレイヤーの当たり判定を返す(移動はしない)
引数：なし
返り値：当たり判定
===================================================================*/
AABB* PStateWalk::GetDestinationPlayerCollider()
{
	//算出用当たり判定の宣言
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	
	//プレイヤーの座標を保存
	modelpos = mpPlayer->GetPlayerModel()->GetPosition();
	
	//プレイヤーの拡大率を保存
	modelscale = mpPlayer->GetPlayerModel()->GetScale();
	
	//現在のキー入力での移動量を算出用変数に追加
	modelpos += mpPlayer->GetStateWalk()->CalculationMoveVelocity();
	
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = modelscale / 2.f;
	halfsize.y *= mpPlayer->GetPlayerColliderExtendY();
	
	//入力をもとに次の当たり判定を算出
	mpDestinationPlayerCollider->SetCollider(modelpos - halfsize, modelpos + halfsize);

	//当たり判定を返す
	return mpDestinationPlayerCollider.get();
}







/*=====================================
State開始時の初期化処理:private
引数：なし
返り値：なし
======================================*/
void PStateWalk::SetSpriteModelPosition()
{
	//簡略化
	DirectX::SimpleMath::Vector3 position= DirectX::SimpleMath::Vector3::Zero, scale= DirectX::SimpleMath::Vector3::Zero;
	position = mpPlayer->GetPlayerModel()->GetPosition();
	scale = mpPlayer->GetPlayerModel()->GetScale();

	mpWalkAnimationModel->GetModel()->SetPosition(position);
	mpWalkAnimationModel->GetModel()->SetScale(scale);
	
	//※当たり判定は通常モデルの方で処理
}

/*=====================================
移動量を加速度的に増加させる:private
引数：なし
返り値：なし
=======================================*/
void PStateWalk::ConstantAcceleration()
{
	//もし加速度が最大値ではなかったら、加速度を少し増やす。
	/*X*/
	if (mActualPlayerVelocity.x < PLAYER_MOVE_VELOCITY_X)
	{
		mActualPlayerVelocity.x += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.x = PLAYER_MOVE_VELOCITY_X;
	}
	/*Y*/
	if (mActualPlayerVelocity.y < PLAYER_MOVE_VELOCITY_Y)
	{
		mActualPlayerVelocity.y += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.y = PLAYER_MOVE_VELOCITY_Y;
	}
	/*Z*/
	if (mActualPlayerVelocity.z < PLAYER_MOVE_VELOCITY_Z)
	{
		mActualPlayerVelocity.z += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	else
	{
		mActualPlayerVelocity.y = PLAYER_MOVE_VELOCITY_Y;
	}


}

/*===========================================================================
全てのオブジェクトに当たっていない場合のみ処理を通す関数:private
引数：なし
返り値：なし
============================================================================*/
void PStateWalk::AllObjectHit()
{
	//どのオブジェクトとも当たっていなかったら
	if (mBlockHitFlag == false)
	{
		//移動処理
		this->Move();

		//当たり判定を更新する
		mpPlayer->UpdateCollider();
	}
}

/*=====================================
移動処理:private
引数：なし
返り値：なし
======================================*/
void PStateWalk::Move()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	DirectX::SimpleMath::Vector3 vel;
	int rot = -1;//Modelの傾き

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward() || pGamePad->MoveUp())	//キー入力が行われたら
	{		
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			vel.z = -mActualPlayerVelocity.z;
			rot = PLAYER_CHARACTER_ANGLE_U;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			vel.x = -mActualPlayerVelocity.x;
			rot = PLAYER_CHARACTER_ANGLE_L;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			vel.z = mActualPlayerVelocity.z;
			rot = PLAYER_CHARACTER_ANGLE_D;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			vel.x = mActualPlayerVelocity.x;
			rot = PLAYER_CHARACTER_ANGLE_R;
			side = true;
		}
	}

	//同時押しの処理(コントローラーは現実的に不可能なので処理は無し)
	//双方向への入力は移動量0とする。
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		vel.x = 0;
	}


	if (pKey->WalkForward() && pKey->WalkBack())
	{
		vel.z = 0;
	}


	//斜め方向の移動処理
	if (whith && side && vel.x != 0 || vel.z != 0)
	{

		//斜めに移動する際は縦横とは長さが異なる（少し長い）ので、それの追加の計算。
		//ベクトルの長さを取得
		float vl = sqrtf((vel.x * vel.x) + (vel.z * vel.z));

		//単位ベクトルを計算
		vel.x /= vl;
		vel.z /= vl;

		//移動ベクトルを目的の大きさ（移動量）にスケーリング
		vel.x *= mActualPlayerVelocity.x;
		vel.z *= mActualPlayerVelocity.z;

		if (pKey->WalkForward() || pGamePad->MoveUp())	//キー入力が行われたら
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_LU;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_RU;
			}
		}
		if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_LD;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_RD;
			}
		}
	}

	//一切処理がなかったら立ち状態へ移行
	if (vel == DirectX::SimpleMath::Vector3::Zero)
	{
		mpPlayer->ChangeStateStand();

		//加速度をすべて初期化する
		this->AllActualPlayerVelocityInit();
	}

	//X方向もしくはZ方向に入力があったら
	if (vel.x != 0 || vel.z != 0) 
	{
		if (mGroundObjectXHitFlag&& mGroundObjectZHitFlag)
		{
			return;
		}
		else if (mGroundObjectXHitFlag)
		{
			vel.x = 0.f;
			mpPlayer->GetPlayerModel()->Move(vel);								//モデルを移動させる。
		}
		else if (mGroundObjectZHitFlag)
		{
			vel.z = 0.f;
			mpPlayer->GetPlayerModel()->Move(vel);								//モデルを移動させる。
		}
		else
		{
			mpPlayer->GetPlayerModel()->Move(vel);								//モデルを移動させる。
		}

		
		mpPlayer->GetPlayerModel()->SetRotationY(static_cast<float>(rot));	//傾きを変更させる
		mpWalkAnimationModel->GetModel()->SetRotationY(static_cast<float>(rot));
		//degreeには関数内で変換
	}
}

/*=====================================
使用する加速度をすべて初期化:private
引数：なし
返り値：なし
======================================*/
void PStateWalk::AllActualPlayerVelocityInit()
{
	mActualPlayerVelocity = DirectX::SimpleMath::Vector3::Zero;
}
