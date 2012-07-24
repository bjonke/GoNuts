#ifndef H_CREATOR
#define H_CREATOR

#include "pod_room.h"

struct creator
{
	creator()
	{
	};

	pod_room create_room()
	{
		pod_room room;
		return room;
	};
};

#endif;