#ifndef NC_LIB_SYSTEM_HXX
#   define NC_LIB_SYSTEM_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* defines */
/* typedefs */
/* system_init_function
 * description:
 * -> this is an initializer function for anything;
 * -> returns {NC_TRUTH if everything is okay} or {NC_FALSE if there is an error};
*/
typedef v1bit_t (NC_API_CALL*nc_sys_init_f) (nil_t);
/* system_quit_function
 * description:
 * -> this is a terminate function for anything;
 * -> returns {NC_TRUTH if everything is okay} or {NC_FALSE if there is an error};
*/
typedef v1bit_t (NC_API_CALL*nc_sys_quit_f) (nil_t);
/* system_work_function
 * description:
 * -> this is an update function for anything;
 * -> takes in a pointer as user data;
 * -> returns {NC_TRUTH if everything is okay} or {NC_FALSE if there is an error};
*/
typedef v1bit_t (NC_API_CALL*nc_sys_work_f) (nil_t);
/* system_memory_set_function
 * description:
 * -> takes a pointer to the data pointer to take and copy the memory;
 * -> takes an iput size to free the memory;
 * -> takes an oput size to take the memory;
 * -> returns {NC_TRUTH if everything is okay} or {NC_FALSE if there is an error};
 * -> to take memory: data != 0; isize == 0; osize != 0;
 * -> to free memory: data != 0; isize != 0; osize == 0;
 * -> to edit memory: data != 0; isize != 0; osize != 0;
*/
typedef v1bit_t(NC_API_CALL*nc_sys_mset_f)(nil_t** data, size_t isize, size_t osize);
/* library_system_type */
typedef struct nc_lib_sys_t nc_lib_sys_t;
/** command **/
NC_API_CALL NC_API v1bit_t nc_lib_sys_init(nil_t);
NC_API_CALL NC_API v1bit_t nc_lib_sys_quit(nil_t);
NC_API_CALL NC_API v1bit_t nc_lib_sys_work(nil_t);
NC_API_CALL NC_API v1bit_t nc_lib_sys_mset(nil_t** data, size_t isize, size_t osize);
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_SYSTEM_HXX */