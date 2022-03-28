//--------------------------------------------
//	INCLUDES
//--------------------------------------------
#include <iostream>
#include "graphics.h"
#include "input.h"

//--------------------------------------------
//	GLOBALS
//--------------------------------------------

// Handle to Tiles device context
//HDC Tiles_DC = 0;
// Main graphic handle to device context
//HDC gDC = 0;

//--------------------------------------------
//	BACK(double) BUFFERING
//--------------------------------------------

// Handle to BackBuffer context
//HDC		BackBuffer = 0;
//HBITMAP BackBuffer_bmp = 0;
//HBITMAP Old_bmp = 0;
//--------------------------------------------

//RECT rect;

PlayerSDL Player;
InputSDL* Logic = 0;
//CInput* Logic = 0;

TilesSDL Tile;

// Initiating everything for the start of the game
bool GraphicsSDL::Init()
{
	//main_window_handle = chwnd;

	//Logic = new CInput(FieldSize,FieldSize);
	Logic = new InputSDL(FieldSize,FieldSize);

	// Den används av både player 1 och 2

	//Player.hIcon = (HBITMAP)LoadImage(NULL,"Badger.bmp",
	//	IMAGE_BITMAP, 0, 0,	LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	//GetObject(Player.hIcon,sizeof(BITMAP), &Player.Icon);

	//------------------------------------------------------------------
	// Splash screen stuff
	//------------------------------------------------------------------
	Splash = true;

	//Tile.hIntro = (HBITMAP)LoadImage(NULL, "Splash.bmp",
	//	IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);


	ShowMenu = true;

	//gDC = GetDC(main_window_handle);

	// För BackBuffer (Dubbel) buffring
	//BackBuffer = CreateCompatibleDC(gDC);
	//BackBuffer_bmp = CreateCompatibleBitmap(gDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//Old_bmp = (HBITMAP)SelectObject(BackBuffer, BackBuffer_bmp);

	//-------------------------------------------------------------------
	// Ladddar in bmp bilder för alla objekt i spelet


	//Tile.hBadAcorn = (HBITMAP)LoadImage(NULL, "BadAcorns.bmp",
    //                                IMAGE_BITMAP, 0, 0,
    //                                LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	//Tile.hAcorn = (HBITMAP)LoadImage(NULL, "Acorns.bmp",
    //                                IMAGE_BITMAP, 0, 0,
    //                                LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// För BackBuffer (Dubbel) buffring
	//BackBuffer = CreateCompatibleDC(gDC);
	//BackBuffer_bmp = CreateCompatibleBitmap(gDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//Old_bmp = (HBITMAP)SelectObject(BackBuffer, BackBuffer_bmp);

	//Tiles_DC = CreateCompatibleDC(NULL);


	//GetObject(Tile.hIntro, sizeof(BITMAP), &Tile.Intro);
	//GetObject(Tile.hBadAcorn, sizeof(BITMAP), &Tile.BadAcorn);
	//GetObject(Tile.hAcorn, sizeof(BITMAP), &Tile.Acorn);

	return true;
}

void GraphicsSDL::EraseScreen()
{
	//ValidateRect(main_window_handle,&rect);
	//GetClientRect(main_window_handle,&rect);
	//FillRect(BackBuffer, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
}

void GraphicsSDL::SplashScreen()
{
}

void GraphicsSDL::Menu()
{
	if(ShowMenu)
	{
        /*
		SetTextColor(BackBuffer,RGB(255,0,0));
		SetBkColor(BackBuffer,RGB(255,255,255));

		GetClientRect(main_window_handle,&rect);

		rect.top = 240;

		if(MenuChoiceOne == 0)
		{
 			DrawText(BackBuffer,"1.Start\n2.Restart\n3.Exit",-1,&rect, DT_CENTER);
		}
		else
		{
			DrawText(BackBuffer,"1.Return to game\n2.Restart\n3.Exit",-1,&rect, DT_CENTER);
		}



		SetTextColor(BackBuffer,RGB(255,255,255));


		if(KEY_DOWN('1'))
		{
			if(!Logic->CheckForAcorns())
				Logic->SpreadAcorns();
			MenuChoiceOne = 1;
			ShowMenu = false;
		}

		if(KEY_DOWN('2'))
		{
			Logic->Reset();
			ShowMenu = false;
		}

		if(KEY_DOWN('3'))
		{
			PostQuitMessage(0);
		}

		BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);
			*/
	}
}

