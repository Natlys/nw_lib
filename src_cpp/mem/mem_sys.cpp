#include <nwl_pch.hpp>
#include "mem_sys.h"

#include <ecs/ecs_ent_sys.h>
#include <ecs/ecs_cmp_sys.h>
#include <data/data_sys.h>

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
		data_sys::get().get_ent_reg().clear();
		data_sys::get().get_cmp_reg().clear();
		if (m_data_ptr != nullptr) { delete[] m_data_ptr; m_data_ptr = nullptr; }
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}