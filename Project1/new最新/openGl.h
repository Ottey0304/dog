
#pragma once


//#include "vector.h"
#include "object.h"


#define TEXTURE_FILENAME "asset/texture/texture.tga"

// カメラ関係
#define VIEW_ANGLE	(5.0f)		// 視野角 def:90.0f
#define VIEW_NEAR_Z (10.0f)		// 近面距離 
#define VIEW_FAR_Z	(100000.0f)	// 遠面距離 


class COpenGl
{
private:
	HGLRC	m_hGLRC;  //GLコンテキスト
	int		g_Texture;

	//とりあえずカメラ用に最低限用意 
	VECTOR3D  m_posP;	// 視点 
	VECTOR3D  m_posR;	// 注視点 
	VECTOR3D  m_vecUp;  // 上方向ベクトル 

public:
	void Init(HWND window);
	void Uninit(HWND window);
	void Update();
	void Draw(HWND window);
	void Draw3d();
};