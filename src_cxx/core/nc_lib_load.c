#include "../nc_lib_pch.h"
#include "nc_lib_load.h"
#if (defined NC_API)
#   include "../../nc_mem/src_cxx/core/nc_mem_sys.h"
// ctor_dtor //
v1bit_t nc_lib_loader_ctor(nc_lib_loader_t* ref) {
    // checking //
    // action //
    ref->handle = NC_NULL;
    ref->name = NC_NULL;
    // result //
    return NC_TRUTH;
}
v1bit_t nc_lib_loader_dtor(nc_lib_loader_t* ref) {
    // checking //
    NC_CHECK(ref->name == NC_NULL, "quit is required!", return NC_FALSE);
    NC_CHECK(ref->handle == NC_NULL, "quit is required!", return NC_FALSE);
    // action //
    // result //
    return NC_TRUTH;
}
// getters //
// setters //
v1bit_t nc_lib_loader_set_name(nc_lib_loader_t* ref, cstr_t name) {
    // checking //
    NC_CHECK(ref->handle == NC_NULL, "quit is required", return NC_FALSE);
    // action //
    if (ref->name != NC_NULL) {  NC_MEM_FREE(ref->name, strlen(ref->name)); }
    NC_MEM_TAKE(ref->name, strlen(name));
    strcpy(ref->name, name);
    // result //
    return NC_TRUTH;
}
// predicates //
// commands //
v1bit_t nc_lib_loader_init(nc_lib_loader_t* ref) {
    // checking //
    NC_CHECK(ref->name != NC_NULL, "ctor is required!", return NC_FALSE);
    // action //
    ref->handle = LoadLibrary(ref->name);
    // result //
    NC_CHECK(ref->handle != NC_NULL, "load error!", return NC_FALSE);
    return NC_TRUTH;
}
v1bit_t nc_lib_loader_quit(nc_lib_loader_t* ref) {
    // checking //
    NC_CHECK(ref->name != NC_NULL, "init is required!", return NC_FALSE);
    NC_CHECK(ref->handle != NC_NULL, "init is required!", return NC_FALSE);
    // action //
    FreeLibrary(ref->handle);
    ref->handle = NC_NULL;
    // result //
    return NC_TRUTH;
}
v1bit_t nc_lib_loader_load(nc_lib_loader_t* ref, cstr_t name, ptr_t* proc) {
    // checking //
    NC_CHECK(ref != NC_NULL, "handle error!", return NC_FALSE);
    NC_CHECK(ref->handle != NC_NULL, "handle error!", return NC_FALSE);
    NC_CHECK(ref->name != NC_NULL, "handle error!", return NC_FALSE);
    NC_CHECK(proc != NC_NULL, "handle error!", return NC_FALSE);
    // action //
    *proc = GetProcAddress(ref->handle, name);
    // result //
    NC_CHECK(*proc != NC_NULL, "load error!", return NC_FALSE);
    return NC_TRUTH;
}
// end_of_file //
#endif  // NC_API //