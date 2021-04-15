#ifndef NW_STD_CONTAINER_H
#define NW_STD_CONTAINER_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename vtype, size_tc slots>
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
#endif	// NW_STD_CONTAINER_H