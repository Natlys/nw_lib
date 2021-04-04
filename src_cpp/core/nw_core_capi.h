#ifndef NW_CORE_CAPI_H
#define NW_CORE_CAPI_H

#if (defined NW_LIB_CORE_HPP & defined NW_CAPI)
// microsoft_visual_studio
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
#	error "nw_lib_core.hpp must be included before this header!"
#endif	// NW_LIB_CORE_HPP & NW_CAPI

#endif	// NW_CORE_CAPI_H