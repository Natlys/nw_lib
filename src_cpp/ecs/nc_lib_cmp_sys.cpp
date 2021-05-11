#include "../nc_lib_pch.hpp"
#include "nc_lib_cmp_sys.hpp"
#if (defined NC_API)
nc_cmp_sys::nc_cmp_sys() : ref_sys_t() { }
nc_cmp_sys::~nc_cmp_sys() { }
// commands //
v1bit_t nc_cmp_sys::init() { NC_CHECK(ref_sys_t::init(), "failed init!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_cmp_sys::quit() { NC_CHECK(ref_sys_t::quit(), "failed quit!", return NC_FALSE); return NC_TRUTH; }
#endif	// NC_API