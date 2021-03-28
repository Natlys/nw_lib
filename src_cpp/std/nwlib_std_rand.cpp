#include "nwlib_pch.hpp"
#include "nwlib_std_rand.h"
#if (defined NW_API)
std::mt19937 NWLIB::s_rand_engine(clock());
namespace NWLIB
{
	//
}
#endif	// NW_API