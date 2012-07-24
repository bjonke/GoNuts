#include <iostream>
#include <ctime>
#include <cstdio>
using namespace std;
#include <windows.h>
#include "CVector.h"
#include "graphics.h"
#include "timing.h"
#include "LoadMap.h"
#include "Clevels.h"
#include "pod_cube.h"
#include "pod_room.h"
#include "world.h"
/*--------------------------------------------
	GLOBALS
----------------------------------------------*/

struct PLAYER
{
	char Name[64];
	int x;
	int y;
	int Score;
	int Velocity;
	int PrevX;
	int PrevY;
	int LastX;
	int LastY;
	double nuts;
	HBITMAP hIcon;
	BITMAP Icon;
	
	int Capacity;
	bool Badnut;
	
} Player;

// handle till minnes device context
HDC Tiles_DC = NULL;
struct TILES
{
	HBITMAP hApple;
	BITMAP Apple;
	HBITMAP hBanana;
	BITMAP Banana;
	HBITMAP hWall;
	HBITMAP hExit;
	BITMAP Wall;
	BITMAP Exit;

	HBITMAP hIntro;
	BITMAP Intro;
} Tile;

RECT rect;
RECT clear;
RECT object;
RECT player;
// For main handle to device context
HDC gDC = 0;
// for back (double) buffering

HDC		BackBuffer = 0;	
HBITMAP BackBuffer_bmp = 0;
HBITMAP Old_bmp = 0;

static int Bag[3][3];

cTiming FPScounter;

world zone;

