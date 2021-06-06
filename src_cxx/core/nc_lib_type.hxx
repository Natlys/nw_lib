#ifndef NC_LIB_TYPE_HXX
#   define NC_LIB_TYPE_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* defines */
/** constants **/
/** functions **/
#   define NC_TYPE_CAST(val, type) ( (type)(val) )
#   define NC_TYPE_CAST_PTR(val)   ( (ptr_t)(val) )
#   define NC_TYPE_CAST_BIT(val)   ( (v1b_tc)(val) )
#   define NC_TYPE_CAST_V1U(val)   ( (v1u_tc)(val) )
#   define NC_TYPE_CAST_V1S(val)   ( (v1s_tc)(val) )
#   define NC_TYPE_CAST_V1F(val)   ( (v1f_tc)(val) )
#   define NC_TYPE_CAST_SIZE(val)  ( (size_tc)(val) )
/* data */
NC_API indx_t nc_code_type;
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_TYPE_HXX */