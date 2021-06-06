#ifndef NC_LIB_UTILITY_HXX
#	define NC_LIB_UTILITY_HXX
#	include "../nc_lib_core.hxx"
#	if (defined NC_API)
/* includes */
/* defines */
#       if (NC_LANG & NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
/* typedefs */
/* iterator_type
 * description:
 * ->
*/
#       define nc_iter_t(tcont, tname) nc_##tcont##_iter_t
/* pair_type
 * description:
 * ->
*/
#       define nc_pair_t(tval0, tval1) nc_pair##_##tval0##_##tval1
#       define NC_TYPEDEF_PAIR(tval0, tval1) /*template definition*/ \
            typedef struct nc_pair##_##tval0##_##tval1 { /*default*/ \
                tval0 val0; tval1 val1; /*actual data_____________*/ \
            } nc_pair##_##tval0##_##tval1 /*template name_________*/ \
/* type is defined */
/* codetor */
/* command */
#       if (NC_LANG & NC_LANG_CPP)
}
#       endif   /* NC_LANG_CPP */
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_UTILITY_HXX */