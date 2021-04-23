#ifndef NW_CORE_VALUE_H
#define NW_CORE_VALUE_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	typedef void              v1nil;
	typedef void*             v1ptr;
	typedef bool              v1bit;
	typedef signed __int8     v1s08;
	typedef unsigned __int8   v1u08;
	typedef signed __int16    v1s16;
	typedef unsigned __int16  v1u16;
	typedef signed __int32    v1s32;
	typedef unsigned __int32  v1u32;
	typedef signed __int64    v1s64;
	typedef unsigned __int64  v1u64;
	typedef float             v1f32;
	typedef double            v1f64;
	typedef long double      v1f128;
	typedef const v1ptr      v1cptr;
	typedef const v1bit      cv1bit;
	typedef const v1s08      cv1s08;
	typedef const v1u08      cv1u08;
	typedef const v1s16      cv1s16;
	typedef const v1u16      cv1u16;
	typedef const v1s32      cv1s32;
	typedef const v1u32      cv1u32;
	typedef const v1s64      cv1s64;
	typedef const v1u64      cv1u64;
	typedef const v1f32      cv1f32;
	typedef const v1f64      cv1f64;
	typedef const v1f128    cv1f128;
	typedef v1bit v1b;      // default boolean type
	typedef v1s32 v1s;      // default signed integer
	typedef v1u32 v1u;      // default unsigned integer
	typedef v1f32 v1f;      // default float
	typedef v1f32 v1n;      // default number
	typedef const v1b cv1b; // default constant boolean
	typedef const v1s cv1s; // default constant signed integer
	typedef const v1u cv1u; // default constant unsigned integer
	typedef const v1f cv1f; // default constant float
	typedef const v1n cv1n; // default constant number
	typedef unsigned int venum; // default enumeration type
	typedef const venum cvenum; // default enumeration type
}
#else
#	error "nw_lib_core.hpp must be included before this file"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_VALUE_H