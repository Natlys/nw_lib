#ifndef NW_CORE_VALUE_H
#define NW_CORE_VALUE_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
#include "nw_core_mem.h"
namespace NW
{
	typedef bool                v1b;
	typedef signed __int8      v1s8;
	typedef unsigned __int8    v1u8;
	typedef signed __int16    v1s16;
	typedef unsigned __int16  v1u16;
	typedef signed __int32    v1s32;
	typedef unsigned __int32  v1u32;
	typedef signed __int64    v1s64;
	typedef unsigned __int64  v1u64;
	typedef float             v1f32;
	typedef double            v1f64;
	typedef long double      v1f128;
	typedef const   v1b        cv1b;
	typedef const  v1s8       cv1s8;
	typedef const  v1u8       cv1u8;
	typedef const v1s16      cv1s16;
	typedef const v1u16      cv1u16;
	typedef const v1s32      cv1s32;
	typedef const v1u32      cv1u32;
	typedef const v1s64      cv1s64;
	typedef const v1u64      cv1u64;
	typedef const v1f32      cv1f32;
	typedef const v1f64      cv1f64;
	typedef const v1f128    cv1f128;
	typedef v1s32 v1s;      // default signed integer
	typedef v1u32 v1u;      // default unsigned integer
	typedef v1f32 v1f;      // default float
	typedef const v1s cv1s; // default constant signed integer
	typedef const v1u cv1u; // default constant unsigned integer
	typedef const v1f cv1f; // default constant float
}
#else
#	error "nw_lib_core.hpp must be included before this file"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_VALUE_H