void GraphicsSDL::Input()
{
	Logic->KeyPress();
	Logic->Collecting();
	Logic->Sick();
	if(!Logic->CheckForAcorns())
	{
		GameFinished();
		Logic->Reset();
		ShowMenu = true;
	}
}

bool GraphicsSDL::Render()
{
	// Renders the different Acorns on the playing field to the backbbuffer
	for(Col = 0; Col < FieldX; Col++)
	{
		for(Row = 0; Row < FieldY; Row++)
		{
			if(Logic->AcornField[Col][Row] == 3)
			{
				//SelectObject(Tiles_DC,Tile.hBadAcorn);

				//BitBlt(BackBuffer, Col*Tile.BadAcorn.bmWidth, Row*Tile.BadAcorn.bmWidth,
				//	Tile.BadAcorn.bmWidth, Tile.BadAcorn.bmHeight, Tiles_DC, 0, 0, SRCCOPY);
			}
			if(Logic->AcornField[Col][Row] == 1)
			{
				//SelectObject(Tiles_DC,Tile.hAcorn);

				//BitBlt(BackBuffer, Col*Tile.Acorn.bmWidth, Row*Tile.Acorn.bmWidth,
				//	Tile.Acorn.bmWidth, Tile.Acorn.bmHeight, Tiles_DC, 0, 0, SRCCOPY);
			}
		}
	}
	///////////////////////////////////////////////

	// Selects the Player bitmap and paints the player in the backbuffer
	//SelectObject(Tiles_DC,Player.hIcon);

	//BitBlt(BackBuffer, Logic->Xloc(), Logic->Yloc(), Player.Icon.bmWidth, Player.Icon.bmHeight, Tiles_DC, 0, 0, SRCAND);

	//BitBlt(BackBuffer, Logic->Xloc2(), Logic->Yloc2(), Player.Icon.bmWidth, Player.Icon.bmHeight, Tiles_DC, 0, 0, SRCAND);
	////////////////////////////////////////////////////////

	//Page flipping
	//BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	return true;
}

void GraphicsSDL::GameFinished()
{
    /*
	SetTextColor(BackBuffer,RGB(255,0,0));
	SetBkColor(BackBuffer,RGB(255,255,255));

	GetClientRect(main_window_handle,&rect);
	rect.top = 240;

	if( Logic->GameFinished() == 1)
	{
		DrawText(BackBuffer,"Player 1 won!\nPress Space to return to menu",-1,&rect, DT_CENTER);
	}
	else
	{
		DrawText(BackBuffer,"Player 2 won!\nPress Space to return to menu",-1,&rect, DT_CENTER);
	}

	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN),
	GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	while(!KEY_DOWN(VK_SPACE))
	{
	}
    */
	ShowMenu = true;
}

void GraphicsSDL::Text()
{
    /*
	char buffer[100];

	RECT PlayerStats;
	RECT Player2Stats;

	PlayerStats.bottom = 505;
	PlayerStats.top = 485;
	PlayerStats.left =	0;
	PlayerStats.right = 320;

	Player2Stats.bottom = 505;
	Player2Stats.top = 485;
	Player2Stats.left =	320;
	Player2Stats.right = 640;

	SetTextColor(BackBuffer,RGB(255,0,0));
	SetBkColor(BackBuffer,RGB(255,255,255));

	sprintf(buffer,"Player 1 Score: %d Acorns: %d",Logic->Score(), Logic->Acorns());
	DrawText(BackBuffer,buffer,-1,&PlayerStats, 0);

	sprintf(buffer,"Player 2 Score: %d Acorns: %d",Logic->Score2(), Logic->Acorns2());
	DrawText(BackBuffer,buffer,-1,&Player2Stats, 0);
	*/
}

GraphicsSDL::GraphicsSDL(int x, int y) : FieldX(x), FieldY(y)
{
	//main_window_handle = 0;
	Row = 21;
	Col = 0;
	ShowMenu = false;
	Splash = true;
	MenuChoiceOne = 0;
}
