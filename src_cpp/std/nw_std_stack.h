#ifndef NW_STD_STACK_H
#define NW_STD_STACK_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename tval>
	using t_stack = std::stack<tval>;
}
#endif	// NW_API
#endif // NW_STD_STACK_H