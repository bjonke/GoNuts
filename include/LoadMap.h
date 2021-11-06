#ifndef INC_LOADMAP_H
#define INC_LOADMAP_H

#include <fstream>
using namespace std;

#include "pod_room.h"


#define MAP_X_SIZE 100;
#define MAP_Y_SIZE 100;
#define GOOD_NUT 1;

int levelFigure[100][100];
int col_size;
int row_size;

void init_map(HWND hwnd, char *map_file)
{
	int _x=0,_y=0;

	for(_x = 0; _x < 100; _x++)
	{
		for(_y = 0; _y < 100; _y++)
		{
			levelFigure[_x][_y] = GOOD_NUT;
		}
	}
}

BOOL LoadMap(HWND hwnd, char *MapFile)
{
	int col;
	int row;
	char c;

	col_size = 0;
	row_size = 0;

	ifstream Map_file ( MapFile, ios_base::in);

	if ( !Map_file.is_open() ) 
	{
		return false;
	}

	Map_file >> col_size;
	Map_file >> row_size;

	for(col = 0; col < col_size; col++)
	{
		for(row = 0; row < row_size; row++)
		{
			levelFigure[row][col] = 1;
		}
	}

	for(col = 0; col < col_size; col++)
	{
		for(row = 0; row < row_size; row++)
		{
			Map_file >> c;
			levelFigure[row][col] = atoi(&c);
		}
	}
	
	Map_file.close();

	return true;
}

#endif
