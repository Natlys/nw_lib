#ifndef NC_LIB_FLOW_HXX
#   define NC_LIB_FLOW_HXX
#   include "../nc_lib_core.hxx"
#   if (defined(NC_API))
/* includes */
/* defines */
#       if (NC_LANG & NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
#       define NC_FLOW_FLAG_WAIT  ( 1u << 0u )
#       define NC_FLOW_FLAG_LIVE  ( 1u << 1u )
#       if (!(defined(NC_USE_FLOW_SIZE)))
#           define NC_MIN_FLOW_SIZE ( 1 << 10u ) /* 1 kb */
#           define NC_MID_FLOW_SIZE ( 1 << 15u ) /* 32 kb */
#           define NC_MAX_FLOW_SIZE ( 1 << 20u ) /* 1024 kb */
#           define NC_USE_FLOW_SIZE NC_MID_FLOW_SIZE
#       endif   /* NC_USE_FLOW_SIZE */
/* flow_procedure_function
 * description:
 * ->
*/
typedef v1bit_t (*nc_flow_proc_f) (ptr_t iput, ptr_t oput);
/* flow_wapi_function */
/* flow_type
 * description:
 * ->
*/
typedef struct nc_flow_t nc_flow_t;
/* codetor */
NC_API_CALL NC_API v1bit_t nc_flow_ctor(nc_flow_t** ref);
NC_API_CALL NC_API v1bit_t nc_flow_dtor(nc_flow_t** ref);
/* getters */
/* setters */
NC_API_CALL NC_API v1bit_t nc_flow_set_size(nc_flow_t* flow, size_t size);
NC_API_CALL NC_API v1bit_t nc_flow_set_flag(nc_flow_t* flow, flag_t flag);
NC_API_CALL NC_API v1bit_t nc_flow_add_flag(nc_flow_t* flow, flag_t flag);
NC_API_CALL NC_API v1bit_t nc_flow_rmv_flag(nc_flow_t* flow, flag_t flag);
/* vetters */
NC_API_CALL NC_API v1bit_t nc_flow_vet_work(nc_flow_t* flow);
NC_API_CALL NC_API v1bit_t nc_flow_vet_flag(nc_flow_t* flow, flag_t flag);
NC_API_CALL NC_API v1bit_t nc_flow_vet_live(nc_flow_t* flow);
NC_API_CALL NC_API v1bit_t nc_flow_vet_wait(nc_flow_t* flow);
/* command */
NC_API_CALL NC_API v1bit_t nc_flow_init(nc_flow_t* flow);
NC_API_CALL NC_API v1bit_t nc_flow_quit(nc_flow_t* flow);
NC_API_CALL NC_API v1bit_t nc_flow_work(nc_flow_t* flow, ptr_t iput, ptr_t oput);
NC_API_CALL NC_API v1bit_t nc_flow_olog(nc_flow_t* flow);
/** system  **/
/** testing  **/
#       if (NC_LANG & NC_LANG_CPP)
}
#       endif   /* NC_LANG_CPP */
#   endif /* NC_API */
/* end_of_file */
#endif  /* NC_LIB_FLOW_HXX */