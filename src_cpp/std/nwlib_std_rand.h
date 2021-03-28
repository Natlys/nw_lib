#ifndef NWLIB_STD_RANDOM_H
#define NWLIB_STD_RANDOM_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	extern std::mt19937 s_rand_engine;
	// --getters
	template<typename nt> NW_API nt get_rand(nt nmin = 0.0, nt nmax = 1.0) {
		constexpr v1f fraction = 1.0 / (static_cast<v1f>(s_rand_engine.max()));
		return  static_cast<nt>(static_cast<nt>(s_rand_engine()) * fraction * (nmax - nmin)) + nmin;
	}
}
#endif	// NW_API
#endif	// NWLIB_STD_RANDOM_H