
#pragma once


#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif


#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>			// DirectInput関連のヘッダー


#define PI				(3.141592f)			// 円周率

//#define SCREEN_WIDTH	(960)				// ウインドウの幅
//#define SCREEN_HEIGHT	(600)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標

#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

#define	REGIST_MOVE				(0.55f)		// 抵抗値
#define	REGIST_MOVE_AIR			(0.95f)		// 抵抗値(空中)
#define	REGIST_MOVE_AIR_Y		(0.985f)	// 抵抗値(空中落下)
#define	REGIST_MOVE_SLIDE		(0.965f)	// 滑る床抵抗値
#define	GRAVITY					(9.80f)		// 重力

#define PREPARE_SCENE_ARRAY		// 複数シーンの作成
#undef PREPARE_SCENE_ARRAY

#ifndef PREPARE_SCENE_ARRAY
#define PREPARE_SCENE_POINTER	// 複数シーンの作成
//#undef PREPARE_SCENE_POINTER
#endif

#define PREPARE_TEXTURE_ARRAY	// 複数テクスチャの作成
//#undef PREPARE_TEXTURE_ARRAY

#define	NUM_OBJECT		(3)			// オブジェクト数

#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(600)				// ウインドウの高さ