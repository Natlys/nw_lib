#ifndef NW_STD_UTILITY_H
#define NW_STD_UTILITY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tval1, typename tval2>
	using t_pair = std::pair<tval1, tval2>;
}
#endif	// NW_API
#endif	// NW_STD_UTILITY_H