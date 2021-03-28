#ifndef NWLIB_CORE_HPP
#define NWLIB_CORE_HPP
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

// --==<linkage>==--
#if (defined NW_WAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
#		define NW_DLL_EXPORT __declspec(dllexport)
#		define NW_DLL_IMPORT __declspec(dllexport)
#		define NW_API_ENTRY  __stdcall
#	endif	// WAPI_WIN
#else
#	error "undefined platform"
#endif	// NW_WAPI

#define NW_BUILD_LIB
#if (defined NW_BUILD_LIB)
#	define NW_API
#elif (defined NW_BUILD_EXE)
#	define NW_API
#elif (defined NW_BUILD_DLL)
#	define NW_API NW_DLL_EXPORT
#else
#	define NW_API NW_DLL_EXPORT
#endif	// NW_BUILD
// --==</linkage>==--

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
#if (defined NW_CAPI)
#	if (NW_CAPI & NW_CAPI_MVS)
#		ifndef _CRT_SECURE_NO_WARNINGS
#			pragma warning(disable : 4002)  // too many arguments for macro
#			pragma warning(disable : 4005)
#			pragma warning(disable : 4081)
#			pragma warning(disable : 4099)
#			pragma warning(disable : 4102)
#			pragma warning(disable : 4244)
#			pragma warning(disable : 4251)
#			pragma warning(disable : 4267)
#			pragma warning(disable : 4273)
#			pragma warning(disable : 4275)
#			pragma warning(disable : 4551)
#			pragma warning(disable : 4552)
#			pragma warning (disable: 4996)  // unsafe functions
#			define _CRT_SECURE_NO_WARNINGS
#		endif	// _CRT_SECURE_NO_WARNINGS
#	endif	// CAPI_MVS
#else
#	error "undefined compiler"
#endif	// NW_CAPI
// --==</warnings>==--

// --==<limits>==--
#define NW_MAX_PATH     1 << 8
#define NW_MAX_MEMORY   1 << 20
// --==</limits>==--

// --==<characters>==--
#if (defined NW_WAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
#		define NW_CHAR_EOL	'\r\n'
#		define NW_CHAR_DIR	'\\'
#		define NW_STR_EOL	"\r\n"
#		define NW_STR_DIR	"\\"
#	else
#		define NW_CHAR_EOL  '\n'
#		define NW_CHAR_DIR	'/'
#		define NW_STR_EOL	"\n"
#		define NW_STR_DIR	"/"
#		define __int8		char
#		define __int16		short
#		define __int32		int
#		define __int64		long int
#		define __int128		long long int
#	endif	// WAPI_WIN
#else
#	error "undefined platform"
#endif	// NW_WAPI

#define NW_STR_TXT(txt) #txt
#define NW_STR_DEFAULT  "default"
#define NW_STR_NAME     "native_world"
#define NW_STR_LOC      NW_STR_DIR "native_world"
// --==</characters>==--

#include "nwlib_pch.hpp"

#if (defined NW_WAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
#		define window_handle  HWND
#		define library_handle HMODULE
#		if (defined NW_GAPI)
#			if (NW_GAPI & NW_GAPI_OGL)
#				define device_handle   HDC
#				define context_handle  HGLRC
#				define GLbyte          unsigned char
#				define GLuint          unsigned int
#				define GLenum          unsigned int
#			endif	// GAPI_OGL
#			if (NW_GAPI & NW_GAPI_DX)
#				define device_handle  ID3D11Device*
#				define context_handle ID3D11DeviceContext*
#			endif	// GAPI_DX
#		else
#		error "undefined graphics"
#		endif	// NW_GAPI
#	endif	// WAPI_WIN
#else
#	error "undefined platform"
#endif	// NW_WAPI

#ifndef NW_DISABLE_NAMES
namespace NWLIB
{
	// numbers
	using v1b     = bool;
	using v1s8    = signed __int8;
	using v1u8    = unsigned __int8;
	using v1s16   = signed __int16;
	using v1u16   = unsigned __int16;
	using v1s32   = signed __int32;
	using v1u32   = unsigned __int32;
	using v1s64   = signed __int64;
	using v1u64   = unsigned __int64;
	using v1f32   = float;
	using v1f64   = double;
	using v1f128  = long double;
	using cv1b    = const v1b;
	using cv1s8   = const v1s8;
	using cv1u8   = const v1u8;
	using cv1s16  = const v1s16;
	using cv1u16  = const v1u16;
	using cv1s32  = const v1s32;
	using cv1u32  = const v1u32;
	using cv1s64  = const v1s64;
	using cv1u64  = const v1u64;
	using cv1f32  = const v1f32;
	using cv1f64  = const v1f64;
	using cv1f128 = const v1f128;
	using v1s     = v1s32;      // default signed integer
	using v1u     = v1u32;      // default unsigned integer
	using v1f     = v1f32;      // default float
	using cv1s     = const v1s; // default constant signed integer
	using cv1u     = const v1u; // default constant unsigned integer
	using cv1f     = const v1f; // default constant float
	// memory
	template<typename mt> using t_ptr = mt*;
	template<typename mt> using t_cptr = const mt*;
	using ptr      = t_ptr<void>;
	using cptr     = t_cptr<void>;
	using sbyte    = char;
	using ubyte    = unsigned char;
	using byte     = ubyte; // default byte type
	using size     = size_t;
	using csize    = const size;
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
#endif	// NW_DISABLE_NAMES

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

#endif	// NWLIB_CORE_HPP