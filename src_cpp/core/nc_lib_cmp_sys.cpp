#include "../nc_lib_pch.hpp"
#include "nc_lib_cmp_sys.hpp"
#if (defined NC_API)
nc_cmp_sys::nc_cmp_sys() : nc_system_ttr() { }
nc_cmp_sys::~nc_cmp_sys() { }
// commands //
v1bit_t nc_cmp_sys::init() { NC_CHECK(nc_system_ttr::init(), "init error!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_cmp_sys::quit() { NC_CHECK(nc_system_ttr::quit(), "quit error!", return NC_FALSE); return NC_TRUTH; }
v1bit_t nc_cmp_sys::work() { NC_CHECK(nc_system_ttr::work(), "work error!", return NC_FALSE); return NC_TRUTH; }
#endif	// NC_API