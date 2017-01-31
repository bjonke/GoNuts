#include <iostream>
#include <cstdio>

#include <SDL2/SDL.h>

#include "input.h"

void InputSDL::KeyPress()
{
	SDL_Event event;

        SDL_WaitEvent(&event);

        switch (event.type)
        {
		case SDL_QUIT:
		    //quit = true;
		    break;
		case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:  Character[0].Position.x -= Character[0].Velocity.x; break;
			case SDLK_RIGHT: Character[0].Position.x += Character[0].Velocity.x; break;
			case SDLK_UP:    Character[0].Position.y -= Character[0].Velocity.y; break;
			case SDLK_DOWN:  Character[0].Position.y += Character[0].Velocity.y; break;
			case SDLK_w: Character[1].Position.y -= Character[1].Velocity.y; break;
			case SDLK_a: Character[1].Position.x -= Character[1].Velocity.x; break;
			case SDLK_d: Character[1].Position.x += Character[1].Velocity.x; break;
			case SDLK_s: Character[1].Position.y += Character[1].Velocity.y; break;
		}
		break;
        }
};

void InputSDL::SpreadAcorns()
{
	for(int Col = 0; Col < 30; Col++)
	{
		for(int Row = 0; Row < 30; Row++)
		{
			AcornField[Row][Col] = rand() % 4;
		}
	}
};

bool InputSDL::CheckForAcorns()
{
	for(int Col = 0; Col < 30; Col++)
	{
		for(int Row = 0; Row < 30; Row++)
		{
			if(AcornField[Row][Col] == 1)
			{
				return true;
			}
		}
	}
	return false;
};

bool InputSDL::Collecting()
{
	// Player 1 stuff
	int xid = Character[0].Position.x/32;
	int yid = Character[0].Position.y/32;
	if(!(xid > FieldSize -1) && !(yid > FieldSize -1))
	{
		if(AcornField[xid][yid] == 1)
		{
			Character[0].Score += 100;
			Character[0].Acorns++;
			AcornField[xid][yid] = 0;
			Character[0].BadAcorn = false;
		}
		else if( AcornField[xid][yid] == 3)
		{
			AcornField[xid][yid] = 0;
			Character[0].BadAcorn = true;
		}
	}
	// Player 2 stuff
	xid = Character[1].Position.x/32;
	yid = Character[1].Position.y/32;

	if(!(xid > FieldSize -1) && !(yid > FieldSize -1))
	{
		if(AcornField[xid][yid] == 1)
		{
			Character[1].Score += 100;
			Character[1].Acorns++;
			AcornField[xid][yid] = 0;
		}
		else if( AcornField[xid][yid] == 3)
		{
			AcornField[xid][yid] = 0;
		}
	}
	return true;
};

bool InputSDL::Sick()
{
	if(Character[0].BadAcorn)
	{
		Character[0].Velocity.x = 1;
		Character[0].Velocity.y = 1;
	}
	else
	{
		Character[0].Velocity.x = 2;
		Character[0].Velocity.y = 2;
	}

	if(Character[1].BadAcorn)
	{
		Character[1].Velocity.x = 1;
		Character[1].Velocity.y = 1;
	}
	else
	{
		Character[1].Velocity.x = 2;
		Character[1].Velocity.y = 2;
	}
	return true;
};

int InputSDL::GameFinished()
{
 	if(Character[0].Acorns > Character[1].Acorns)
	{
		return 1;
	}
	else
	{
		return 2;
	}
	return 0;
}

int InputSDL::Acorns()
{
	return Character[0].Acorns;
}

int InputSDL::Acorns2()
{
	return Character[1].Acorns;
}

int InputSDL::Score()
{
	return Character[0].Score;
}

int InputSDL::Score2()
{
	return Character[1].Score;
}

int InputSDL::Xloc()
{
	return Character[0].Position.x;
}

int InputSDL::Yloc()
{
	return Character[0].Position.y;
}

int InputSDL::Xloc2()
{
	return Character[1].Position.x;
}

int InputSDL::Yloc2()
{
	return Character[1].Position.y;
}

int InputSDL::ShowSplash()
{
	return Splash;
}

void InputSDL::Reset()
{
	Character[0].BadAcorn = false;
	Character[0].Velocity.x = 1;
	Character[0].Velocity.y = 1;
	Character[0].Acorns = 0;
	Character[0].Position.x = 576;
	Character[0].Position.y = 0;
	Character[0].Score = 0;

	Character[1].BadAcorn = false;
	Character[1].Velocity.x = 1;
	Character[1].Velocity.y = 1;
	Character[1].Acorns = 0;
	Character[1].Position.x = 576;
	Character[1].Position.y = 448;
	Character[1].Score = 0;

	SpreadAcorns();

	Splash = 0;
}

InputSDL::InputSDL(int x, int y)
{
	Character[0].BadAcorn = false;
	Character[0].Velocity.x = 1;
	Character[0].Velocity.y = 1;
	Character[0].Acorns = 0;
	Character[0].Position.x = 576;
	Character[0].Position.y = 0;
	Character[0].Score = 0;

	Character[1].BadAcorn = false;
	Character[1].Velocity.x = 1;
	Character[1].Velocity.y = 1;
	Character[1].Acorns = 0;
	Character[1].Position.x = 576;
	Character[1].Position.y = 448;
	Character[1].Score = 0;

	SpreadAcorns();

	Splash = 0;
}
