#ifndef NW_STD_LIST_H
#define NW_STD_LIST_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tval>
	using t_list2 = std::list<tval>;
}
#endif	// NW_API
#endif // NW_STD_LIST_H