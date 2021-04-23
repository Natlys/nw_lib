#include "nw_lib_pch.hpp"
#include "nw_ecs_ent_sys.h"
#if (defined NW_API)
namespace NW
{
	ent_sys::ent_sys()
	{
	}
	ent_sys::~ent_sys()
	{
	}
	// --==<core_methods>==--
	v1bit ent_sys::init()
	{
		NW_CHECK(t_ecs_sys::init(), "failed init!", return NW_FALSE);
		return NW_TRUE;
	}
	v1bit ent_sys::quit()
	{
		NW_CHECK(t_ecs_sys::quit(), "failed quit!", return NW_FALSE);
		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API