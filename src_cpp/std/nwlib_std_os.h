#ifndef NWLIB_STD_OS_H
#define NWLIB_STD_OS_H
//#include "nwlib_core.hpp"
#if (NW_WAPI & NW_WAPI_WIN) || (defined NW_PLATFORM_WINDOWS)
#	define NOMINMAX
#	define WIN32_LEAN_AND_MEAN 1
#	include <windows.h>
#	ifndef APIENTRY
#		define APIENTRY
#	endif	// APIENTRY
#	ifndef APIENTRYP
#		define APIENTRYP APIENTRY*
#	endif	// APIENTRYP
#	include <commdlg.h>
#	include <tchar.h>
#	if (NW_CAPI & NW_CAPI_MVS && !(defined NOGDI))
#		pragma comment(lib, "winmm.lib")
#		pragma comment(lib, "gdi32")   // link with gdi32.lib for GetDeviceCaps()
#	endif	// NW_CAPI
#endif
#endif	// NWLIB_STD_OS_H