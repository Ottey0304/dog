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
	// ピクセルフォーマット
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),//構造体のサイズ
		1,                  //
		PFD_DRAW_TO_WINDOW |//OpenGLでダブルバッファを使い
		PFD_SUPPORT_OPENGL |//ウィンドウへ描画する
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,      //RGBA形式のピクセル情報を使う
		24,                 //RGB24ビット
		0, 0, 0, 0, 0, 0,   //この辺から未使用
		0,
		0,
		0,
		0, 0, 0, 0,
		32,        //深度バッファ32ビット         
		0,         //この辺から未使用         
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};



	// Windowデバイスコンテキスト取得
	HDC	m_hDC;//自身のウィンドウのデバイスコンテキスト
	m_hDC = GetDC(g_Window2);

	//この設定で使用できるピクセルフォーマットを取得して設定
	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	//GLコンテキスト作成して設定（描画を管理するオブジェクト）
	m_hGLRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hGLRC);


	// OpenGL描画設定 初期化の最後にやっておく基本設定
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
	// 画面と深度バッファをクリア
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// <<<<<<<<<<<<<ここで全て描画
	// ライティング無効
	glDisable(GL_LIGHTING);

	// 2D用マトリクス設定
	glMatrixMode(GL_PROJECTION);//プエロジェクション行列操作モード
	glPushMatrix();//現在のプロジェクション行列を保存
	glLoadIdentity();//現在のプロジェクション行列を単位行列にする
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);//平行投影行列セット
	glMatrixMode(GL_MODELVIEW);//モデルビュー行列操作モード
	glPushMatrix();//現在のモデルビュー行列を保存
	glLoadIdentity();//現在のモデルビュー行列を単位行列にする

	// ポリゴン描画
	glBegin(GL_TRIANGLE_STRIP);		//描画モードを指定してデータセット開始

	glColor4f(1.0, 0.0, 0.0, 1.0f);	//頂点０番目　頂点カラーセット
	glTexCoord2f(0, 0);		//頂点０番目　テクスチャ座標セット
	glVertex3f(100, 100, 0);	//頂点０番目　頂点座標セット

	glColor4f(0.0, 1.0, 0.0, 1.0f);
	glTexCoord2f(0, -1);
	glVertex3f(100, 300, 0);

	glColor4f(0.0, 0.0, 1.0, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(300, 100, 0);

	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glTexCoord2f(1, -1);
	glVertex3f(300, 300, 0);

	glEnd();				//一回分の描画セット終了

	// ライティング有効
	glEnable(GL_LIGHTING);

	// 各マトリクス設定を戻す
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();//上のPUSHとセット
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//上のPUSHとセット



	// フロントバッファ・バックバッファ入れ替え
	HDC m_hDC = GetDC(g_Window2);
	SwapBuffers(m_hDC);


}

void OpenGL::Uninit()
{
	// Windowデバイスコンテキスト取得
	HDC	m_hDC;//自身のウィンドウのデバイスコンテキスト
	m_hDC = GetDC(g_Window2);

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(g_Window2, m_hDC);
	wglDeleteContext(m_hGLRC);
}