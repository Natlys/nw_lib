#ifndef NC_LIB_LOADER_H
#   define NC_LIB_LOADER_H
#include "../nc_lib_core.h"
#   if (defined NC_API)
// includes //
// types //
/// native_code_type
/// description:
/// ->
/// interface:
/// ->
typedef struct {
    nc_wapi_library_t handle;
    str_t name;
} nc_lib_loader_t;
typedef const nc_lib_loader_t nc_lib_loader_tc;
// ctor_dtor //
NC_API v1bit_t nc_lib_loader_ctor(nc_lib_loader_t* ref);
NC_API v1bit_t nc_lib_loader_dtor(nc_lib_loader_t* ref);
// getters //
// setters //
NC_API v1bit_t nc_lib_loader_set_name(nc_lib_loader_t* ref, cstr_t name);
// predicates //
// commands //
NC_API v1bit_t nc_lib_loader_init(nc_lib_loader_t* ref);
NC_API v1bit_t nc_lib_loader_quit(nc_lib_loader_t* ref);
NC_API v1bit_t nc_lib_loader_load(nc_lib_loader_t* ref, cstr_t name, ptr_t* proc);
#   endif  // NC_API //
// end_of_file //
#endif // NC_LIB_LOADER_H //