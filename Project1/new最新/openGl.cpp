
#include "main.h"
#include "openGl.h"
#include <windows.h>
#include <GL/gl.h>
#include "textureGL.h"
#include "model.h"
#include "player.h"


#define TEXTURE_FILE_2D	"asset\\texture\\texture2.tga"
#define MODEL_FILE		"asset\\model\\cube.obj"


CModel box;


void COpenGl::Init(HWND window)
{
	// �s�N�Z���t�H�[�}�b�g
	PIXELFORMATDESCRIPTOR pfd = {
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
	m_hDC = GetDC(window);

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


	box.Load(MODEL_FILE);
}


void COpenGl::Uninit(HWND window)
{
	// �e�N�X�`���̉��
	UnloadTexture(g_Texture);

	// Window�f�o�C�X�R���e�L�X�g�擾
	HDC	m_hDC;//���g�̃E�B���h�E�̃f�o�C�X�R���e�L�X�g
	m_hDC = GetDC(window);

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(window, m_hDC);
	wglDeleteContext(m_hGLRC);


	box.Unload();
}


void COpenGl::Update()
{

}


void COpenGl::Draw(HWND window)
{
	// ��ʂƐ[�x�o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	COpenGl::Draw3d();

	// �t�����g�o�b�t�@�E�o�b�N�o�b�t�@����ւ�
	HDC m_hDC = GetDC(window);
	SwapBuffers(m_hDC);
}


void COpenGl::Draw3d()
{
	// �r���[�|�[�g�Z�b�g 
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//�e���̉�ʃT�C�Y���g�� 

	/******************************************************************************/
	/*2D �� 3D �Ńv���W�F�N�V�����E�i���f���j�r���[�s��̐ݒ�͂�������؂�ւ��邱��*/
	/******************************************************************************/
	// �A�X�y�N�g�������Ă��� 
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//�e���̉�ʃT�C�Y���g�� 
	// 3D �p�v���W�F�N�V�����}�g���N�X�ݒ� 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ��� 
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//�J�����g�s��Ƀv���W�F�N�V�����s�񂪏�Z�����

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f);  //�J�������W 
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f);  //�J���������_ 
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f);  //����x�N�g�� 

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

	//glBindTexture(GL_TEXTURE_2D, m_nTexture); // �e�N�X�`���ݒ� 

	//static GLfloat angle = 0.0f;//�f�o�b�O�p 
	//glRotatef(angle, 1.0f, 0.0f, 0.0f);//���݂̃J�����g�s��� X ��]�s�񂪏�Z����� 
	//angle += 1.0f;//�p�x�X�V 

	static GLfloat angle = 0.0f;
	static GLfloat angle2 = 0.0f;

	GLfloat posx = sinf(angle2 * (3.14159 / 180.0f)) * 50.0f;
	glTranslatef(posx, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	angle += 1.5f;
	angle2 += 0.0f; //3.0f;

	glBindTexture(GL_TEXTURE_2D, g_Texture);

	// 3D �I�u�W�F�N�g�̕`�� 
	glBegin(GL_TRIANGLE_STRIP);

	//glColor4f(1.0, 0.0, 0.0, 1.0f);//���_�J���[ 
	//glNormal3f(0, 1, 0);  //�@�� 
	//glTexCoord2f(0, 0);  //�e�N�X�`�����W 
	//glVertex3f(-100, 0, 100);  //���_���W 

	//glColor4f(0.0, 1.0, 0.0, 1.0f);
	//glNormal3f(0, 1, 0);
	//glTexCoord2f(1, 0);
	//glVertex3f(100, 0, 100);

	//glColor4f(0.0, 0.0, 1.0, 1.0f);
	//glNormal3f(0, 1, 0);
	//glTexCoord2f(0, 1);
	//glVertex3f(-100, 0, -100);

	//glColor4f(1.0, 1.0, 1.0, 1.0f);
	//glNormal3f(0, 1, 0);
	//glTexCoord2f(1, 1);
	//glVertex3f(100, 0, -100);

	glEnd();


	box.Draw();


	// ���f���r���[�}�g���N�X�𕜌� 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//�J�����g�s����폜 

	// ���C�e�B���O�L�� 
	glEnable(GL_LIGHTING);
}