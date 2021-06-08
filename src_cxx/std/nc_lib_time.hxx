#ifndef NC_LIB_TIME_HXX
#	define NC_LIB_TIME_HXX
#	include "../nc_lib_core.hxx"
#	if (defined(NC_API))
/* includes */
/* defines */
#       if (NC_LANG & NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
/* typedefs */
/* time_type
 * description:
 * ->
*/
typedef struct nc_time_t {
    v1f_t diff;
    v1f_t curr;
    v1f_t last;
} nc_time_t;
/** codetor **/
NC_API_CALL NC_API v1bit_t nc_time_ctor(nc_time_t** ref);
NC_API_CALL NC_API v1bit_t nc_time_dtor(nc_time_t** ref);
/** getters **/
/** setters **/
/** vetters **/
/** command **/
NC_API_CALL NC_API v1bit_t nc_time_work(nc_time_t* ref);
#       if (NC_LANG & NC_LANG_CPP)
}
#       endif   /* NC_LANG_CPP */
#	endif	/* NC_API */
/* end_of_file */
#endif /* NC_LIB_TIME_HXX */