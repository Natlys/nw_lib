#include "nc_lib_pch.hpp"
#include "nc_ecs_ent_sys.hpp"
#if (defined NC_API)
// ctor_dtor //
nc_ent_sys::nc_ent_sys() : ref_sys_tt() { }
nc_ent_sys::~nc_ent_sys() { }
// commands //
v1bit_t nc_ent_sys::init() { NC_CHECK(ref_sys_t::init(), "failed init!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_ent_sys::quit() { NC_CHECK(ref_sys_t::quit(), "failed quit!", return NC_FALSE); return NC_TRUTH; }
#endif	// NC_API