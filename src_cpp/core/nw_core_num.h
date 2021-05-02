#ifndef NW_CORE_NUM_H
#define NW_CORE_NUM_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
// basics
#	define NW_NUM_EULER            ( NW_CAST_FLOAT(2.7'1828'1828'4590) )
#	define NW_NUM_POW(num, base)   ( std::pow(num, base) )
#	define NW_NUM_ABS(num)         ( std::abs(num) )
#	define NW_NUM_MIN(num0, num1)  ( std::min(num0, num1) )
#	define NW_NUM_MAX(num0, num1)  ( std::max(num0, num1) )
#	define NW_NUM_CLAMP(num, lower, upper)    ( NW_NUM_MIN(NW_NUM_MAX(num, lower), upper) )
#	define NW_NUM_LERP(lower, upper, percent) ( (upper - lower) * (1.0f - percent) )
// trigonometry
#	define NW_NUM_PI            ( NW_CAST_FLOAT(3.141'592'653) )
#	define NW_NUM_RAD           ( NW_CAST_FLOAT(57.295'779 )
#	define NW_NUM_TO_DEG(angle) ( NW_CAST_FLOAT(angle) / NW_NUM_PI * NW_CAST_FLOAT(180.0))
#	define NW_NUM_TO_RAD(angle) ( NW_CAST_FLOAT(angle) * NW_NUM_PI / NW_CAST_FLOAT(180.0))
#	define NW_NUM_ANGLE(angle)  ( NW_NUM_TO_RAD(angle) )
#	define NW_NUM_COS(angle)    ( std::cosf(NW_NUM_ANGLE(angle)) )
#	define NW_NUM_SIN(angle)    ( std::sinf(NW_NUM_ANGLE(angle)) )
#	define NW_NUM_TANG(angle)   ( NW_NUM_SIN(angle) / NW_NUM_COS(angle) )
#	define NW_NUM_CTAN(angle)   ( NW_NUM_COS(angle) / NW_NUM_SIN(angle) )
#	define NW_NUM_ROOT(num, base)  ( std::pow(num, 1.0f / base) )
// combinatorics
#	define NW_NUM_FACTOR(num) ( nw_num_get_factor(num) )
#	define NW_NUM_PERMUT(from, what, repeat) repeat ?                                          \
		( NW_NUM_POW(from) ) :                                                                 \
		( NW_NUM_FACTOR(from) / NW_NUM_FACTOR(from - what) )                                   \
// NW_NUM_PERMUT
#	define NW_NUM_COMBIN(from, what, repeat) repeat ?                                          \
		( NW_NUM_FACTOR(what + from + 1u) / NW_NUM_FACTOR(what) / NW_NUM_FACTOR(from - 1u) ) : \
		( NW_NUM_FACTOR(from) / NW_NUM_FACTOR(what) / NW_NUM_FACTOR(from - what) )             \
// NW_NUM_COMBIN
// arithmetics
namespace NW
{
	template<typename ntype> ntype nw_num_get_abs(ntype n) { return n < 0 ? -n : n; }
	template<typename ntype> ntype nw_num_get_max(ntype n0, ntype n1) { return n0 > n1 ? n0 : n1; }
	template<typename ntype> ntype nw_num_get_min(ntype n0, ntype n1) { return n0 < n1 ? n0 : n1; }
	template<typename ntype> ntype nw_num_get_clamp(ntype nmin, ntype nmax, ntype naverage) { return get_max<ntype>(nmin, get_min<ntype>(nmax, naverage)); }
	template<typename ntype> ntype nw_num_get_lerp(ntype nmin, ntype nmax, float npercent) { return (nmax - nmin) * npercent; }
}
// combinatorics
namespace NW
{
	inline cv1u nw_num_get_factor(v1u num) { v1u fact(1u); while (num > 0u) { fact *= num--; } return fact; }
	inline cv1u nw_num_get_produc(v1u from)           { return nw_num_get_factor(from); }
	inline cv1u nw_num_get_produc(v1u what, v1u from) { return nw_num_get_factor(from) / nw_num_get_factor(from - what); }
	template<cv1b repeat> inline cv1u nw_num_get_permut(v1u num) { v1u fact(1u); while (num > 0u) { fact *= num--; } return fact; }
	template<cv1b repeat> inline cv1u nw_num_get_combin(v1u num) { v1u fact(1u); while (num > 0u) { fact *= num--; } return fact; }
}
// trigonometry
namespace NW
{
	template<typename ntype> ntype nw_num_get_pi() { return static_cast<ntype>(3.14159265359); }
	template<typename ntype> ntype nw_num_deg_to_rad(ntype deg) { return deg * get_pi<ntype>() / 180.0; }
	template<typename ntype> ntype nw_num_rad_to_deg(ntype rad) { return rad * 180.0 / get_pi<ntype>(); }
	template<typename ntype> ntype nw_num_apx_sin(ntype rad) { ntype temp = 180.0 - rad; return (rad * (temp * 4)) / (40500 - rad * (ntemp)); }
	template<typename ntype> ntype nw_num_apx_cos(ntype rad) { ntype temp = apx_sin(rad); return get_sqrt(); }
}
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_NUM_H