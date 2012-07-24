#ifndef H_POD_ROOM
#define H_POD_ROOM

#include <cmath>
using namespace std;

#include "pod_cube.h"
#include "macros.h"

struct pod_room
{
	int size;
	int x;
	int y;
	std::vector<pod_cube> cube;
	pod_room()
	{
		Log(__FILE__,__LINE__,"room constructed");
		size = 4;
		x=rand()%300;
		y=rand()%300;

		Log3n(__FILE__,__LINE__,"coords",x,y,size);
		for(int i=0; i < size; ++i)
		{
			for(int j=0; j < size; ++j)
			{
				Log(__FILE__,__LINE__,"cube");
				pod_cube build_cube;
				build_cube.x = x + i*32;
				build_cube.y = y + j*32;
				Log3n(__FILE__,__LINE__,"coords",build_cube.x,build_cube.y,0);
				cube.push_back(build_cube);
			}
		}
	};
};

#endif;