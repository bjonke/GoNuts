#ifndef H_POD_CUBE
#define H_POD_CUBE

#include <vector>
using namespace std;
#include "pod_entity.h"

struct pod_cube
{
   int x, y, z;
   bool up,down,left,right,top,bottom;
   std::vector<pod_entity> monster;	
};

#endif;