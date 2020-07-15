
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
	// ピクセルフォーマット
	PIXELFORMATDESCRIPTOR pfd = {
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
	m_hDC = GetDC(window);

	//この設定で使用できるピクセルフォーマットを取得して設定
	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	//GLコンテキスト作成して設定（描画を管理するオブジェクト）
	m_hGLRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hGLRC);

	// 画像ファイル読み込み、ハンドル保存
	g_Texture = LoadTexture((char*)TEXTURE_FILENAME);

	// OpenGL描画設定 初期化の最後にやっておく基本設定
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


	box.Load(MODEL_FILE);
}


void COpenGl::Uninit(HWND window)
{
	// テクスチャの解放
	UnloadTexture(g_Texture);

	// Windowデバイスコンテキスト取得
	HDC	m_hDC;//自身のウィンドウのデバイスコンテキスト
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
	// 画面と深度バッファをクリア
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	// テクスチャのハンドル設定
	glBindTexture(GL_TEXTURE_2D, g_Texture);

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

	COpenGl::Draw3d();

	// フロントバッファ・バックバッファ入れ替え
	HDC m_hDC = GetDC(window);
	SwapBuffers(m_hDC);
}


void COpenGl::Draw3d()
{
	// ビューポートセット 
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//各自の画面サイズを使う 

	/******************************************************************************/
	/*2D と 3D でプロジェクション・（モデル）ビュー行列の設定はしっかり切り替えること*/
	/******************************************************************************/
	// アスペクト比を作っておく 
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//各自の画面サイズを使う 
	// 3D 用プロジェクションマトリクス設定 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//カレント行列を単位行列にする 
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//カレント行列にプロジェクション行列が乗算される

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f);  //カメラ座標 
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f);  //カメラ注視点 
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f);  //上方ベクトル 

	// 3D 用（モデル）ビューマトリクス設定 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//カレント行列を単位行列にする 
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//カレント行列にビュー行列乗算される 

	// ライティング無効 
	glDisable(GL_LIGHTING);

	// モデルビューマトリクスの設定 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//カレント行列をコピー 

	//glBindTexture(GL_TEXTURE_2D, m_nTexture); // テクスチャ設定 

	//static GLfloat angle = 0.0f;//デバッグ用 
	//glRotatef(angle, 1.0f, 0.0f, 0.0f);//現在のカレント行列に X 回転行列が乗算される 
	//angle += 1.0f;//角度更新 

	static GLfloat angle = 0.0f;
	static GLfloat angle2 = 0.0f;

	GLfloat posx = sinf(angle2 * (3.14159 / 180.0f)) * 50.0f;
	glTranslatef(posx, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	angle += 1.5f;
	angle2 += 0.0f; //3.0f;

	glBindTexture(GL_TEXTURE_2D, g_Texture);

	// 3D オブジェクトの描画 
	glBegin(GL_TRIANGLE_STRIP);

	//glColor4f(1.0, 0.0, 0.0, 1.0f);//頂点カラー 
	//glNormal3f(0, 1, 0);  //法線 
	//glTexCoord2f(0, 0);  //テクスチャ座標 
	//glVertex3f(-100, 0, 100);  //頂点座標 

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


	// モデルビューマトリクスを復元 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//カレント行列を削除 

	// ライティング有効 
	glEnable(GL_LIGHTING);
}