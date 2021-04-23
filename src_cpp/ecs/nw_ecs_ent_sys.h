#ifndef NW_ECS_ENTITY_SYSTEM_H
#define NW_ECS_ENTITY_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_ecs_sys.h"
#	include "nw_ecs_ent.h"
namespace NW
{
	/// entity_system singleton class
	class NW_API ent_sys : public t_ecs_sys<ent_sys, a_ent>
	{
	public:
	public:
		ent_sys();
		~ent_sys();
		// --core_methods
		v1bit init();
		v1bit quit();
	private:
	};
}
#endif	// NW_API
#endif // NW_ECS_ENTITY_SYSTEM_H