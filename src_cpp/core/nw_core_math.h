#ifndef NW_CORE_MATH_H
#define NW_CORE_MATH_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
#define NW_MATH_PI              ( NW_CAST_FLOAT(3.1416) )
#define NW_MATH_RAD             ( NW_CAST_FLOAT(57.295) )
#define NW_MATH_TO_DEG(angle)   ( NW_CAST_FLOAT(angle) / NW_MATH_PI * NW_CAST_FLOAT(180.0))
#define NW_MATH_TO_RAD(angle)   ( NW_CAST_FLOAT(angle) * NW_MATH_PI / NW_CAST_FLOAT(180.0))
#define NW_MATH_ANGLE(angle)    ( NW_MATH_TO_RAD(angle) )
#define NW_MATH_COS(angle)      ( std::cosf(NW_MATH_ANGLE(angle)) )
#define NW_MATH_SIN(angle)      ( std::sinf(NW_MATH_ANGLE(angle)) )
#define NW_MATH_TANG(angle)     ( NW_MATH_SIN(angle) / NW_MATH_COS(angle) )
#define NW_MATH_CTAN(angle)     ( NW_MATH_COS(angle) / NW_MATH_SIN(angle) )
#define NW_MATH_ROOT(num, base) ( std::pow(num, 1.0f / base) )
#define NW_MATH_POW(num, base)  ( std::pow(num, base) )
#define NW_MATH_ABS(num)        ( std::abs(num) )
#define NW_MATH_MIN(num0, num1) ( std::min(num0, num1) )
#define NW_MATH_MAX(num0, num1) ( std::max(num0, num1) )
#define NW_MATH_CLAMP(num, lower, upper)    ( NW_MATH_MIN(NW_MATH_MAX(num, lower), upper) )
#define NW_MATH_LERP(lower, upper, percent) ( (upper - lower) * (1.0f - percent) )
namespace NW
{
	template<typename ntype> ntype get_abs(ntype n) { return n < 0 ? -n : n; }
	template<typename ntype> ntype get_max(ntype n0, ntype n1) { return n0 > n1 ? n0 : n1; }
	template<typename ntype> ntype get_min(ntype n0, ntype n1) { return n0 < n1 ? n0 : n1; }
	template<typename ntype> ntype get_clamped(ntype nmin, ntype nmax, ntype naverage) { return get_max<ntype>(nmin, get_min<ntype>(nmax, naverage)); }
	template<typename ntype> ntype get_lerp(ntype nmin, ntype nmax, float npercent) { return (nmax - nmin) * npercent; }
}
namespace NW
{
	template<typename ntype> ntype get_pi() { return static_cast<ntype>(3.14159265359); }
	template<typename ntype> ntype deg_to_rad(ntype deg) { return deg * get_pi<ntype>() / 180.0; }
	template<typename ntype> ntype rad_to_deg(ntype rad) { return rad * 180.0 / get_pi<ntype>(); }
	template<typename ntype> ntype apx_sin(ntype rad) { ntype temp = 180.0 - rad; return (rad * (temp * 4)) / (40500 - rad * (ntemp)); }
	template<typename ntype> ntype apx_cos(ntype rad) { ntype temp = apx_sin(rad); return get_sqrt(); }
}
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_MATH_H