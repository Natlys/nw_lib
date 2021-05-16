#ifndef NC_LIB_TABLE_H
#	define NC_LIB_TABLE_H
#	include "../nc_lib_core.h"
#	if (defined NC_API)
#		if !(defined NC_USE_NUMB_TABLE)
#			define NC_MIN_NUMB_TABLE 5u
#			define NC_MID_NUMB_TABLE 10u
#			define NC_MAX_NUMB_TABLE 30u
#			define NC_USE_NUMB_TABLE NC_MID_NUMB_TABLE
#		endif	// NC_USE_NUMB_TABLE //
/// table_iterator_type
/// description:
/// ->table iterator;
#       define nc_table_iter_t(tname) nc_table_iter##_##tname
#       define NC_TYPEDEF_TABLE_ITER(tname) /*iter type________*/ \
            typedef struct /*forward declaration for pointers__*/ \
                nc_table_iter_t(tname)  /*base name____________*/ \
                nc_table_iter_t(tname); /*same as above________*/ \
            typedef struct nc_table_iter_t(tname) { /*base name*/ \
                indx_t hash; /*hash value-key__________________*/ \
                tname data; /*the actual data__________________*/ \
                nc_table_iter_t(tname)* next; /*hash collisions*/ \
            } nc_table_iter_t(tname); /*template name__________*/ \
// type is defined //
/// table_main_type
/// description:
#       define nc_table_main_t(tname) nc_table_main##_##tname
#       define NC_TYPEDEF_TABLE_MAIN(tname) /*main type________*/ \
            typedef struct /*forward declaration for pointers__*/ \
                nc_table_main_t(tname)  /*base name____________*/ \
                nc_table_main_t(tname); /*same as above________*/ \
            typedef struct nc_table_main_t(tname) { /*base name*/ \
                nc_table_iter_t(tname)* head; /*first link_____*/ \
                nc_table_iter_t(tname)* back; /*last link______*/ \
            } nc_table_main_t(tname); /*template name__________*/ \
// type is defined //
// ctor_dtor //
#       define nc_table_ctor(tname, ref) ({         \
            ref.head = ref.back = NC_NULL;          \
            size_t size = NC_USE_NUMB_TABLE;    \
            size *= sizeof(nc_table_iter_t(tname)); \
            NC_MEM_MOVE(ref.head, NC_ZERO, size);   \
            ref.back = ref.head;                    \
            ref.back += NC_USE_NUMB_TABLE;      \
        })
#       define nc_table_dtor(tname, ref) ({         \
            size_t size = ref.back - ref.head;      \
            size *= sizeof(nc_table_iter_t(tname)); \
            NC_MEM_MOVE(ref.head, size, NC_ZERO);   \
            ref.head = ref.back = NC_NULL;          \
        })
// getters //
#       define nc_table_get_numb(tname, ref, numb) ({ \
            numb = ref.back - ref.head;               \
        })
#       define nc_table_get_size(tname, ref, size) ({ \
            nc_table_get_numb(tname, ref, size);      \
            size *= sizeof(nc_table_iter_t(tname));   \
        })
#       define nc_table_get_iter(tname, ref, key, iter) ({ \
            size_t numb = NC_ZERO;                         \
            nc_table_get_numb(tname, ref, numb);           \
            indx_t hash = NC_ZERO;                         \
            if (sizeof(key) == sizeof(cstr_t)) {           \
                NC_STR_HASH(key, hash);                    \
            } else {                                       \
                NC_VAL_HASH(key, hash);                    \
            }                                              \
            iter = ref.head[hash % numb];                  \
            while (iter.hash != hash) {                    \
                NC_CHECK(iter.next, "iter error!", break); \
                iter = *iter.next;                         \
            }                                              \
        })
#       define nc_table_get_elem(tname, ref, key, elem) ({ \
            nc_table_iter_t(tname) iter;                   \
            nc_table_get_iter(tname, ref, key, iter);      \
            elem = iter.data;                              \
        })
// setters //
#       define nc_table_set_numb(tname, ref, numb) ({ \
            size_t sz_old, sz_new;                    \
            sz_old = ref.back - ref.head;             \
            sz_old *= sizeof(nc_table_iter_t(tname)); \
            sz_new = numb;                            \
            sz_new *= sizeof(nc_table_iter_t(tname)); \
            NC_MEM_MOVE(ref.head, sz_old, sz_new);    \
            ref.back = ref.head + numb;               \
        })
#       define nc_table_set_elem(tname, ref, key, val) ({ \
            size_t numb = NC_ZERO;                        \
            nc_table_get_numb(tname, ref, numb);          \
            indx_t hash = NC_ZERO;                        \
            if (sizeof(key) == sizeof(cstr_t)) {          \
                NC_STR_HASH(key, hash);                   \
            } else {                                      \
                NC_VAL_HASH(key, hash);                   \
            }                                             \
            nc_table_iter_t(tname)* iter = NC_NULL;       \
            iter = &ref.head[hash % numb];                \
            if ((iter->hash % numb) == (hash % numb)) {   \
                while (iter->next != NC_NULL) {           \
                    iter = iter->next;                    \
                }                                         \
                size_t size = sizeof(*iter);              \
                NC_MEM_TAKE(iter->next, size);            \
                iter = iter->next;                        \
            }                                             \
            iter->hash = hash;                            \
            iter->data = val;                             \
        })
// commands //
#       define nc_table_each(tname, ref, actn) ({ \
            nc_table_iter_t(tname)* each;         \
            each = ref.head;                      \
            size_t indx = NC_ZERO;                \
            while(each != ref.back) {             \
                actn; indx++; each++;             \
            }                                     \
        })
#       define nc_table_oput(tname, ref) ({ \
            \
        })
#       define nc_table_olog(tname, ref) ({      \
            NC_OLOG(                             \
                "table:" "{" NC_STR_EOL          \
                "   numb:%d;" NC_STR_EOL         \
                "   data:" "{"                   \
                , (ref.back - ref.head)          \
            );                                   \
            nc_table_each(tname, ref, {          \
                NC_OPUT(                         \
                "   iter:{hash:%d;data:%d;",     \
                    each->hash, each->data       \
                );                               \
                nc_table_iter_t(tname)* next;    \
                next = each->next;               \
                while(next != NC_NULL) {         \
                    NC_OPUT(                     \
                    "next:{hash:%d;data:%d;};",  \
                        next->hash, next->data   \
                    );                           \
                    next = next->next;           \
                }                                \
                NC_OPUT("};" NC_STR_EOL);        \
            });                                  \
            NC_OPUT("   };" NC_STR_EOL);         \
            NC_OPUT("};" NC_STR_EOL);            \
        })
// other names //
#       define nc_table_t(tname) nc_table_main_t(tname)
#       define NC_TYPEDEF_TABLE(tname)    \
            NC_TYPEDEF_TABLE_ITER(tname); \
            NC_TYPEDEF_TABLE_MAIN(tname); \
// type is defined //
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_TABLE_H //