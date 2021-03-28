#ifndef NWLIB_STD_THREAD_H
#define NWLIB_STD_THREAD_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	using thread = std::thread;
	using thread_locker = std::mutex;
}
#endif	// NW_API
#endif	// NWLIB_STD_THREAD_H