#ifndef NWL_CORE_HPP
#define NWL_CORE_HPP
// --==<building>==--
#define NW_BUILD_LIB
#if (defined NW_BUILD_LIB)
#	define NW_API
#elif (defined NW_BUILD_EXE)
#	define NW_API
#elif (defined NW_BUILD_DLL)
#	define NW_API __declspec(dllexport)
#else
#	define NW_API __declspec(dllimport)
#endif	// NW_BUILD
// --==</building>==--

// --==<core_libraries>==--
// graphics api
#define NW_GAPI_OGL		1 << 1
#define NW_GAPI_DX		1 << 2
#define NW_GAPI			NW_GAPI_DX
// window api
#define NW_WAPI_WIN		1 << 1
#define NW_WAPI			NW_WAPI_WIN

#define NW_CAPI_MVS     1 << 1
#define NW_CAPI_GNU     1 << 2
#define NW_CAPI         NW_CAPI_MVS
// --==</core_libraries>==--

// --==<helpers>==--
#define NW_EMPTY  // just empty macro
#define NW_LAST_CLASS __declspec(novtable)
#define NW_DEF_OPER_BIT(btype) \
	inline ui32 operator|(btype enm_0, btype enm_1)  { return static_cast<ui32>(enm_0) | static_cast<ui32>(enm_1); } \
	inline ui32 operator&(btype enm_0, btype enm_1)  { return static_cast<ui32>(enm_0) & static_cast<ui32>(enm_1); } \
	inline ui32 operator<<(btype enm_0, ui32 lshift) { return static_cast<ui32>(enm_0) << lshift; } \
	inline ui32 operator>>(btype enm_0, ui32 rshift) { return static_cast<ui32>(enm_0) >> rshift; }
// --==</helpers>==--

// --==<warnings>==--
#ifndef NW_CAPI
#error "undefined compiler"
#elif (NW_CAPI & NW_CAPI_MVS)
#	ifndef _CRT_SECURE_NO_WARNINGS
#		pragma warning(disable : 4002)  // too many arguments for macro
#		pragma warning(disable : 4005)
#		pragma warning(disable : 4081)
#		pragma warning(disable : 4099)
#		pragma warning(disable : 4102)
#		pragma warning(disable : 4244)
#		pragma warning(disable : 4251)
#		pragma warning(disable : 4267)
#		pragma warning(disable : 4273)
#		pragma warning(disable : 4275)
#		pragma warning(disable : 4551)
#		pragma warning(disable : 4552)
#		pragma warning (disable: 4996)  // unsafe functions
#		define _CRT_SECURE_NO_WARNINGS
#	endif	// _CRT_SECURE_NO_WARNINGS
#endif	// NW_CAPI
// --==</warnings>==--

// --==<limits>==--
#define NW_MAX_PATH     1 << 8
#define NW_MAX_MEMORY   1 << 20
// --==</limits>==--

// --==<characters>==--
#ifndef NW_WAPI
#error "undefined platform"
#elif (NW_WAPI & NW_WAPI_WIN)
#	define NW_CHAR_EOL	'\r\n'
#	define NW_CHAR_DIR	'\\'
#	define NW_STR_EOL	"\r\n"
#	define NW_STR_DIR	"\\"
#else
#	define NW_CHAR_EOL  '\n'
#	define NW_CHAR_DIR	'/'
#	define NW_STR_EOL	"\n"
#	define NW_STR_DIR	"/"
#	define __int8		char
#	define __int16		short
#	define __int32		int
#	define __int64		long int
#	define __int128		long long int
#endif	// NW_WAPI

#define NW_STR_TXT(txt) #txt
#define NW_STR_DEFAULT  "default"
#define NW_STR_NAME     "native_world"
#define NW_STR_LOC      NW_STR_DIR "native_world"
// --==</characters>==--

#include "nwl_pch.hpp"

#ifndef NW_WAPI
#error "undefined platform"
#elif (NW_WAPI & NW_WAPI_WIN)
using window_handle = HWND;
using library_handle = HMODULE;
#	ifndef NW_GAPI
#	elif (NW_GAPI & NW_GAPI_OGL)
using device_handle = HDC;
using context_handle = HGLRC;
using GLuint = unsigned int;
using GLbyte = unsigned char;
#	elif (NW_GAPI & NW_GAPI_DX)
struct ID3D11Device;
struct ID3D11DeviceContext;
using device_handle = ID3D11Device*;
using context_handle = ID3D11DeviceContext*;
#	endif	// NW_GAPI
#endif

namespace NW
{
	// numbers
	using v1si8    = signed __int8;
	using v1ui8    = unsigned __int8;
	using v1si16   = signed __int16;
	using v1ui16   = unsigned __int16;
	using v1si32   = signed __int32;
	using v1ui32   = unsigned __int32;
	using v1si64   = signed __int64;
	using v1ui64   = unsigned __int64;
	using v1f32    = float;
	using v1f64    = double;
	using v1f128   = long double;
	using v1si     = signed int;   // default signed integer
	using v1ui     = unsigned int; // default unsigned integer
	using v1f      = float;        // default float
	// memory
	template<typename mt> using t_ptr = mt*;
	template<typename mt> using t_cptr = const mt*;
	using ptr      = t_ptr<void>;
	using cptr     = t_cptr<void>;
	using bit      = bool;
	using sbyte    = char;
	using ubyte    = unsigned char;
	using byte     = ubyte; // default byte type
	using size     = size_t;
	// characters
	using schar    = char;
	using uchar    = unsigned char;
	using wchar    = wchar_t;
	using sstr     = char*;
	using wstr     = wchar_t*;
	using csstr    = const char*;
	using cwstr    = const wchar_t*;
	using str      = sstr;  // default string type
	using cstr     = csstr; // default string type
}

// --==<support_macroses>==--
#define NW_XY_TO_X(x, y, w) ( (static_cast<size>(y) * static_cast<size>(w)) + static_cast<size>(x) )
#define NW_ALIGN_FORWARD(data, alignment) ( (static_cast<size>(data) + (static_cast<size>(alignment) - 1)) & ~(static_cast<size>(alignment) - 1) )

#if (defined NW_DEBUG)
#	define NW_CHECK_TYPE_BASE(base, derived)	std::is_base_of<base, derived>::value
#	define NW_BREAK() (__debugbreak())
#	define NW_ASSERT(expr, comment) if (expr == false) { std::cout << comment; NW_BREAK(); }
#	define NW_ERR(comment) NW_ASSERT(false, comment);
// --==</support_macroses>==--
#else
#	define NW_CHECK_TYPE_BASE() 1
#	define NW_BREAK()  NW_EMPTY
#	define NW_ASSERT() NW_EMPTY
#	define NW_ERR()    NW_EMPTY
#endif	// NW_DEBUG

#endif	// NWL_CORE_HPP