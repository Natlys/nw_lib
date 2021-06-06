#ifndef NC_LIB_REFERENCE_HXX
#   define NC_LIB_REFERENCE_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
/* defines */
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* typedefs */
/* reference_type
 * description:
 * -> data pointer for a buffer of bytes;
 * -> size number for keeping the data size in bytes;
 * -> type number for type identification;
 * -> numb number for data reference counting;
*/
typedef struct nc_ref_t {
    data_t data;
    size_t size;
    size_t type;
    size_t numb;
} nc_ref_t;
/** command **/
#       define nc_ref_init(ref) ({           \
            NC_MEM_TAKE(ref.data, ref.size); \
})
#       define nc_ref_quit(ref) ({           \
            NC_MEM_FREE(ref.data, ref.size); \
})
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_REFERENCE_HXX */