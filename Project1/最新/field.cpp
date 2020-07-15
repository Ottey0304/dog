
#include "main.h"
//#include "renderer.h"
#include "field.h"
#include "textureGL.h"
#include "vector.h"



void CField::Init()
{
	m_Texture = LoadTexture((char*)"asset\\texture\\texture.tga");
}


void CField::Uninit()
{
	//UnloadTexture(m_Texture);
}


void CField::Update()
{

}


void CField::Draw()
{
	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// �}�g���N�X�ޔ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	

	static GLfloat angle = 0.0f;//�f�o�b�O�p
	static GLfloat angle2 = 0.0f;//�f�o�b�O�p
	GLfloat posx = sinf(angle2*(3.14 / 180.0f))*50.0f;

	// �e�N�X�`���ݒ�
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 0, 100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(100, 0, 100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-100, 0, -100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(1, 1);
	glVertex3f(100, 0, -100);

	glEnd();
	// �}�g���N�X����
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// �}�g���N�X�ޔ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// �e�N�X�`���ݒ�
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTranslatef(posx, 0.0f, 0.0f);//���s
	glRotatef(angle, 0.0f, 1.0f, 0.0f);//���݂̃J�����g�s��� y ��]�s�񂪏�Z�����
	
	glScalef(1.0f, 1.0f, 1.0f);
	//glScalef//�g��k��

	angle += 10.0f;//�p�x�X�V
	angle2 += 3.0f;

	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 50, 100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(100, 50, 100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-100, 50, -100);

	glColor4f(0.6, 1.0, 0.4, 1.0f);
	glTexCoord2f(1, 1);
	glVertex3f(100, 50, -100);

	glEnd();

	// �}�g���N�X����
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);
}