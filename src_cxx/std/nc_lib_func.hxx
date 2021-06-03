#ifndef NC_LIB_FUNC_HXX
#   define  NC_LIB_FUNC_HXX
#   include "../nc_lib_core.hxx"
#   if (defined(NC_API))
#       include "../core/nc_lib_sys.hxx"
/*
 * function_procedure_type
 * description:
 * ->
 * interaction:
 * ->
*/
#       define nc_func_proc_t(itype, otype) nc_func_proc##_##itype##_##otype
#       define NC_TYPEDEF_FUNC_PROC(itype, otype)                  \
            typedef otype (*nc_func_proc_t(itype, otype)) (itype); \
/* type is defined */
/** ctor_dtor **/
/** getters **/
/** setters **/
/** vetters **/
/** commands **/
/*
 * function_main_type
 * description:
 * ->
 * interaction:
 * ->
*/
#       define nc_func_main_t(itype, otype) nc_func_main##_##itype##_##otype
#       define NC_TYPEDEF_FUNC_MAIN(itype, otype)         \
            typedef struct                                \
                nc_func_main_t(itype, otype)              \
                nc_func_main_t(itype, otype);             \
            typedef struct nc_func_main_t(itype, otype) { \
                nc_func_proc_t(itype, otype)* proc;       \
                nc_func_main_t(itype, otype)* next;       \
            } nc_func_main_t(itype, otype);
/* type is defined */
/** ctor_dtor **/
#       define nc_func_ctor(itype, otype, ref) ({ \
            ref.proc = NC_NULL;                   \
            ref.next = NC_NULL;                   \
})
#       define nc_func_dtor(itype, otype, ref) ({ \
            while(ref.next) {                     \
                nc_func_rmv(itype, otype, ref);   \
            }                                     \
            ref.proc = NC_NULL;                   \
            ref.next = NC_NULL;                   \
})
/** getters **/
/** setters **/
#       define nc_func_add(itype, otype, ref) ({ \
            NC_MEM_TAKE(ref.next, sizeof(ref));  \
}
#       define nc_func_rmv(itype, otype, ref) ({ \
            nc_func_main_t(itype, otype)* temp;  \
            temp = NC_NULL;                      \
            while (temp != ref) {                \
                temp = ref;                      \
                while (temp.next != NC_NULL) {   \
                    temp = temp.next;            \
                }                                \
                NC_MEM_FREE(temp, sizeof(*temp); \
            }                                    \
            NC_MEM_FREE(ref, sizeof(*ref);       \
            else {                               \
                NC_ERROR("set error!", NC_VOID); \
            }                                    \
})
/** vetters **/
/** commands **/
#       define nc_func_work(itype, otype, ref, iput) ({ \
            nc_func_main_t(itype, otype)* temp = ref;   \
            while(temp != NC_NULL) {                    \
                iput = temp->proc(iput);                \
                temp = temp->next;                      \
            }                                           \
})
/* other names */
#       define nc_func_t(itype, otype) nc_func_main_t(itype, otype)
#       define NC_TYPEDEF_FUNC(itype, otype) \
            NC_TYPEDEF_FUNC_PROC(itype, otype); \
            NC_TYPEDEF_FUNC_MAIN(itype, otype); \
/* type is defined */
#   endif   /* NC_API */
#endif  /* NC_LIB_FUNC_HXX */