#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>

class GraphicsSDL
{
public:
	GraphicsSDL(){  };
	SDL_Point Field;
	int FieldX;
	int FieldY;
	int Row;
	int Col;
	int MenuChoiceOne;
	bool ShowMenu;
	bool Splash;

	bool Init();
	void SplashScreen();
	void EraseScreen();
	bool Render();
	void Text();
	void Menu();
	void Input();
	void GameFinished();
	void Release();

	GraphicsSDL(int x, int y);
};

#endif
