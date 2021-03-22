#include <nwl_pch.hpp>
#include "nwl_info.h"
namespace NW
{
	a_info::a_info()
	{
	}
	// --setters
	// --operators
	stm_out& operator<<(stm_out& stm, const a_info& info) { return info.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_info& info) { return info.operator>>(stm); }
}