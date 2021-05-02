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
#define NW_BUILD_EXE    1 << 1
#define NW_BUILD_LIB    1 << 2
#define NW_BUILD_DLL    1 << 3
#define NW_BUILD        NW_BUILD_LIB
// --==</configuration>==--

// --==<helpers>==--
#define NW_NAME          native_world
#define NW_NAME_STR      "native_world"
#define NW_NAMESPACE     NW
#define NW_NAMESPACE_STR "NW"
#define NW_NULL   NULL
#define NW_ZERO   0
#define NW_UNIT   1
#define NW_FALSE  0
#define NW_TRUE   1
#define NW_DEFAULT       // just empty macro
#define NW_DEFAULT_VAL   0
#define NW_DEFAULT_PTR   nullptr
#define NW_DEFAULT_STR   "default"
#define NW_CAST_SINT(num)     ( static_cast<v1s>(num) )
#define NW_CAST_UINT(num)     ( static_cast<v1u>(num) )
#define NW_CAST_FLOAT(num)    ( static_cast<v1f>(num) )
#define NW_CAST_SIZE(num)     ( static_cast<size_t>(num) )
#define NW_XY_TO_X(x, y, w)   ( (NW_CAST_SIZE(y) * NW_CAST_SIZE(w)) + NW_CAST_SIZE(x) )
#define NW_XY_SIZE(x, y)      ( NW_CAST_SIZE(x) * NW_CAST_SIZE(y) )
#define NW_ALIGN(data, alig)  ( (NW_CAST_SIZE(data) + (NW_CAST_SIZE(alig) - 1)) & ~(NW_CAST_SIZE(alig) - 1) )

#if (defined NW_DEBUG)
#	define NW_BREAK __debugbreak();
#	define NW_ERROR(mesg, error_action) \
	std::cout << mesg << NW_STR_EOL; NW_BREAK; error_action;
#	define NW_CHECK(expr, mesg, error_action) \
	if ((expr) == NW_FALSE) { NW_ERROR(mesg, error_action); }
#	define NW_CHECK_TYPE_BASE(tname, tbase, mesg) \
		static_assert(std::is_base_of<tbase, tname>(), mesg);
#else
#	define NW_BREAK() NW_DEFAULT
#	define NW_ERROR() NW_DEFAULT
#	define NW_CHECK() NW_DEFAULT
#	define NW_CHECK_TYPE_BASE() NW_DEFAULT
#endif	// NW_DEBUG
// --==</helpers>==--

// --==<core_files>==--
#include "nw_lib_pch.hpp"
#include "core/nw_core_wapi.h"
#include "core/nw_core_gapi.h"
#include "core/nw_core_capi.h"
#include "core/nw_core_val.h"
#include "core/nw_core_num.h"
#include "core/nw_core_mem.h"
#include "core/nw_core_str.h"
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