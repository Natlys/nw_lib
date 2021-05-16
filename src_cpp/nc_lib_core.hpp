#ifndef NC_LIB_CORE_HPP
#   define NC_LIB_CORE_HPP
// config //
// // building // //
#   if (defined NC_BUILD)
#       undef NC_BUILD
#   endif   // NC_BUILD //
#   define NC_BUILD NC_BUILD_LIB
// // standard // //
#   if !(defined NC_REF)
#       define NC_REF_STD 1 << 0
#       define NC_REF_OWN 1 << 1
#       define NC_REF     NC_REF_OWN
#   endif   // NC_REF //
#   if !(defined NC_UTIL)
#       define NC_UTIL_STD 1 << 0
#       define NC_UTIL_OWN 1 << 1
#       define NC_UTIL     NC_UTIL_STD
#   endif   // NC_UTIL //
#   if !(defined NC_FUNC)
#       define NC_FUNC_STD 1 << 0
#       define NC_FUNC_OWN 1 << 1
#       define NC_FUNC     NC_FUNC_STD
#   endif   // NC_FLOW //
#   if !(defined NC_FLOW)
#       define NC_FLOW_STD 1 << 0
#       define NC_FLOW_OWN 1 << 1
#       define NC_FLOW     NC_FLOW_STD
#   endif   // NC_FLOW //
// // containers // //
#   if !(defined NC_LIST1)
#       define NC_LIST1_STD 1 << 0
#       define NC_LIST1_OWN 1 << 1
#       define NC_LIST1     NC_LIST1_OWN
#   endif   // NC_LIST1 //
#   if !(defined NC_LIST2)
#       define NC_LIST2_STD 1 << 0
#       define NC_LIST2_OWN 1 << 1
#       define NC_LIST2     NC_LIST2_STD
#   endif   // NC_LIST2 //
#   if !(defined NC_ARRAY)
#       define NC_ARRAY_STD 1 << 0
#       define NC_ARRAY_OWN 1 << 1
#       define NC_ARRAY     NC_ARRAY_STD
#   endif   // NC_ARRAY //
#   if !(defined NC_STACK)
#       define NC_STACK_STD 1 << 0
#       define NC_STACK_OWN 1 << 1
#       define NC_STACK     NC_STACK_STD
#   endif   // NC_STACK //
#   if !(defined NC_TABLE)
#       define NC_TABLE_STD 1 << 0
#       define NC_TABLE_OWN 1 << 1
#       define NC_TABLE     NC_TABLE_STD
#   endif   // NC_TABLE //
// includes //
#include "nc_lib_pch.hpp"
// linkage //
// // remove old NC_API // //
#   if (defined NC_API)
#       undef NC_API
#   endif   // NC_API //
// // remake new NC_API // //
#   if !(defined NC_BUILD)
#   elif (NC_BUILD & NC_BUILD_EXE)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_LIB)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_DLL)
#       define NC_API NC_DLL_EXPORT
#   else
#       define NC_API NC_DLL_IMPORT
#   endif	// NC_BUILD //
// end_of_file //
#endif	// NC_LIB_CORE_HPP //