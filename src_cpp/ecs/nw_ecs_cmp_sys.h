#ifndef NW_ECS_COMPONENT_SYSTEM_H
#define NW_ECS_COMPONENT_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_ecs_sys.h"
#	include "nw_ecs_cmp.h"
namespace NW
{
	/// component_system singleton class
	class NW_API cmp_sys : public t_ecs_sys<cmp_sys, a_cmp>
	{
	public:
		cmp_sys();
		~cmp_sys();
		// --getters
		// --setters
		// --predicates
		// --core_methods
		v1bit init();
		v1bit quit();
	private:
	};
}
#endif	// NW_API
#endif	// NW_ECS_COMPONENT_SYSTEM_H