#ifndef H_POD_BALL
#define H_POD_BALL

struct pod_ball
{
	float x;
	float y;
	int tile;
	bool updating;
	bool in_endzone;
	bool active;
	bool carried;
	pod_ball()
	{
		carried = false;
		x = 0;
	};

	void update()
	{
	};

	void reset()
	{
		x = 5;
		y = 5;
		carried = false;
		active = true;
		in_endzone = false;
		updating = false;
		//tile = 0;
	};
};

#endif