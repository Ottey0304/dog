
#include "main.h"
#include "manager.h"
#include "openGl.h"


COpenGl g_openGl;


void CManager::Init(HWND window)
{
	g_openGl.Init(window);
}


void CManager::Uninit(HWND window)
{
	g_openGl.Uninit(window);
}


void CManager::Update()
{
	g_openGl.Update();
}


void CManager::Draw(HWND window)
{
	g_openGl.Draw(window);
}