#include <nwl_pch.hpp>
#include "mem_sys.h"

namespace NW
{
	mem_sys::mem_sys() :
		mem_arena(new sbyte[NW_MAX_GLOBAL_MEMORY], NW_MAX_GLOBAL_MEMORY)
	{
		if (get_data() != nullptr) { return; }
	}
	mem_sys::~mem_sys()
	{
		if (m_data_ptr != nullptr) { delete[] m_data_ptr; m_data_ptr = nullptr; }
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}