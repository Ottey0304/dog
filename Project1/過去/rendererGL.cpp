#include "main.h"
#include "rendererGL.h"
#include "manager.h"
#include "renderer.h"

HDC m_hDC;
HWND g_Window2;
HGLRC m_hGLRC;

//HWND GetWindow()
//{
//	return g_Window;
//}

void OpenGL::Init()
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
	m_hDC = GetDC(g_Window2);

	//���̐ݒ�Ŏg�p�ł���s�N�Z���t�H�[�}�b�g���擾���Đݒ�
	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	//GL�R���e�L�X�g�쐬���Đݒ�i�`����Ǘ�����I�u�W�F�N�g�j
	m_hGLRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hGLRC);


	// OpenGL�`��ݒ� �������̍Ō�ɂ���Ă�����{�ݒ�
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


}

void OpenGL::Update()
{

}

void OpenGL::Draw()
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
	HDC m_hDC = GetDC(g_Window2);
	SwapBuffers(m_hDC);


}

void OpenGL::Uninit()
{
	// Window�f�o�C�X�R���e�L�X�g�擾
	HDC	m_hDC;//���g�̃E�B���h�E�̃f�o�C�X�R���e�L�X�g
	m_hDC = GetDC(g_Window2);

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(g_Window2, m_hDC);
	wglDeleteContext(m_hGLRC);
}