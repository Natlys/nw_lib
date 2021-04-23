#ifndef NW_CORE_MEM_H
#define NW_CORE_MEM_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
// definitions
// types
namespace NW
{
	using ptr_t             = void*;
	using ptr_tc      = const void*;
	typedef signed char     sbyte_t;
	typedef const sbyte_t  sbyte_tc;
	typedef unsigned char   ubyte_t;
	typedef const ubyte_t  ubyte_tc;
	typedef char             byte_t; // default byte type
	typedef const byte_t    byte_tc; // default constant byte type
	typedef size_t           size_t; // default byte size type
	typedef const size_t    size_tc; // default constant byte size type
}
#else
#	error "nw_lib_core.hpp must be included before this header!"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_MEM_H