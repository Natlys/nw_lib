#include "../nc_lib_pch.hxx"
#include "nc_lib_sys.hxx"
#if (defined(NC_API))
/* includes */
struct nc_lib_sys_t {
    nc_sys_t base; /* standard system */
} nc_lib_sys = {
    .base = {
        .init = nc_lib_sys_init,
        .quit = nc_lib_sys_quit,
        .work = nc_lib_sys_work,
        .mset = nc_lib_sys_mset,
        .data = NC_VOID_PTR,
        .size = NC_USE_SYS_MEM,
    }
};
/* getters */
nc_lib_sys_t* nc_lib_sys_get() {
    return &nc_lib_sys;
}
/* setters */
/* commands */
v1bit_t nc_lib_sys_init() {
    NC_PCALL({ /* init */
        NC_CHECK(NC_MEM_ISIDE_SIZE_FULL(nc_lib_sys.base.size), "memory error!", return NC_FALSE);
    }, "init error!", return NC_FALSE);
    NC_PCALL({ /* work */
    }, "init error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_lib_sys_quit() {
    NC_PCALL({ /* init */
    }, "quit error!", return NC_FALSE);
    NC_PCALL({ /* work */
    }, "quit error!", return NC_FALSE);
    /* quit */
    return NC_TRUTH;
}
v1bit_t nc_lib_sys_work() {
    NC_PCALL({ /* init */
    }, "work error!", return NC_FALSE);
    NC_PCALL({ /* work */
    }, "work error!", return NC_FALSE);
    return NC_TRUTH;
}
v1bit_t nc_lib_sys_mset(ptr_t* data, size_t isize, size_t osize) {
    NC_PCALL({ /* init */
    }, "mset error!", return NC_FALSE);
    NC_PCALL({ /* work */
    NC_MEM_EDIT(*data, isize, osize);
    }, "mset error!", return NC_FALSE);
    return NC_TRUTH;
}
#endif  /* NC_API */