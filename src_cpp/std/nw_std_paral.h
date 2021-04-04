#ifndef NW_STD_PARALLEL_H
#define NW_STD_PARALLEL_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	using thread = std::thread;
	using thread_locker = std::mutex;
}
#endif	// NW_API
#endif	// NW_STD_PARALLEL_H