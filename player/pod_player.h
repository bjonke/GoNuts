#ifndef H_POD_PLAYER
#define H_POD_PLAYER

#include <list>
#include <stdlib.h>
using namespace std;

#include "soul.h"
#include "pod_item.h"
#include "pod_container.h"
struct pod_ball;

struct pod_player : public soul, pod_item
{
	std::list<pod_container> container;
	float x;
	float y;
	int tile;
	
	bool performed_action;
	bool updating;
	bool selected; //true if it is the active player
	bool tackled;
	bool knocked_down;
	int direction;
	bool carries_ball;
	
	struct tackle_zone
	{
		int x;
		int y;
	}area[9];

	pod_player()
	{
		performed_action = false;
		carries_ball = false;
		updating = false;
		direction = 5;
		knocked_down = false;
		tackled = false;
		selected = false;
		for(int i=0;i< 9; i++) 
		{
			  area[i].x = 0;
			  area[i].y = 0;
		}
		x = 0;
		y = 0;
		set_tackle_zone();
	};

	void set_tackle_zone()
	{
		// 123
		// 456
		// 789
		area[0].x = this->x - 1;
		area[0].y = this->y - 1;
		area[1].x = this->x;
		area[1].y = this->y -1;
		area[2].x = this->x + 1;
		area[2].y = this->y - 1;

		area[3].x = this->x;
		area[3].y = this->y;
		area[4].x = this->x + 1;
		area[4].y = this->y;
		area[5].x = this->x - 1;
		area[5].y = this->y;

		area[6].x = this->x - 1;
		area[6].y = this->y + 1;
		area[7].x = this->x;
		area[7].y = this->y + 1;
		area[8].x = this->x + 1;
		area[8].y = this->y + 1;
	};

	void subtract()
	{
		if( MA > 0)
		{
			MA--;
		}
	};

	void update();
	bool grabbed(pod_ball b);
	pod_ball update_ball();
	int pass();
};

#endif
