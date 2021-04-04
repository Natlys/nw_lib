#ifndef NW_CORE_MEM_H
#define NW_CORE_MEM_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
// definitions
#define NW_MAX_MEMORY   1 << 20
// types
namespace NW
{
	using ptr              = void*;
	using cptr       = const void*;
	typedef char             sbyte;
	typedef unsigned char    ubyte;
	typedef ubyte             byte; // default byte type
	typedef const ubyte      cbyte; // default constant byte type
	typedef size_t            size; // default byte size type
	typedef const size       csize; // default constant byte size type
}
#else
#	error "nw_lib_core.hpp must be included before this header!"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_MEM_H