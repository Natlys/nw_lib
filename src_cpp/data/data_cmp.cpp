#include <nwl_pch.hpp>
#include "data_cmp.h"
#include "data_sys.h"
namespace NW
{
	a_data_cmp::a_data_cmp()
	{
	}
	a_data_cmp::~a_data_cmp() { }
	// --setters
	// --operators
	stm_out& operator<<(stm_out& stm, const a_data_cmp& cmp) { return cmp.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_data_cmp& cmp) { return cmp.operator>>(stm); }
	// --==<core_methods>==--
	// --==</core_methods>==--
}