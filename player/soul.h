#ifndef H_SOUL
#define H_SOUL

#include <vector>
using namespace std;
#include "pod_skill.h"
#include "actions.h"

struct soul
{
	int MA;
	int ST;
	int AG;
	int AV;
	int zone_of_influense;
	std::vector<pod_skill> skill;
	actions perform_action;

	soul()
	{
		MA = 0;
		ST = 0;
		AG = 0;
		AV = 0;
		zone_of_influense = 1;
	};
};

#endif