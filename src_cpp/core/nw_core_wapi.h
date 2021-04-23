#ifndef NW_CORE_WAPI_H
#define NW_CORE_WAPI_H

#if (defined NW_LIB_CORE_HPP & defined NW_WAPI)
// windows platform
#	if (NW_WAPI & NW_WAPI_WIN)
// // configs
#		define NOMINMAX
#		define WIN32_LEAN_AND_MEAN 1
// // includes
#		include <windows.h>
#		include <commdlg.h>
#		include <tchar.h>
// // support
#		define NW_DLL_EXPORT    __declspec(dllexport)
#		define NW_DLL_IMPORT    __declspec(dllexport)
#		define NW_API_ENTRY     __stdcall
#		define NW_API_ENTRYP    NW_API_ENTRY*
// // types
#		define window_handle       HWND
#		define library_handle      HMODULE
#		define wapi_device_handle  HDC
#		define wapi_context_handle HGLRC
// // constants
#			define NW_NULL       NULL
// // strings
#		define NW_CHAR_EOL	    '\r\n'
#		define NW_CHAR_DIR	    '\\'
#		define NW_STR_EOL	    "\r\n"
#		define NW_STR_DIR	    "\\"
#		define NW_MAX_PATH      MAX_PATH
#		if (NW_CAPI & NW_CAPI_MVS && !(defined NOGDI))
#			pragma comment(lib, "winmm.lib")
#			pragma comment(lib, "gdi32")   // link with gdi32.lib for GetDeviceCaps()
#		endif	// NW_CAPI
#	endif	// WAPI_WIN
#else
#	error "nw_lib_core.hpp must be included before this header!"
#endif	// NW_LIB_CORE_HPP & NW_WAPI

#endif	// NW_CORE_WAPI_H