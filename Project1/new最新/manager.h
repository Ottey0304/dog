
#pragma once


class CManager
{
public:
	static void Init(HWND window);
	static void Uninit(HWND window);
	static void Update();
	static void Draw(HWND window);
};