#ifndef NW_NUM_VALUE_H
#define NW_NUM_VALUE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	static constexpr inline cv1u get_dgt_count(v1u num, cv1u base) {
		v1u count(NW_NULL);
		while (num > 0) { count += 1; num /= base; }
		return count;
	}
	static constexpr inline cv1u get_dgt_count(v1u num, cv1u base, cv1u dgt) {
		v1u count(NW_NULL);
		while (num > 0) { if (num % base == dgt) { count += 1; } num /= base; }
		return count;
	}
	// --getters
	template<typename tname> static constexpr tname get_rand(tname vmin = NW_NULL, tname vmax = NW_UNIT) {
		static std::mt19937 s_rand_engine(clock());
		constexpr double fraction = 1.0 / (static_cast<v1f>(s_rand_engine.max()));
		return  static_cast<tname>(s_rand_engine() * fraction * (vmax - vmin) + vmin);
	}
}
#endif	// NW_API
#endif	// NW_STD_RANDOM_H