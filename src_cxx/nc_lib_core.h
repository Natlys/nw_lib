#ifndef NC_LIB_CORE_H
#   define NC_LIB_CORE_H
// config //
// // building // //
#   if (defined NC_BUILD)
#       undef NC_BUILD
#   endif   // NC_BUILD //
#   define NC_BUILD NC_BUILD_LIB
// includes //
#   include "nc_lib_pch.h"
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
#endif	// NC_LIB_CORE_H //