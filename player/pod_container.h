#ifndef H_POD_CONTAINER
#define H_POD_CONTAINER

#include "pod_item.h"

struct pod_container
{
	char* name;
	std::list<pod_item> item;

	pod_container()
	{
		name = "empty";
	};
};

#endif;