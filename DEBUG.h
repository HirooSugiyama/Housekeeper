/*
デバッグ操作用ヘッダーファイル
*/
#pragma once


//デバッグ処理
#define DEBUG

#ifdef DEBUG

//プレイシーンのデバッグ処理(定義時のみ通る)
//#define DEBUG_PLAYSCENE

/*-----------カメラ-----------*/
//メインカメラ
//#define DEBUG_CAMERA_MAIN

//引き気味のカメラ
//#define DEBUG_CAMERA_SLIGHTY

//真上からのカメラ
//#define DEBUG_CAMERA_TOP

//真横からのカメラ
//#define DEBUG_CAMERA_SIDE


//設定中
#define DEBUG_CAMERA_NOW


//※どれか一つは定義しておくこと！

/*-----------グリッド床-----------*/

//定義：表示　未定義：非表示
//#define DRAW_GRID_FLOOR


#else

//メインカメラの表示
#define DEBUG_CAMERA_MAIN


#endif