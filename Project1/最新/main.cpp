
#include "main.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "textureGL.h"
#include "model.h"
#include "vector.h"
#include "field.h"
//#include "opengl.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "AT13E_09_���V�_��";

CField* g_Field;
//COpenGL* g_OpenGL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HGLRC	m_hGLRC;  //GL�R���e�L�X�g
HDC		m_hDC;


#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)				// �E�C���h�E�̍���



#define TEXTURE_FILENAME "asset/texture/texture.tga"

int g_Texture;

#define VIEW_ANGLE (45.0f) // ����p
#define VIEW_NEAR_Z (10.0f) // �ߖʋ���
#define VIEW_FAR_Z (100000.0f) //���ʋ���
VECTOR3D m_posP; // ���_
VECTOR3D m_posR; // �����_
VECTOR3D m_vecUp; // ������x�N�g��


HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);


	// ����������(�E�B���h�E���쐬���Ă���s��)
	//CManager::Init();
	OpenGLInit();

	g_Field = new CField();
	g_Field->Init();
	

	/*g_OpenGL = new COpenGL();
	g_OpenGL->Init();*/


	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	//�t���[���J�E���g������
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// ���b�Z�[�W���[�v
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				//CManager::Update();
				OpenGLUpdate();
				
				//g_Field->Update();

				//g_OpenGL->Update();

				// �`�揈��
				//CManager::Draw();
				//OpenGLDraw();

				//OpenGLDraw3D();

				//g_OpenGL->Draw();

				FDDraw();
				
				
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	//CManager::Uninit();
	OpenGLUninit();

	g_Field->Uninit();
	delete g_Field;

	/*g_OpenGL->Uninit();
	delete g_OpenGL;*/

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//�������牺�t�@�C����������
//=====================================================================================
void OpenGLInit()
{
	// �s�N�Z���t�H�[�}�b�g
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),//�\���̂̃T�C�Y
		1,                  //
		PFD_DRAW_TO_WINDOW |//OpenGL�Ń_�u���o�b�t�@���g��
		PFD_SUPPORT_OPENGL |//�E�B���h�E�֕`�悷��
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,      //RGBA�`���̃s�N�Z�������g��
		24,                 //RGB24�r�b�g
		0, 0, 0, 0, 0, 0,   //���̕ӂ��疢�g�p
		0,
		0,
		0,
		0, 0, 0, 0,
		32,        //�[�x�o�b�t�@32�r�b�g         
		0,         //���̕ӂ��疢�g�p         
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};



	// Window�f�o�C�X�R���e�L�X�g�擾
	HDC	m_hDC;//���g�̃E�B���h�E�̃f�o�C�X�R���e�L�X�g
	m_hDC = GetDC(g_Window);

	//���̐ݒ�Ŏg�p�ł���s�N�Z���t�H�[�}�b�g���擾���Đݒ�
	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	//GL�R���e�L�X�g�쐬���Đݒ�i�`����Ǘ�����I�u�W�F�N�g�j
	m_hGLRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hGLRC);


	// �摜�t�@�C���ǂݍ��݁A�n���h���ۑ�
	g_Texture = LoadTexture((char*)TEXTURE_FILENAME);


	// OpenGL�`��ݒ� �������̍Ō�ɂ���Ă�����{�ݒ�
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}


void OpenGLUninit()
{
	//// Window�f�o�C�X�R���e�L�X�g�擾
	HDC	m_hDC;//���g�̃E�B���h�E�̃f�o�C�X�R���e�L�X�g
	m_hDC = GetDC(g_Window);

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(g_Window, m_hDC);
	wglDeleteContext(m_hGLRC);

	UnloadTexture(g_Texture);
}


void OpenGLUpdate()
{

}


void OpenGLDraw()
{
	// ��ʂƐ[�x�o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// <<<<<<<<<<<<<�����őS�ĕ`��

	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// 2D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);//�v�G���W�F�N�V�����s�񑀍샂�[�h

	glPushMatrix();//���݂̃v���W�F�N�V�����s���ۑ�

	glLoadIdentity();//���݂̃v���W�F�N�V�����s���P�ʍs��ɂ���

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);//���s���e�s��Z�b�g

	glMatrixMode(GL_MODELVIEW);//���f���r���[�s�񑀍샂�[�h

	glPushMatrix();//���݂̃��f���r���[�s���ۑ�

	glLoadIdentity();//���݂̃��f���r���[�s���P�ʍs��ɂ���


	// �e�N�X�`���̃n���h���ݒ�
	glBindTexture(GL_TEXTURE_2D, g_Texture);


	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);		//�`�惂�[�h���w�肵�ăf�[�^�Z�b�g�J�n

	glColor4f(1.0, 0.0, 0.0, 1.0f);	//���_�O�Ԗځ@���_�J���[�Z�b�g
	glTexCoord2f(0, 0);		//���_�O�Ԗځ@�e�N�X�`�����W�Z�b�g
	glVertex3f(100, 100, 0);	//���_�O�Ԗځ@���_���W�Z�b�g

	glColor4f(0.0, 1.0, 0.0, 1.0f);
	glTexCoord2f(0, -1);
	glVertex3f(100, 300, 0);

	glColor4f(0.0, 0.0, 1.0, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(300, 100, 0);

	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glTexCoord2f(1, -1);
	glVertex3f(300, 300, 0);

	glEnd();				//��񕪂̕`��Z�b�g�I��

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);

	// �e�}�g���N�X�ݒ��߂�
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();//���PUSH�ƃZ�b�g
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//���PUSH�ƃZ�b�g




	// �t�����g�o�b�t�@�E�o�b�N�o�b�t�@����ւ�
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);


}


