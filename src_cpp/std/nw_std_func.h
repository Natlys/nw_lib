#ifndef NW_STD_FUNCTIONAL_H
#define NW_STD_FUNCTIONAL_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename arg>
	using func = std::function<arg>;
}
#endif	// NW_API
#endif	// NW_STD_FUNCTIONAL_H