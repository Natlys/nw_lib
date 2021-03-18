#ifndef NWL_OPERATIONAL_SYSTEM_HPP
#define NWL_OPERATIONAL_SYSTEM_HPP

#if (defined NW_PLATFORM_WINDOWS)
#	define NOMINMAX
#	define WIN32_LEAN_AND_MEAN 1
#	include <windows.h>
#	ifndef APIENTRY
#		define APIENTRY
#	endif	// APIENTRY
#	ifndef APIENTRYP
#		define APIENTRYP APIENTRY *
#	endif	// APIENTRYP
#	include <commdlg.h>
#	include <tchar.h>
#	if (!(defined NOGDI))
#		pragma comment(lib, "winmm.lib")
#		pragma comment(lib, "gdi32")   // link with gdi32.lib for GetDeviceCaps()
#	endif	// MSC_VER
#endif	// NW_PLATFORM_WINDOWS

#endif	// NWL_OPERATIONAL_SYSTEM_HPP