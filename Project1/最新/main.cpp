
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
const char* WINDOW_NAME = "AT13E_09_金澤浩亮";

CField* g_Field;
//COpenGL* g_OpenGL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HGLRC	m_hGLRC;  //GLコンテキスト
HDC		m_hDC;


#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(600)				// ウインドウの高さ



#define TEXTURE_FILENAME "asset/texture/texture.tga"

int g_Texture;

#define VIEW_ANGLE (45.0f) // 視野角
#define VIEW_NEAR_Z (10.0f) // 近面距離
#define VIEW_FAR_Z (100000.0f) //遠面距離
VECTOR3D m_posP; // 視点
VECTOR3D m_posR; // 注視点
VECTOR3D m_vecUp; // 上方向ベクトル


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

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
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


	// 初期化処理(ウィンドウを作成してから行う)
	//CManager::Init();
	OpenGLInit();

	g_Field = new CField();
	g_Field->Init();
	

	/*g_OpenGL = new COpenGL();
	g_OpenGL->Init();*/


	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	//フレームカウント初期化
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// メッセージループ
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
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

				// 更新処理
				//CManager::Update();
				OpenGLUpdate();
				
				//g_Field->Update();

				//g_OpenGL->Update();

				// 描画処理
				//CManager::Draw();
				//OpenGLDraw();

				//OpenGLDraw3D();

				//g_OpenGL->Draw();

				FDDraw();
				
				
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	//CManager::Uninit();
	OpenGLUninit();

	g_Field->Uninit();
	delete g_Field;

	/*g_OpenGL->Uninit();
	delete g_OpenGL;*/

	return (int)msg.wParam;
}


//=============================================================================
// ウインドウプロシージャ
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


//こっから下ファイル分けたい
//=====================================================================================
void OpenGLInit()
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
	m_hDC = GetDC(g_Window);

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
}


void OpenGLUninit()
{
	//// Windowデバイスコンテキスト取得
	HDC	m_hDC;//自身のウィンドウのデバイスコンテキスト
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




	// フロントバッファ・バックバッファ入れ替え
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);


}


void FDDraw()
{
	// 画面と深度バッファをクリア
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//フィールド使うには3D用の準備が必要

	// ビューポートセット
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//各自の画面サイズを使う

		// アスペクト比を作っておく
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//各自の画面サイズを使う

	// 3D 用プロジェクションマトリクス設定
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//カレント行列を単位行列にする
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//カレント行列にプロジェクション行列が乗算される

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //カメラ座標
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //カメラ注視点
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //上方ベクトル

	// 3D 用（モデル）ビューマトリクス設定
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();//カレント行列を単位行列にする
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//カレント行列にビュー行列乗算される



	g_Field->Draw();

	// フロントバッファ・バックバッファ入れ替え
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);
}





//*****************************************************************************
// 構造体定義
//*****************************************************************************
void OpenGLDraw3D()
{
	// 画面と深度バッファをクリア
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ビューポートセット
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//各自の画面サイズを使う
	/******************************************************************************/
	/*2D と 3D でプロジェクション・（モデル）ビュー行列の設定はしっかり切り替えること*/
	/******************************************************************************/

	//2D
	//================================================================================
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

	//2D描画終了
	//==========================================================================================
	
	
	//3D描画
	//===========================================================================================================
	// アスペクト比を作っておく
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//各自の画面サイズを使う

	// 3D 用プロジェクションマトリクス設定
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//カレント行列を単位行列にする
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//カレント行列にプロジェクション行列が乗算される

	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //カメラ座標
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //カメラ注視点
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //上方ベクトル

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

	glBindTexture(GL_TEXTURE_2D, g_Texture); // テクスチャ設定

	static GLfloat angle = 0.0f;//デバッグ用

	glRotatef(angle, 1.0f, 0.0f, 0.0f);//現在のカレント行列に X 回転行列が乗算される

	angle += 1.0f;//角度更新

	// 3D オブジェクトの描画
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0, 0.0, 0.0, 1.0f);//頂点カラー
	glNormal3f(0, 1, 0); //法線
	glTexCoord2f(0, 0); //テクスチャ座標
	glVertex3f(-100, 0, 100); //頂点座標

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



	// モデルビューマトリクスを復元
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();//カレント行列を削除

	// ライティング有効
	glEnable(GL_LIGHTING);

	// フロントバッファ・バックバッファ入れ替え
	HDC m_hDC = GetDC(g_Window);
	SwapBuffers(m_hDC);
}