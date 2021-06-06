#include "../nc_lib_pch.hxx"
#include "../nc_lib.hxx"
#if (defined(NC_API))
/* types */
/* library_system_type
 * description:
 * -> contains function pointers for standard functions;
 * -> handles block of memory and its size;
*/
typedef struct nc_lib_sys_t {
    nc_sys_init_f init;
    nc_sys_quit_f quit;
    nc_sys_work_f work;
    nc_sys_mset_f mset;
} nc_lib_sys_t;
nc_lib_sys_t nc_lib_sys = {
    .init = nc_lib_sys_init,
    .quit = nc_lib_sys_quit,
    .work = nc_lib_sys_work,
    .mset = nc_lib_sys_mset
};
/* command */
NC_API_CALL v1bit_t nc_lib_sys_init() {
    /* init */
    /* work */
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_lib_sys_quit() {
    /* init */
    /* work */
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_lib_sys_work() {
    /* init */
    /* work */
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_lib_sys_mset(ptr_t* data, size_t isize, size_t osize) {
    /* init */
    /* work */
    NC_MEM_EDIT(*data, isize, osize);
    /* quit */
    return NC_TRUTH;
}
#endif  /* NC_API */
/* end_of_file */