#ifndef NW_STD_RANDOM_H
#define NW_STD_RANDOM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "mat/nw_mat_vec.h"
#	include "mat/nw_mat_mtx.h"
namespace NW
{
	// --getters
	template<typename tname>
	tname get_rand(tname minv = static_cast<tname>(0), tname maxv = static_cast<tname>(1)) {
		static std::mt19937 s_rand_engine(clock());
		constexpr double fraction = 1.0 / (static_cast<v1f>(s_rand_engine.max()));
		return  static_cast<tname>(s_rand_engine() * fraction * (maxv - minv) + minv);
	}
	template<typename tname, size_tc size_x>
	t_vec<tname, size_x> get_rand(tname minv, tname maxv) {
		t_vec<tname, size_x> result;
		for (v1u ix = 0u; ix < size_x; ix++) {
			result[ix] = get_rand<tname>(minv, maxv);
		}
		return result;
	}
	template<typename tname, size_tc size_x, size_tc size_y>
	t_mat<tname, size_x, size_y> get_rand(tname minv, tname maxv) {
		t_mat<tname, size_x, size_y> result;
		for (v1u iy = 0u; iy < size_y; iy++) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[iy][ix] = get_rand<tname>(minv, maxv);
			}
		}
		return result;
	}
}
#endif	// NW_API
#endif	// NW_STD_RANDOM_H