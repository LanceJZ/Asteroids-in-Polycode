#pragma once
#include "Asteroids.h"
#include "windows.h"
#include "resource.h"

#define IDI_MYICON 201

using namespace Polycode;
std::unique_ptr<Asteroids> pAsteroids;
Core *pCore;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PolycodeView *view = new PolycodeView(hInstance, nCmdShow, L"Asteroids Beta 1.45");
	// 	Core (int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex)
	pCore = new POLYCODE_CORE(view, 800, 720, false, true, 0, 0, 240, 0, true);

	pAsteroids = std::unique_ptr<Asteroids>( new Asteroids(view, pCore));
	
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
	SendMessage(view->hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hMyIcon);

	MSG Msg;

	do
	{
		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		pCore->doSleep();
	} 
	while (pAsteroids->Update());

	return Msg.wParam;
}