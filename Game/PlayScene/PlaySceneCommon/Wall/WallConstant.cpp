/*===================================================
壁の座標や拡大率などをまとめた定数定義
作成者：杉山
作成日：2021/10/21
===================================================*/

#include"pch.h"
#include"WallConstant.h"



//左の壁
	//拡大率
const float WallConstant::WALL_LEFT_SCALE_X = 0.5f;
const float WallConstant::WALL_LEFT_SCALE_Y = 6.f;
const float WallConstant::WALL_LEFT_SCALE_Z = 60.f;
//座標			 
const float WallConstant::WALL_LEFT_POSITION_X = -20.f;
const float WallConstant::WALL_LEFT_POSITION_Y = 2.f;
const float WallConstant::WALL_LEFT_POSITION_Z = -15.f;

//右の壁		
	//拡大率	
const float WallConstant::WALL_RIGHT_SCALE_X = WALL_LEFT_SCALE_X;
const float WallConstant::WALL_RIGHT_SCALE_Y = WALL_LEFT_SCALE_Y;
const float WallConstant::WALL_RIGHT_SCALE_Z = WALL_LEFT_SCALE_Z;
//座標				
const float WallConstant::WALL_RIGHT_POSITION_X = -WALL_LEFT_POSITION_X;
const float WallConstant::WALL_RIGHT_POSITION_Y = WALL_LEFT_POSITION_Y;
const float WallConstant::WALL_RIGHT_POSITION_Z = WALL_LEFT_POSITION_Z;
