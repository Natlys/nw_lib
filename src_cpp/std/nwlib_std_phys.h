#ifndef NWLIB_STD_PHYSICS_H
#define NWLIB_STD_PHYSICS_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "nwlib_std_val.h"
namespace NWLIB
{
	v1b is_collision_pt_rt(v2f xyPoint, v2f rect_left_top, v2f rect_right_bot);
	v1b is_collision_rt_rt(v2f rect0_left_top, v2f rect0_right_bot, v2f rect1_left_top, v2f rect1_right_bot);
}
#endif	// NW_API
#endif	// NWLIB_STD_PHYSICS_H