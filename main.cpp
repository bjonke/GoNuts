#include <windows.h>
#include <ctime>
#include "graphics.h"
#include "macros.h"
//#include "pod_room.h"
//#include "world.h"
/**********************************************************************
* Globaler
/*********************************************************************/
CGraphics* GfxEngine = 0;
int ClientSizeY = 480;
int ClientSizeX = 640;

HDC hDC = 0;

int game_state = 0;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

/***************************************************************************************
	Main window entry point
****************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow) 
{
	InitLog();
	TCHAR szAppName[] = "Go nuts";
	HWND hwnd;
	MSG			msg = {0};
	WNDCLASS	wndclass ;

	wndclass.style			= CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc	= WndProc ;
	wndclass.cbClsExtra		= 0 ;
	wndclass.cbWndExtra		= 0 ;
	wndclass.hInstance		= hInstance ;
	wndclass.hIcon			= LoadIcon (hInstance, IDI_APPLICATION) ;
	wndclass.hCursor		= LoadCursor (hInstance, IDC_ARROW) ;
	wndclass.hbrBackground	= (HBRUSH) GetStockObject (BLACK_BRUSH) ;
	wndclass.lpszMenuName	= NULL ;
	wndclass.lpszClassName	= szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires a advanced windows"),
					szAppName, MB_ICONERROR) ;
		return 0;
	}
	
	GfxEngine = new CGraphics();
	
	// Huvudfönstret
	hwnd = CreateWindow (szAppName,		// Window class name
						 szAppName,	//window caption
						 WS_POPUP | WS_BORDER,
						 0,
						 0,
						 ClientSizeX,
						 ClientSizeY,
						 NULL,
						 NULL,
						 hInstance,
						 NULL) ;

	srand ( time(0) );

	ShowWindow(hwnd, iCmdShow) ;
	UpdateWindow(hwnd);

	GfxEngine->Init(hwnd);

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage (&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GfxEngine->EraseScreen();
			GfxEngine->Text();
			GfxEngine->Input();
			GfxEngine->SquirrelSick();
			GfxEngine->Collecting(GfxEngine->x/32,GfxEngine->y/32);
			if(GfxEngine->Splash)
				GfxEngine->SplashScreen();

			if(GfxEngine->showmenu)
				GfxEngine->Menu();
			if(!GfxEngine->Splash && !GfxEngine->showmenu)
				GfxEngine->Paint();
			GfxEngine->GameFinished();
		}
	}
	return(msg.wParam) ;
}

/*******************************************************************************
* LRESULT CALLBACK WndProc() sköter grovjobbet
/*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_QUIT:
		PostQuitMessage (0) ;
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}