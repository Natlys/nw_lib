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
#define NW_EMPTY                // just empty macro
#define NW_TO_STR(txt)          #txt
#define NW_NAME                 "native_world"
#define NW_DEFAULT_VAL          0
#define NW_DEFAULT_STR          "default"
#define NW_CAST_SINT(num)       ( static_cast<v1s>(num) )
#define NW_CAST_UINT(num)       ( static_cast<v1u>(num) )
#define NW_CAST_FLOAT(num)      ( static_cast<v1f>(num) )
#define NW_MATH_PI              ( NW_CAST_FLOAT(3.14159265359) )
#define NW_MATH_DEGREE(angle)   ( NW_CAST_FLOAT(angle) / NW_MATH_PI * NW_CAST_FLOAT(180.0))
#define NW_MATH_RADIAN(angle)   ( NW_CAST_FLOAT(angle) * NW_MATH_PI / NW_CAST_FLOAT(180.0))
#define NW_MATH_ANGLE(angle)    ( NW_MATH_RADIAN(angle) )
#define NW_MATH_COS(angle)      ( std::cosf(NW_MATH_ANGLE(angle)) )
#define NW_MATH_SIN(angle)      ( std::sinf(NW_MATH_ANGLE(angle)) )
#define NW_MATH_TANG(angle)     ( NW_MATH_SIN(angle) / NW_MATH_COS(angle) )
#define NW_MATH_CTAN(angle)     ( NW_MATH_COS(angle) / NW_MATH_SIN(angle) )
#define NW_MATH_ROOT(num, base) ( std::pow(num, 1.0f / base) )
#define NW_MATH_POW(num, base)  ( std::pow(num, base) )
#define NW_MATH_MIN(num0, num1) ( std::min(num0, num1) )
#define NW_MATH_MAX(num0, num1) ( std::max(num0, num1) )
#define NW_MATH_CLAMP(num, lower, upper) ( NW_MATH_MIN(NW_MATH_MAX(num, lower), upper) )
#define NW_MATH_LERP(lower, upper, percent) ( (upper - lower) * (1.0f - percent) )
// --==</helpers>==--

// --==<support_macroses>==--
#define NW_XY_TO_X(x, y, w)         ( (static_cast<size>(y) * static_cast<size>(w)) + static_cast<size>(x) )
#define NW_ALIGN(data, align)       ( (static_cast<size>(data) + (static_cast<size>(align) - 1)) & ~(static_cast<size>(align) - 1) )

#if (defined NW_DEBUG)
#	define NW_CHECK_TYPE_BASE(base, derived)  (std::is_base_of<base, derived>::value)
#	define NW_BREAK()                         (__debugbreak())
#	define NW_ASSERT(expr, comment)           \
	if (expr == false) { std::cout << comment; NW_BREAK(); }
#	define NW_ERR(comment)                    NW_ASSERT(0, comment);
#else
#	define NW_CHECK_TYPE_BASE() 1
#	define NW_BREAK()  NW_EMPTY
#	define NW_ASSERT() NW_EMPTY
#	define NW_ERR()    NW_EMPTY
#endif	// NW_DEBUG
// --==</support_macroses>==--

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
#		define NW_API    NW_EMPTY
#	elif (NW_BUILD & NW_BUILD_LIB)
#		define NW_API    NW_EMPTY
#	elif (NW_BUILD & NW_BUILD_DLL)
#		define NW_API    NW_DLL_EXPORT
#	else
#		define NW_API    NW_DLL_IMPORT
#	endif
#endif	// NW_BUILD
// --==</linkage>==--

// --==<support_functions>==--
namespace NW
{
	template<typename in_type, typename out_type>
	NW_API out_type convert();
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input);
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input, size count);
}
// --==</support_functions>==--

#endif	// NW_LIB_CORE_HPP