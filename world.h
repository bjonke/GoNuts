#ifndef H_WORLD
#define H_WORLD

#include "creator.h"
#include "pod_room.h"
#include "player/pod_player.h"

struct world
{
	creator builder;
	pod_room room[10];
	pod_player someone;

	world()
	{
	};

	void populate()
	{
		pod_player vessel;
		pod_player vessel2;
		vessel2.x = 100;
		Log3n( __FILE__ , __LINE__ , "stats", vessel.AG, vessel.AV,vessel.MA);
		vessel.skill.push_back(vessel.perform_action.learn_skill("block"));
		vessel.skill.push_back(vessel.perform_action.learn_skill("blitz"));
		for( unsigned int i = 0; i < vessel.skill.size(); ++i)
		{
			Log( __FILE__ , __LINE__ , vessel.skill.at(i).name);
		}

		pod_ball ball;
		Log1n( __FILE__ , __LINE__ , "ef", ball.x );
		vessel.perform_action.throw_obj(ball,vessel2.x,vessel2.y);
		Log1n( __FILE__ , __LINE__ , "fe", ball.x );
		pod_container backpack;
		vessel.container.push_front(backpack);
		vessel.container.front().name = "Backpack";
		pod_item book;
		vessel.perform_action.put_obj(book,vessel.container.front());
		book.name = "book";
		vessel.perform_action.put_obj(book,vessel.container.front());
		vessel.perform_action.get_obj(vessel.container.front());
		vessel.perform_action.get_obj(vessel.container.front());
		vessel.perform_action.tackle(vessel.name);
		//for(int i=0; i < 10; ++i)
		//{
		//	room[i] = builder.create_room();
		//}
	};
};

#endif;