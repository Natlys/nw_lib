#ifndef NW_STD_ARRAY_H
#define NW_STD_ARRAY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tval, size_tc slots>
	using t_sarray = std::array<tval, slots>;
	template <typename tval>
	using t_darray = std::vector<tval>;
}
#endif	// NW_API
#endif	// NW_STD_ARRAY_H