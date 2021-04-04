#ifndef NW_STD_RANDOM_H
#define NW_STD_RANDOM_H
#include "nw_lib_pch.hpp"
#if (defined NW_API)
namespace NW
{
	// --getters
	template<typename nt> nt get_rand(nt nmin = 0.0, nt nmax = 1.0) {
		static std::mt19937 s_rand_engine(clock());
		constexpr double fraction = 1.0 / (static_cast<v1f>(s_rand_engine.max()));
		return  static_cast<nt>(static_cast<nt>(s_rand_engine()) * fraction * (nmax - nmin)) + nmin;
	}
}
#endif	// NW_API
#endif	// NW_STD_RANDOM_H