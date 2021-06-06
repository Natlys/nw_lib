#ifndef NC_LIB_HLIBRARY_HXX
#   define NC_LIB_HLIBRARY_HXX
#include "../nc_lib_core.hxx"
#   if (defined(NC_API))
/* includes */
/* defines */
#       if (NC_LANG & NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
/* typedefs */
/* module_type
 * description:
 * ->
*/
typedef struct {
    nc_wapi_module_t hand;
    str_t name;
} nc_module_t;
typedef const nc_module_t nc_module_tc;
/** getters **/
#       define nc_module_get_proc(ref, name, proc) ({ \
            proc = GetProcAddress(ref.hand, name);    \
        })
/** setters **/
#       define nc_module_set_name(ref, str) ({          \
            size_t prev = NC_ZERO, next = NC_ZERO;      \
            if (ref.name) { prev = strlen(ref.name); }  \
            if (str) { next = strlen(str); }            \
            NC_MEM_EDIT(ref.name, prev, next);          \
            if (str) { strcpy_s(ref.name, next, str); } \
        })
/** vetters **/
/** command **/
#       define nc_module_init(ref) ({  \
            NC_CHECK(                  \
                ref.name != NC_NULL,   \
                "init error!",         \
                NC_VOID                \
            );                         \
            NC_CHECK(                  \
                ref.hand == NC_NULL,   \
                "init error!",         \
                NC_VOID                \
            );                         \
        })
#       define nc_module_quit(ref) ({  \
            NC_CHECK(                  \
                ref.name != NC_NULL,   \
                "quit error!",         \
                NC_VOID                \
            );                         \
            NC_CHECK(                  \
                ref.hand != NC_NULL,   \
                "quit error!",         \
                NC_VOID                \
            );                         \
            FreeLibrary(ref.hand);     \
            size_t sz;                 \
            sz = strlen(ref.name);     \
            NC_MEM_FREE(ref.name, sz); \
        })
#       if (NC_LANG & NC_LANG_CPP)
}
#       endif   /* NC_LANG_CPP */
#   endif  /* NC_API */
/* end_of_file */
#endif  /* NC_LIB_HLIBRARY_HXX */