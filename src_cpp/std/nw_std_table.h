#ifndef NW_STD_TABLE_H
#define NW_STD_TABLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tkey, typename tval>
	using t_table = std::unordered_map<tkey, tval>;
}
#endif	// NW_API
#endif	// NW_STD_TABLE_H