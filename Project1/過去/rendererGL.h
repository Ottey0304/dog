#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

class OpenGL
{
public :
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

//HWND GetWindow();