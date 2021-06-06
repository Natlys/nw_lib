#ifndef NC_LIB_CORE_HXX
#   define NC_LIB_CORE_HXX
/* config */
/** building **/
#   if (defined NC_BUILD)
#       undef NC_BUILD
#   endif   /* NC_BUILD */
#   define NC_BUILD_EXE ( 1 << 0 )
#   define NC_BUILD_LIB ( 1 << 1 )
#   define NC_BUILD_DLL ( 1 << 2 )
#   define NC_BUILD     NC_BUILD_LIB
/** graphics api **/
#   define NC_GAPI_OGL  ( 1 << 0 )
#   define NC_GAPI_D3D  ( 1 << 1 )
#   define NC_GAPI      NC_GAPI_OGL
/** window api **/
#   define NC_WAPI_WIN  ( 1 << 0 )
#   define NC_WAPI      NC_WAPI_WIN
/** compiler api **/
#   define NC_CAPI_MVS  ( 1 << 0 )
#   define NC_CAPI_GNU  ( 1 << 1 )
#   define NC_CAPI      NC_CAPI_GNU
/* native api */
/* linkage */
#   if (!(defined(NC_BUILD)))
#       error "NC_BUILD is not defined!"
#   elif (NC_BUILD & NC_BUILD_EXE)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_LIB)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_DLL)
#       define NC_API NC_DLL_EXPORT
#   else
#       define NC_API NC_DLL_IMPORT
#   endif	/* NC_BUILD */
/** language **/
#   define NC_LANG_LANG_CPP ( 1 << 0 )
#   define NC_LANG_LANG_CXX ( 1 << 1 )
#   define NC_LANG_LANG_LUA ( 1 << 2 )
#   define NC_LANG          NC_LANG_CXX
/* includes */
#   include "nc_lib_pch.hxx"
/** api **/
#   include "core/nc_lib_capi.hxx"
#   include "core/nc_lib_wapi.hxx"
#   include "core/nc_lib_gapi.hxx"
/** value **/
#   include "core/nc_lib_val.hxx"
#   include "core/nc_lib_num.hxx"
#   include "core/nc_lib_str.hxx"
/** main **/
#   include "core/nc_lib_dbg.hxx"
#   include "core/nc_lib_mem.hxx"
#   include "core/nc_lib_iop.hxx"
#   include "core/nc_lib_type.hxx"
/** system **/
#   include "core/nc_lib_ref.hxx"
#   include "core/nc_lib_cmd.hxx"
#   include "core/nc_lib_sys.hxx"
/* defines */
/** constants **/
/*** general ***/
#   define NC_VOID /* just empty macro */
/*** names ***/
#   define NC_NAME_FULL nati_code
#   define NC_NAME_VERS ver_7_0
#   define NC_NAME_CORE NC
/*** strings ***/
#   define NC_DIRL NC_STR_DIRL
#   define NC_ENDL NC_STR_ENDL
#   define NC_SEPL NC_STR_SEPL
#   define NC_SIGL NC_STR_SIGL
#   define NC_TABL NC_STR_TABL
/** functions **/
/*** utils ***/
#   define NC_SWAP NC_VAL_SWAP
/*** typedefs ***/
#   define NC_CAST(val, type) NC_TYPE_CAST(val, type)
#   define NC_CAST_PTR(val)   NC_TYPE_CAST_PTR(val)
#   define NC_CAST_PTR(val)   NC_TYPE_CAST_BIT(val)
#   define NC_CAST_V1U(val)   NC_TYPE_CAST_V1U(val)
#   define NC_CAST_V1S(val)   NC_TYPE_CAST_V1S(val)
#   define NC_CAST_V1F(val)   NC_TYPE_CAST_V1F(val)
#   define NC_CAST_SIZE(val)  NC_TYPE_CAST_SIZE(val)
/*** numbers ***/
#   define NC_MIN(num0, num1)   NC_NUM_MIN(num0, num1)
#	define NC_MAX(num0, num1)   NC_NUM_MAX(num0, num1)
#   define NC_ALIG(size, alig)  NC_NUM_ALIG(size, alig)
/* typedefs */
/* end_of_file */
#endif	/* NC_LIB_CORE_HXX */