#include "pod_player.h"
#include "pod_ball.h"

pod_ball player_ball;

int pass()
{
	return rand()%5;
};

void pod_player::update()
{
	if( MA == 0 )
	{
		carries_ball = false;
	}

	if(tackled)
	{
		knocked_down = true;
		MA = 0;
		tackled = false;
		updating = false;
	}
};

bool pod_player::grabbed(pod_ball b)
{
	player_ball = b;
	player_ball.carried = true;
	carries_ball = true;
	return true;
};

pod_ball pod_player::update_ball()
{
	player_ball.x = x;
	player_ball.y = y;
	return player_ball;
};