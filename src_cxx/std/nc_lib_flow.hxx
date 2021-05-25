#ifndef NC_LIB_FLOW_H
#   define NC_LIB_FLOW_H
#   include "../nc_lib_core.hxx"
#   if (defined NC_API)
/* includes */
/* defines */
#       define NC_FLOW_FLAG_WAIT  ( 1u << 0u )
#       define NC_FLOW_FLAG_LIVE  ( 1u << 1u )
#       if !(defined NC_DEFAULT_FLOW_SIZE)
#           define NC_MINIMAL_FLOW_SIZE ( 1 << 10u ) // 1 kb //
#           define NC_AVERAGE_FLOW_SIZE ( 1 << 15u ) // 32 kb //
#           define NC_MAXIMAL_FLOW_SIZE ( 1 << 20u ) // 1024 kb //
#           define NC_DEFAULT_FLOW_SIZE NC_AVERAGE_FLOW_SIZE
#       endif   // NC_DEFAULT_FLOW_SIZE //
/* flow_procedure_type
 * description:
 * interaction:
*/
typedef v1bit_t (*nc_flow_proc_t) (ptr_t iput, ptr_t oput);
/// flow_wapi_type_function
typedef LPTHREAD_START_ROUTINE nc_flow_wapi_proc_t;
/* flow_type
 * description:
 * interaction:
*/
typedef struct nc_flow_t {
    nc_wapi_thread_t mark;
    nc_flow_proc_t proc;
    indx_t indx;
    size_t size;
    flag_t flag;
} nc_flow_t;
// ctor_dtor //
v1bit_t nc_flow_ctor(nc_flow_t* flow);
v1bit_t nc_flow_dtor(nc_flow_t* flow);
/* getters */
/* setters */
v1bit_t nc_flow_set_size(nc_flow_t* flow, size_t size);
v1bit_t nc_flow_set_flag(nc_flow_t* flow, flag_t flag);
#       define nc_flow_add_flag(flowp, flagv) ( nc_flow_set_flag(flowp, flowp->flag| flagv) )
#       define nc_flow_rmv_flag(flowp, flagv) ( nc_flow_set_flag(flowp, flowp->flag& ~flagv) )
/* predicates */
#       define nc_flow_has_work(flowp)        ( ((flowp)->mark != NC_NULL) && ((flowp)->indx != NC_ZERO) )
#       define nc_flow_has_flag(flowp, flagv) ( (flowp)->flag & flagv )
#       define nc_flow_is_live(flowp)         ( (flowp)->flag & NC_FLOW_FLAG_LIVE )
#       define nc_flow_is_wait(flowp)         ( (flowp)->flag & NC_FLOW_FLAG_WAIT )
/* commands */
v1bit_t nc_flow_init(nc_flow_t* flow);
v1bit_t nc_flow_quit(nc_flow_t* flow);
v1bit_t nc_flow_work(nc_flow_t* flow, ptr_t iput, ptr_t oput);
v1bit_t nc_flow_olog(nc_flow_t* flow);
// // system // //
DWORD nc_flow_wapi_proc(LPVOID iput);
// // testing // //
v1bit_t nc_flow_test_proc(ptr_t iput, ptr_t oput);
#   endif /* NC_API */
/* end_of_file */
#endif  // NC_LIB_FLOW_H //