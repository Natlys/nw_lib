#include "nc_lib_pch.hpp"
#include "nc_ecs_ent_sys.hpp"
#if (defined NC_API)
// ctor_dtor //
nc_ent_sys::nc_ent_sys() : nc_system_ttr() { }
nc_ent_sys::~nc_ent_sys() { }
// commands //
v1bit_t nc_ent_sys::init() { NC_CHECK(nc_system_ttr::init(), "init error!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_ent_sys::quit() { NC_CHECK(nc_system_ttr::quit(), "quit error!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_ent_sys::work() { NC_CHECK(nc_system_ttr::quit(), "work error!", return NC_FALSE); return NC_TRUTH; }
#endif	// NC_API