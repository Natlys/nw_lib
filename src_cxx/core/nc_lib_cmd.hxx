#ifndef NC_LIB_COMMAND_HXX
#   define NC_LIB_COMMAND_HXX
#   include "../nc_lib_pch.hxx"
#   if (defined(NC_LIB_CORE_HXX))
/* defines */
#       if (!(defined(NC_USE_CMD)))
#       endif   /* NC_USE_CMD */
/* typedefs */
/* command_type
 * description:
 * ->
*/
typedef struct nc_cmd_t {
    data_t data;
};
#   else    /* NC_LIB_CORE_HXX */
#       error "nc_lib_core.hxx must be included before this header!"
#   endif  /* NC_LIB_CORE_HXX */
#endif  /* NC_LIB_COMMAND_HXX */