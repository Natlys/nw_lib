#include "../nc_lib_pch.hxx"
#include "nc_lib_time.hxx"
#if (defined(NC_API))
/* includes */
#   include "../core/nc_lib_sys.hxx"
#   include <time.h>
/* defines */
/* typedefs */
/** codetor **/
NC_API_CALL v1bit_t nc_time_ctor(nc_time_t** ref) {
    /* init */
    NC_CHECK(
        ref != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    nc_time_t* time = *ref;
    time->curr = NC_ZERO;
    time->last = NC_ZERO;
    time->diff = NC_ZERO;
    NC_CHECK(
        nc_lib_sys_mset(ref, NC_ZERO, sizeof(nc_time_t)),
        "failed to allocate a timer!",
        return NC_FALSE
    );
    /* quit */
    return NC_TRUTH;
}
NC_API_CALL v1bit_t nc_time_dtor(nc_time_t** ref) {
    /* init */
    NC_CHECK(
        ref != NC_NULL,
        "null error!",
        return NC_FALSE
    );
    /* work */
    nc_time_t* time = *ref;
    time->curr = NC_ZERO;
    time->last = NC_ZERO;
    time->diff = NC_ZERO;
    NC_CHECK(
        nc_lib_sys_mset(ref, sizeof(nc_time_t), NC_ZERO),
        "failed to allocate a timer!",
        return NC_FALSE
    );
    /* quit */
    return NC_TRUTH;
}
/** getters **/
/** setters **/
/** vetters **/
/** commands **/
NC_API_CALL v1bit_t nc_time_work(nc_time_t* ref) {
    /* init */
    /* work */
    ref->diff = ref->curr - ref->last;
    ref->last = ref->curr;
    ref->curr = ref->curr + ref->diff;
    /* quit */
    return NC_TRUTH;
}
#endif  /* NC_API */