void FDDraw()
{
	// ��ʂƐ[�x�o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//�t�B�[���h�g���ɂ�3D�p�̏������K�v

	// �r���[�|�[�g�Z�b�g
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//�e���̉�ʃT�C�Y���g��

		// �A�X�y�N�g�������Ă���
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//�e���̉�ʃT�C�Y���g��

	// 3D �p�v���W�F�N�V�����}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//�J�����g�s��Ƀv���W�F�N�V�����s�񂪏�Z�����

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //�J�������W
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //�J���������_
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //����x�N�g��

	// 3D �p�i���f���j�r���[�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//�J�����g�s��Ƀr���[�s���Z�����



	g_Field->Draw();

	// �t�����g�o�b�t�@�E�o�b�N�o�b�t�@����ւ�
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);
}





//*****************************************************************************
// �\���̒�`
//*****************************************************************************
void OpenGLDraw3D()
{
	// ��ʂƐ[�x�o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �r���[�|�[�g�Z�b�g
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//�e���̉�ʃT�C�Y���g��
	/******************************************************************************/
	/*2D �� 3D �Ńv���W�F�N�V�����E�i���f���j�r���[�s��̐ݒ�͂�������؂�ւ��邱��*/
	/******************************************************************************/

	//2D
	//================================================================================
	// ���C�e�B���O����
	glDisable(GL_LIGHTING);
		// 2D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);//�v�G���W�F�N�V�����s�񑀍샂�[�h

	glPushMatrix();//���݂̃v���W�F�N�V�����s���ۑ�

	glLoadIdentity();//���݂̃v���W�F�N�V�����s���P�ʍs��ɂ���

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);//���s���e�s��Z�b�g

	glMatrixMode(GL_MODELVIEW);//���f���r���[�s�񑀍샂�[�h

	glPushMatrix();//���݂̃��f���r���[�s���ۑ�

	glLoadIdentity();//���݂̃��f���r���[�s���P�ʍs��ɂ���


	// �e�N�X�`���̃n���h���ݒ�
	glBindTexture(GL_TEXTURE_2D, g_Texture);


	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);		//�`�惂�[�h���w�肵�ăf�[�^�Z�b�g�J�n

	glColor4f(1.0, 0.0, 0.0, 1.0f);	//���_�O�Ԗځ@���_�J���[�Z�b�g
	glTexCoord2f(0, 0);		//���_�O�Ԗځ@�e�N�X�`�����W�Z�b�g
	glVertex3f(100, 100, 0);	//���_�O�Ԗځ@���_���W�Z�b�g

	glColor4f(0.0, 1.0, 0.0, 1.0f);
	glTexCoord2f(0, -1);
	glVertex3f(100, 300, 0);

	glColor4f(0.0, 0.0, 1.0, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(300, 100, 0);

	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glTexCoord2f(1, -1);
	glVertex3f(300, 300, 0);

	glEnd();				//��񕪂̕`��Z�b�g�I��

	//2D�`��I��
	//==========================================================================================
	
	
	//3D�`��
	//===========================================================================================================
	// �A�X�y�N�g�������Ă���
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//�e���̉�ʃT�C�Y���g��

	// 3D �p�v���W�F�N�V�����}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//�J�����g�s��Ƀv���W�F�N�V�����s�񂪏�Z�����

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //�J�������W
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //�J���������_
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //����x�N�g��

	// 3D �p�i���f���j�r���[�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//�J�����g�s��Ƀr���[�s���Z�����

		// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();//�J�����g�s����R�s�[

	glBindTexture(GL_TEXTURE_2D, g_Texture); // �e�N�X�`���ݒ�

	static GLfloat angle = 0.0f;//�f�o�b�O�p

	glRotatef(angle, 1.0f, 0.0f, 0.0f);//���݂̃J�����g�s��� X ��]�s�񂪏�Z�����

	angle += 1.0f;//�p�x�X�V

	// 3D �I�u�W�F�N�g�̕`��
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0, 0.0, 0.0, 1.0f);//���_�J���[
	glNormal3f(0, 1, 0); //�@��
	glTexCoord2f(0, 0); //�e�N�X�`�����W
	glVertex3f(-100, 0, 100); //���_���W

	glColor4f(0.0, 1.0, 0.0, 1.0f);
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(100, 0, 100);

	glColor4f(0.0, 0.0, 1.0, 1.0f);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-100, 0, -100);

	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(100, 0, -100);

	glEnd();



	// ���f���r���[�}�g���N�X�𕜌�
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//�J�����g�s����폜

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);

	// �t�����g�o�b�t�@�E�o�b�N�o�b�t�@����ւ�
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);
}