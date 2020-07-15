
#pragma once


//#include "vector.h"
#include "object.h"


#define TEXTURE_FILENAME "asset/texture/texture.tga"

// �J�����֌W
#define VIEW_ANGLE	(5.0f)		// ����p def:90.0f
#define VIEW_NEAR_Z (10.0f)		// �ߖʋ��� 
#define VIEW_FAR_Z	(100000.0f)	// ���ʋ��� 


class COpenGl
{
private:
	HGLRC	m_hGLRC;  //GL�R���e�L�X�g
	int		g_Texture;

	//�Ƃ肠�����J�����p�ɍŒ���p�� 
	VECTOR3D  m_posP;	// ���_ 
	VECTOR3D  m_posR;	// �����_ 
	VECTOR3D  m_vecUp;  // ������x�N�g�� 

public:
	void Init(HWND window);
	void Uninit(HWND window);
	void Update();
	void Draw(HWND window);
	void Draw3d();
};