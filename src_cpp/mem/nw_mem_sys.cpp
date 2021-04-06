#include "nw_lib_pch.hpp"
#include "nw_mem_sys.h"
#if (defined NW_API)
#include "ecs/nw_ecs_ent_sys.h"
#include "ecs/nw_ecs_cmp_sys.h"
namespace NW
{
	mem_sys::mem_sys() :
		mem_arena(new sbyte[NW_MAX_MEMORY], NW_MAX_MEMORY)
	{
		if (get_data() != nullptr) { return; }
	}
	mem_sys::~mem_sys()
	{
		ent_sys::get().get_ent_reg().clear();
		cmp_sys::get().get_cmp_reg().clear();
		//io_sys::get().get_ent_reg().clear();
		//io_sys::get().get_cmp_reg().clear();
		if (m_data_ptr != nullptr) { delete[] m_data_ptr; m_data_ptr = nullptr; }
	}
	// --==<core_methods>==--
	void mem_sys::update()
	{
	}
	// --==</core_methods>==--
}
#endif	// NW_API