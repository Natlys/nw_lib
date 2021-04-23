#include "nw_lib_pch.hpp"
#include "nw_mem_sys.h"
#if (defined NW_API)
namespace NW
{
	mem_sys::mem_sys() :
		mem_alloc_arena(NW_NULL, NW_NULL)
	{
	}
	mem_sys::~mem_sys()
	{
		NW_CHECK(!has_data() && !has_size(), "no quit!", return)
	}
	// --==<core_methods>==--
	v1bit mem_sys::init()
	{
		NW_CHECK(!has_data(), "init is already done!!", return NW_FALSE);
		NW_CHECK(has_size(), "no size!", return NW_FALSE);
		set_data(new byte_t[get_size()]);
		NW_CHECK(mem_alloc_arena::remake(), "failed remake!", return NW_FALSE);

		return NW_TRUE;
	}
	v1bit mem_sys::quit()
	{
		NW_CHECK(has_data(), "quit is already done!", return NW_FALSE);
		NW_CHECK(has_size(), "no size!", return NW_FALSE);
		
		if (has_data()) { delete[] get_data(); set_data(NW_NULL); }
		if (has_size()) { set_size(NW_NULL); }

		return NW_TRUE;
	}
	v1nil mem_sys::update()
	{
	}
	// --==</core_methods>==--
}
#endif	// NW_API