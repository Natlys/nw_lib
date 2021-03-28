#ifndef NWLIB_STD_CONTAINER_H
#define NWLIB_STD_CONTAINER_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	template <typename vtype, size slots>
	using sarray = std::array<vtype, slots>;
	template <typename vtype>
	using darray = std::vector<vtype>;
	template <typename vtype>
	using dstack = std::stack<vtype>;
	template <typename vtype>
	using list2links = std::list<vtype>;
	template <typename ktype, typename vtype>
	using dictionary = std::unordered_map<ktype, vtype>;
	template <typename type1, typename type2>
	using pair = std::pair<type1, type2>;
}
#endif	// NW_API
#endif	// NWLIB_STD_CONTAINER_H