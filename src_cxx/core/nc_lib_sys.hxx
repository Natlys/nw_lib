#ifndef NC_LIB_SYSTEM_HXX
#   define NC_LIB_SYSTEM_HXX
#include "../nc_lib_core.hxx"
#   if (defined NC_API)
/* includes */
/* types */
/* library_system_type
 * description:
 * ->
*/
typedef struct nc_lib_sys_t nc_lib_sys_t;
/** getters **/
NC_API nc_lib_sys_t* nc_lib_sys_get();
/** setters **/
/** commands **/
NC_API v1bit_t nc_lib_sys_init();
NC_API v1bit_t nc_lib_sys_quit();
NC_API v1bit_t nc_lib_sys_work();
NC_API v1bit_t nc_lib_sys_mset(ptr_t* data, size_t isize, size_t osize);
#   endif  /* NC_API */
/* end_of_file */
#endif  /* NC_LIB_SYSTEM_HXX */