#ifndef NWL_PHYSX_COLLISION_H
#define NWL_PHYSX_COLLISION_H
#include <nwl_core.hpp>
#include <math/math_vec.h>
namespace NW
{
	bit is_collision_pt_rt(v2f xyPoint, v2f rect_left_top, v2f rect_right_bot);
	bit is_collision_rt_rt(v2f rect0_left_top, v2f rect0_right_bot, v2f rect1_left_top, v2f rect1_right_bot);
}
#endif	// NWL_PHYSICS_COLLISION_H