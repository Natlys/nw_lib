#ifndef NW_LIB_CORE_HPP
#define NW_LIB_CORE_HPP

// --==<configuration>==--
// graphics api
#define NW_GAPI_OGL		1 << 1
#define NW_GAPI_D3D		1 << 2
#define NW_GAPI			NW_GAPI_OGL
// window api
#define NW_WAPI_WIN		1 << 1
#define NW_WAPI			NW_WAPI_WIN
// compiler api
#define NW_CAPI_MVS     1 << 1
#define NW_CAPI_GNU     1 << 2
#define NW_CAPI         NW_CAPI_MVS
// build type
#define NW_BUILD_EXE      1 << 1
#define NW_BUILD_LIB      1 << 2
#define NW_BUILD_DLL      1 << 3
#define NW_BUILD          NW_BUILD_LIB
// --==</configuration>==--

// --==<helpers>==--
#define NW_NAME    "native_world"
#define NW_NULL    NULL
#define NW_ZERO    0
#define NW_UNIT    1
#define NW_FALSE   0
#define NW_TRUE    1
#define NW_DEFAULT              // just empty macro
#define NW_DEFAULT_VAL   0
#define NW_DEFAULT_STR   "default"
#define NW_CAST_SINT(num)       ( static_cast<v1s>(num) )
#define NW_CAST_UINT(num)       ( static_cast<v1u>(num) )
#define NW_CAST_FLOAT(num)      ( static_cast<v1f>(num) )
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
#define NW_MATH_MIN(num0, num1) ( std::min(num0, num1) )
#define NW_MATH_MAX(num0, num1) ( std::max(num0, num1) )
#define NW_MATH_CLAMP(num, lower, upper)    ( NW_MATH_MIN(NW_MATH_MAX(num, lower), upper) )
#define NW_MATH_LERP(lower, upper, percent) ( (upper - lower) * (1.0f - percent) )
#define NW_XY_TO_X(x, y, w)      ( (static_cast<size>(y) * static_cast<size>(w)) + static_cast<size>(x) )
#define NW_ALIGN(data, align)    ( (static_cast<size>(data) + (static_cast<size>(align) - 1)) & ~(static_cast<size>(align) - 1) )

#if (defined NW_DEBUG)
#	define NW_BREAK __debugbreak();
#	define NW_ERROR(mesg) \
	std::cout << mesg << NW_STR_EOL; NW_BREAK;
#	define NW_CHECK(expr, mesg) \
	if ((expr) == NW_FALSE) { NW_ERROR(mesg); }
#	define NW_CHECK_TYPE_BASE(type, base) \
//	NW_CHECK( (std::is_base_of<base, type> ), "invalid base type")

#else
#	define NW_BREAK() NW_DEFAULT
#	define NW_ERROR() NW_DEFAULT
#	define NW_CHECK() NW_DEFAULT
#	define NW_CHECK_TYPE_BASE() NW_DEFAULT
#endif	// NW_DEBUG
// --==</helpers>==--

// --==<core_files>==--
#include "nw_lib_pch.hpp"
// configurations
#include "core/nw_core_wapi.h"
#include "core/nw_core_gapi.h"
#include "core/nw_core_capi.h"
// types
#include "core/nw_core_val.h"
#include "core/nw_core_vec.h"
#include "core/nw_core_mtx.h"
#include "core/nw_core_str.h"
#include "core/nw_core_mem.h"
// operations
#include "core/nw_core_math.h"
// --==</core_files>==--

// --==<linkage>==--
#if (defined NW_BUILD)
#	if (NW_BUILD & NW_BUILD_EXE)
#		define NW_API    NW_DEFAULT
#	elif (NW_BUILD & NW_BUILD_LIB)
#		define NW_API    NW_DEFAULT
#	elif (NW_BUILD & NW_BUILD_DLL)
#		define NW_API    NW_DLL_EXPORT
#	else
#		define NW_API    NW_DLL_IMPORT
#	endif
#endif	// NW_BUILD
// --==</linkage>==--

#endif	// NW_LIB_CORE_HPP