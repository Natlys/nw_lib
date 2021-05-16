#ifndef NC_LIB_MODULE_H
#   define NC_LIB_MODULE_H
#include "../nc_lib_core.h"
#   if (defined NC_API)
// includes //
// types //
/// module_type
/// description:
/// ->
/// interface:
/// ->
typedef struct {
    nc_wapi_module_t handle;
    str_t name;
} nc_module_t;
typedef const nc_module_t nc_module_tc;
// ctor_dtor //
NC_API v1bit_t nc_module_ctor(nc_module_t* ref);
NC_API v1bit_t nc_module_dtor(nc_module_t* ref);
// // getters //
// // setters //
NC_API v1bit_t nc_module_set_name(nc_module_t* ref, cstr_t name);
// // predicates //
// // commands //
NC_API v1bit_t nc_module_init(nc_module_t* ref);
NC_API v1bit_t nc_module_quit(nc_module_t* ref);
NC_API v1bit_t nc_module_load(nc_module_t* ref, cstr_t name, nil_t** proc);
#   endif  // NC_API //
// end_of_file //
#endif // NC_LIB_MODULE_H //