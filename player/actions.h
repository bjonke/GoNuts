#ifndef H_ACTIONS
#define H_ACTIONS

#include "macros.h"
#include "pod_ball.h"
#include "pod_item.h"
#include "pod_container.h"

struct actions
{
	pod_skill learn_skill(char* name)
	{
		Log( __FILE__ , __LINE__ , name );
		pod_skill temp;
		temp.name = name;
		return temp;
	};

	void throw_obj(pod_ball& obj, float x, float y)
	{
		Log1n( __FILE__ , __LINE__ , "Ball", obj.x );
		Log3n( __FILE__ , __LINE__ , "passed to ", x , y, 0);
		obj.x = x;
		obj.y = y;
	};

	void put_obj(pod_item& obj, pod_container& con)
	{
		Log( __FILE__ , __LINE__ , obj.name);
		Log( __FILE__ , __LINE__ , " put into ");
		Log( __FILE__ , __LINE__ , con.name );
		con.item.push_front(obj);
	};

	void get_obj(pod_container& con)
	{
		Log( __FILE__ , __LINE__ , con.item.front().name);
		Log( __FILE__ , __LINE__ , " removed from ");
		Log( __FILE__ , __LINE__ , con.name );
		con.item.pop_front();
	};

	void tackle(char* victim)
	{
		Log( __FILE__ , __LINE__ , "You tackle ");
		Log( __FILE__ , __LINE__ , victim);
	};

	void move(float x, float y)
	{

	};
};

#endif;
