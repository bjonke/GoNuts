#ifndef INC_LOADMAP_H
#define INC_LOADMAP_H

#include <fstream>
using namespace std;

#include "pod_room.h"

int	levelFigure[200][200];
int col_size;
int row_size;
//pod_room room[200][200];

BOOL LoadMap(HWND hwnd, char *MapFile)
{
	int		col;
	int		row;
	char	c;

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
