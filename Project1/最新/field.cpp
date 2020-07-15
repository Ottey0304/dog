
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
	// ライティング無効
	glDisable(GL_LIGHTING);

	// マトリクス退避
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	

	static GLfloat angle = 0.0f;//デバッグ用
	static GLfloat angle2 = 0.0f;//デバッグ用
	GLfloat posx = sinf(angle2*(3.14 / 180.0f))*50.0f;

	// テクスチャ設定
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// ポリゴン描画
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
	// マトリクス復元
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ライティング無効
	glDisable(GL_LIGHTING);

	// マトリクス退避
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// テクスチャ設定
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTranslatef(posx, 0.0f, 0.0f);//平行
	glRotatef(angle, 0.0f, 1.0f, 0.0f);//現在のカレント行列に y 回転行列が乗算される
	
	glScalef(1.0f, 1.0f, 1.0f);
	//glScalef//拡大縮小

	angle += 10.0f;//角度更新
	angle2 += 3.0f;

	// ポリゴン描画
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

	// マトリクス復元
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ライティング有効
	glEnable(GL_LIGHTING);
}