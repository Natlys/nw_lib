#ifndef NWL_CORE_HPP
#define NWL_CORE_HPP
// --==<configuration>==--
#define NW_BUILD_DLL
#if (defined NW_BUILD_LIB)
#	define NW_API
#elif (defined NW_BUILD_EXE)
#	define NW_API
#elif (defined NW_BUILD_DLL)
#	define NW_API __declspec(dllexport)
#elif (1)
#	define NW_API __declspec(dllimport)
#endif	// NW_BUILD

#define NW_LAST_CLASS __declspec(novtable)

#define NW_GAPI_OGL		1 << 1
#define NW_GAPI_DX		1 << 2
#define NW_GAPI			NW_GAPI_OGL

#define NW_WAPI_WIN		1 << 1
#define NW_WAPI			NW_WAPI_WIN
// --==</configuration>==--

// --==<suport>==--
#if defined(_MSC_VER)
#	if (!(defined _CRT_SECURE_NO_WARNINGS) && false)
#		pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#		define _CRT_SECURE_NO_WARNINGS
#	endif
#endif	// microsoft visual studio version
#if (defined _WIN32)
#	define NW_CHAR_EOL	'\r\n'
#	define NW_CHAR_DIR	'\\'
#	define NW_STR_EOL	"\r\n"
#	define NW_STR_DIR	"\\"
#else
#	define NW_CHAR_EOL  '\n'
#	define NW_CHAR_DIR	'/'
#	define NW_STR_EOL	"\n"
#	define NW_STR_DIR	"/"
#endif
#define NW_STR_TXT(txt)	#txt	
#define NW_STR_DEFAULT	"default"
#define NW_STR_NAME		"native_world"
#define NW_STR_LOC		NW_STR_DIR"native_world"

#define NW_MAX_GLOBAL_MEMORY	1 << 20
// --==</support>==--

// --==<pragmas>==--
#pragma warning(disable : 4005)
#pragma warning(disable : 4081)
#pragma warning(disable : 4099)
#pragma warning(disable : 4102)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4273)
#pragma warning(disable : 4275)
#pragma warning(disable : 4551)
#pragma warning(disable : 4552)
#pragma warning(disable : 4996)
#ifdef _MSC_VER
#endif
// --==</pragmas>==--

#include "nwl_pch.hpp"

#if (defined NW_WAPI && defined NW_GAPI)
#	if (NW_WAPI & NW_WAPI_WIN)
using window_handle = HWND;
using library_handle = HMODULE;
#		if (NW_GAPI & NW_GAPI_OGL)
using device_handle = HDC;
using context_handle = HGLRC;
using GLuint = unsigned int;
using GLbyte = unsigned char;
#		endif
#		if (NW_GAPI & NW_GAPI_DX)
struct ID3D11Device;
struct ID3D11DeviceContext;
using device_handle = ID3D11Device*;
using context_handle = ID3D11DeviceContext*;
#		endif	// NW_GAPI
#	endif
#endif	// NW_WAPI && NW_GAPI

namespace NW
{
	using si8 = signed __int8;
	using si16 = signed __int16;
	using si32 = signed __int32;
	using si64 = signed __int64;
	using ui8 = unsigned __int8;
	using ui16 = unsigned __int16;
	using ui32 = unsigned __int32;
	using ui64 = unsigned long int;
	using f32 = float;
	using f64 = double;
	using f128 = long double;
	using ptr = void*;
	using cptr = const void*;
	using bit = bool;
	using sbyte = char;
	using ubyte = unsigned char;
	using size = size_t;
	using schar = char;
	using uchar = unsigned char;
	using wchar = wchar_t;
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
#	define NW_CHECK_TYPE_BASE(base, derived)
#	define NW_BREAK()
#	define NW_ASSERT(expt, comment)
#	define NW_ERR(comment)
#endif	// NW_DEBUG

namespace NW
{
	template<class stype>
	class NW_API a_singleton;
	struct NW_API a_event;
	struct NW_API wnd_event;
	struct NW_API ms_event;
	struct NW_API kbd_event;
}
#endif	// NWL_CORE_HPP