bool CGraphics::Init(HWND hwnd)
{
	zone.populate();
	main_window_handle = hwnd;

	CLevels* leveltest = 0;

	Player.Badnut = false;

	QueryPerformanceFrequency(&ticksPerSecond);
	QueryPerformanceFrequency(&FPScounter.ticksPerSecond);

	// Load map and display Messagebox if error
	if (! LoadMap(hwnd,"level1.txt" ) )
	{
		MessageBox(hwnd, TEXT("Error in opening level file\n"), TEXT("Error"), MB_ICONERROR | MB_OK);
		return false;
	}

	// Setting bools for movement to false so there is no movement
	up = false;
	down = false;
	right = false;
	left = false;

	velocity = 10;
	Player.Velocity = 1;
	col = 0;
	row = 0;
	x = 0;
	y = 0;
	Player.nuts = 0;
	Player.Capacity = 9;
	showmenu = false;
	Splash = true;

	//squrl
	Player.x = 0;
	Player.y = 0;

	gDC = GetDC(hwnd);

	// För BackBuffer (Dubbel) buffring
	BackBuffer = CreateCompatibleDC(gDC);
	BackBuffer_bmp = CreateCompatibleBitmap(gDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Old_bmp = (HBITMAP)SelectObject(BackBuffer, BackBuffer_bmp);

	//-------------------------------------------------------------------
		// Ladddar in bmp bilder för alla objekt i spelet
	Player.hIcon = (HBITMAP)LoadImage(NULL,"Squirrel.bmp",
										IMAGE_BITMAP, 0, 0,
										LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if( Player.hIcon == 0 )
	{
		MessageBox(hwnd,TEXT("Error, no player.bmp in directory\n"), TEXT("Error"),MB_ICONERROR | MB_OK);
		return false;
	}

	Tile.hApple = (HBITMAP)LoadImage(NULL, "Apple.bmp",
                                    IMAGE_BITMAP, 0, 0,
                                    LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if( Tile.hApple == 0 )
	{
		MessageBox(hwnd,TEXT("Error, no Apple.bmp in directory\n"), TEXT("Error"),MB_ICONERROR | MB_OK);
		return false;
	}

	Tile.hBanana = (HBITMAP)LoadImage(NULL, "Banana.bmp",
                                    IMAGE_BITMAP, 0, 0,
                                    LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if( Tile.hBanana == 0 )
	{
		MessageBox(hwnd,TEXT("Error, no Banana.bmp in directory\n"), TEXT("Error"),MB_ICONERROR | MB_OK);
		return false;
	}

	Tile.hIntro = (HBITMAP)LoadImage(NULL, "Splash.bmp",
                                    IMAGE_BITMAP, 0, 0,
                                    LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if( Tile.hIntro == 0 )
	{
		MessageBox(hwnd,TEXT("Error, no Banana.bmp in directory\n"), TEXT("Error"),MB_ICONERROR | MB_OK);
		return false;
	}
	
	Tiles_DC = CreateCompatibleDC(NULL);

	GetObject(Player.hIcon,sizeof(BITMAP), &Player.Icon);
	GetObject(Tile.hWall, sizeof(BITMAP), &Tile.Wall);
	GetObject(Tile.hExit, sizeof(BITMAP), &Tile.Exit);
	GetObject(Tile.hIntro, sizeof(BITMAP), &Tile.Intro);
	GetObject(Tile.hApple, sizeof(BITMAP), &Tile.Apple);
	GetObject(Tile.hBanana, sizeof(BITMAP), &Tile.Banana);


	return true;
}

void CGraphics::EraseScreen()
{
	ValidateRect(main_window_handle,&clear);
	GetClientRect(main_window_handle,&clear);
	FillRect(BackBuffer, &clear, (HBRUSH)GetStockObject(WHITE_BRUSH));
}

void CGraphics::SplashScreen()
{
	SelectObject(Tiles_DC,Tile.hIntro);
	BitBlt(BackBuffer, 0, 0, 
	Tile.Intro.bmWidth, Tile.Intro.bmHeight, Tiles_DC, 0, 0, SRCCOPY);

	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
		GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	if(KEY_DOWN(VK_SPACE))
		Splash = false;
}

void CGraphics::RandomTest()
{
	//int thing = Random() % 2;
	for(col = 0; col < 15; col++)
	{
		for(row = 0; row < 20; row++)
		{
			//hämtar in tecken
			//char c = Map_file.get();
			//konverterar tecknet till integer
			//levelFigure[row][col] = atoi(&c);
		}
	}
}
void CGraphics::Menu()
{
	if(showmenu)
	{
		SetTextColor(BackBuffer,RGB(255,0,0));
		SetBkColor(BackBuffer,RGB(255,255,255));

		GetClientRect(main_window_handle,&rect);

		rect.top = 240;
		DrawText(BackBuffer,"1.Start\n2.Restart\n3.Exit",-1,&rect, DT_CENTER);

		SetTextColor(BackBuffer,RGB(255,255,255));

		if(KEY_DOWN(0x31))
		{
			LoadMap(main_window_handle,"level2.txt");
		//	Init(main_window_handle);
		}
		if(KEY_DOWN(0x32))
		{
		}
		if(KEY_DOWN(0x33))
		{
			showmenu = false;
		}

		BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
			GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);
	}
}

bool CGraphics::Input()
{
	if(KEY_DOWN(VK_ESCAPE))
	{
		PostQuitMessage(0);
		return true;
	}

	if(KEY_DOWN(VK_UP))
		up = true;
	if(KEY_UP(VK_UP))
		up = false;

	if(KEY_DOWN(VK_DOWN))
		down = true;
	if(KEY_UP(VK_DOWN))
		down = false;

	if(KEY_DOWN(VK_RIGHT))
		right = true;
	if(KEY_UP(VK_RIGHT))
		right = false;

	if(KEY_DOWN(VK_LEFT))
		left = true;
	if(KEY_UP(VK_LEFT))
		left = false;
	return true;
	
	if(KEY_DOWN(VK_F3))
		showmenu = true;
	return false;
}

bool CGraphics::Paint()
{
	FPScounter.StartTimer();
	//velocity test
	x = Player.x;
	y = Player.y;
	Player.PrevX =Player.x;
	Player.PrevY = Player.y;
	Player.Velocity = velocity;
	//Movement
	if(left == true && Player.x > 0)
	{
		if(Player.x < col_size)
		{
			//Player.x = 300;
		}
		else
		{
			Player.x -= 32;//Player.Velocity;
			Sleep(100);
		}

	}
	else if(Player.x < 0)
	{
		left = false;
		Player.x = 0;
	}

	if(right == true && Player.x < 606)
	{
		Player.x += Player.Velocity;
	}
	else if(Player.x > 606)
	{
		right = false;
		Player.x = 606;
	}

	if(up == true && Player.y > 0)
	{
		Player.y -= Player.Velocity;
	}
	else if(Player.y < 0)
	{
		up = false;
		Player.y = 0;
	}

	if(down == true && Player.y < 446)
	{
		Player.y += Player.Velocity;
	}
	else if(Player.y > 446)
	{
		down = false;
		Player.y = 446;
	}
	/*
	for(int i = 0; i < 3; i++)
	{
		for(col = 0; col < zone.room[i].cube.size(); col++)
		{
			SelectObject(Tiles_DC,Tile.hApple);
			BitBlt(BackBuffer, zone.room[i].cube.at(col).x, zone.room[i].cube.at(col).y, 
			Tile.Apple.bmWidth, Tile.Apple.bmHeight, Tiles_DC, 0, 0, SRCAND);
		}
	}*/

	// bag of nuts
	for(col = 0; col < 3; col++)
	{
		for(row = 0; row < 3; row++)
		{
			if(Bag[col][row] == 1)
			{
				SelectObject(Tiles_DC,Tile.hApple);
				BitBlt(BackBuffer, 547 + col*Tile.Apple.bmWidth, 0 + row*Tile.Apple.bmHeight, 
				Tile.Apple.bmWidth, Tile.Apple.bmHeight, Tiles_DC, 0, 0, SRCAND);
			}
		}
	}

	// Render map
	for(col = 0; col < col_size; col++)
	{
		for(row = 0; row < row_size; row++)
		{
			if(levelFigure[col][row] == 3)
			{
				SelectObject(Tiles_DC,Tile.hApple);

				BitBlt(BackBuffer, col*Tile.Apple.bmWidth, row*Tile.Apple.bmWidth, 
					Tile.Apple.bmWidth, Tile.Apple.bmHeight, Tiles_DC, 0, 0, SRCCOPY);
			}
			else
			if(levelFigure[col][row] == 1)
			{
				SelectObject(Tiles_DC,Tile.hBanana);

				BitBlt(BackBuffer, col*Tile.Banana.bmWidth, row*Tile.Banana.bmWidth, 
					Tile.Banana.bmWidth, Tile.Banana.bmHeight, Tiles_DC, 0, 0, SRCCOPY);
			}
		}
	}

	///////////////////////////////////////////////
	FillRect(BackBuffer, &object, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if(Player.x > 600)
	{
		EmptyBag();
		Player.Capacity = 9;
		if (! LoadMap(main_window_handle,"level1.txt" ) )
		{
			MessageBox(main_window_handle, TEXT("Error in opening level file\n"), TEXT("Error"), MB_ICONERROR | MB_OK);
			return false;
		}
	}
					
	SelectObject(Tiles_DC,Player.hIcon);

	BitBlt(BackBuffer, Player.x, Player.y, Player.Icon.bmWidth, Player.Icon.bmHeight, Tiles_DC, 0, 0, SRCAND);	


	//Page flipping
	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	//fps counter
	Status();

	return true;
}

bool CGraphics::Collecting(int x, int y)
{
	if(Player.Capacity == 0)
	{
		TextOut(BackBuffer,200,460,"You must drop of collected nuts", strlen("You must drop of collected nuts"));
		return false;
	}
	if(levelFigure[x][y] == 3)
	{
		Player.Score -= 1000;
		Player.nuts += 1;
		Player.Capacity -= 1;
		object.top += 10;
		Player.Badnut = true;
		levelFigure[x][y] = 0;
		SquirrelSick();
		FillBag();
		return true;
	}
	if(levelFigure[x][y] == 1)
	{
		//if(left)
		//	Player.x--;
		//if(right)
		//	Player.x++;
		//if(up)
		//	Player.y--;
		//if(down)
		//	Player.y++;
		
		Player.Score += 200;
		Player.nuts += 1;
		Player.Capacity -= 1;
		Player.x += 8;
		object.top -= 1;
		levelFigure[x][y] = 0;
		Player.Badnut = false;
		SquirrelSick();
		FillBag();
		return true;
	}
	return false;
}

bool CGraphics::Status()
{
	//FPScounter.Wait(60);
//	FPScounter.FPSloop();
	return true;
}

bool CGraphics::GameFinished()
{
	if(Player.Score == 1000)
		LoadMap(main_window_handle,"level2.txt" );
	return true;
}

bool CGraphics::SquirrelSick()
{
	if(Player.Badnut)
	{
		TextOut(BackBuffer,450,300,"SICK!",strlen("SICK!"));
		velocity = 4;
	}
	else
		velocity = 4;
	return true;
}

bool CGraphics::FillBag()
{
	if(Player.Capacity == 8)
		Bag[0][0] = 1;
	if(Player.Capacity == 7)
		Bag[0][1] = 1;
	if(Player.Capacity == 6)
		Bag[0][2] = 1;
	if(Player.Capacity == 5)
		Bag[1][0] = 1;
	if(Player.Capacity == 4)
		Bag[1][1] = 1;
	if(Player.Capacity == 3)
		Bag[1][2] = 1;
	if(Player.Capacity == 2)
		Bag[2][0] = 1;
	if(Player.Capacity == 1)
		Bag[2][1] = 1;
	if(Player.Capacity == 0)
		Bag[2][2] = 1;


	return true;
}

//Resetting the bag to be empty
void CGraphics::EmptyBag()
{
	for(col = 0; col < 3; col++)
	{
		for(row = 0; row < 3; row++)
		{
			if(Bag[col][row] == 1)
			{
				Bag[col][row] = 0;
			}
		}
	}
}

void CGraphics::Text()
{
	char buffer[100];

	RECT TextWindow;
	TextWindow.bottom = 500;
	TextWindow.top = 100;
	TextWindow.left =	520;
	TextWindow.right = 640;

	SetTextColor(BackBuffer,RGB(255,0,0));
	SetBkColor(BackBuffer,RGB(255,255,255));

	sprintf(buffer,"Score: %d",Player.Score);
	DrawText(BackBuffer,buffer,-1,&TextWindow, 0);
	sprintf(buffer,"\nNuts: %.0f", Player.nuts);
	DrawText(BackBuffer,buffer,-1, &TextWindow, 0);
}

CGraphics::CGraphics()
{
}
