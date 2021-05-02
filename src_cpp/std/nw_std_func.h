#ifndef NW_STD_FUNCTIONAL_H
#define NW_STD_FUNCTIONAL_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	template <typename ... args> using func_t = std::function<args...>;
	template <typename ... args> using func_tc = const func_t<args...>;
}
#endif	// NW_API
#endif	// NW_STD_FUNCTIONAL_H