#ifndef NW_STD_STACK_H
#define NW_STD_STACK_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename vtype>
	using t_stack = std::stack<vtype>;
}
#endif	// NW_API
#endif // NW_STD_STACK_H