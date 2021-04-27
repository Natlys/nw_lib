#ifndef NW_STD_ARRAY_H
#define NW_STD_ARRAY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tval, size_tc slots>
	using sarray_t = std::array<tval, slots>;
	template <typename tval, size_tc slots>
	using sarray_tc = const std::array<tval, slots>;
	template <typename tval>
	using darray_t = std::vector<tval>;
	template <typename tval>
	using darray_tc = const std::vector<tval>;
}
#endif	// NW_API
#endif	// NW_STD_ARRAY_H