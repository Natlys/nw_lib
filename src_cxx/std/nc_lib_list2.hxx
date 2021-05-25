#ifndef NC_LIB_LIST2_H
#	define NC_LIB_LIST2_H
#	include "../nc_lib_core.hxx"
#	if (defined NC_API)
#		if !(defined NC_USE_NUMB_LIST2)
#			define NC_MIN_NUMB_LIST2 0u
#			define NC_MID_NUMB_LIST2 3u
#			define NC_MAX_NUMB_LIST2 10u
#			define NC_USE_NUMB_LIST2 NC_MIN_NUMB_LIST2
#		endif	// NC_USE_NUMB_LIST2 //
/// list2_iterator_type
/// description:
/// ->two-linked list iterator;
#       define nc_list2_iter_t(tname) nc_list2_iter##_##tname
#       define NC_TYPEDEF_LIST2_ITER(tname) /*iterator type__*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list2_iter_t(tname)  /*base name__________*/ \
                nc_list2_iter_t(tname); /*same as above______*/ \
            typedef struct nc_list2_iter_t(tname) { /*name___*/ \
                nc_list2_iter_t(tname)* next; /*next link____*/ \
                nc_list2_iter_t(tname)* prev; /*prev link____*/ \
                tname data; /*the actual data________________*/ \
            } nc_list2_iter_t(tname); /*template name________*/ \
// type is defined //
/// list2_main_type
/// description:
/// ->one-linked forward list;
/// ->can grow linearly in front;
/// ->has own iterator type;
/// ->uses 2 iterators as begin-end pointers;
#       define nc_list2_main_t(tname) nc_list2_main##_##tname
#       define NC_TYPEDEF_LIST2_MAIN(tname) /*main type______*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list2_main_t(tname)  /*base name__________*/ \
                nc_list2_main_t(tname); /*same as above______*/ \
            typedef struct nc_list2_main_t(tname) { /*name___*/ \
                nc_list2_iter_t(tname)* head; /*first link___*/ \
                nc_list2_iter_t(tname)* back; /*last link____*/ \
                size_t numb; /*number of values______________*/ \
            } nc_list2_main_t(tname); /*template name________*/ \
// type is defined //
// ctor_dtor //
#       define nc_list2_ctor(tname, ref) ({              \
            ref.head = NC_NULL;                          \
            ref.back = NC_NULL;                          \
            ref.numb = NC_ZERO;                          \
            while(ref.numb < NC_USE_NUMB_LIST2) {    \
                nc_list2_add_iter(tname, ref, ref.head); \
            }                                            \
        })
#       define nc_list2_dtor(tname, ref) ({              \
            while(ref.head != ref.back) {                \
                nc_list2_rmv_iter(tname, ref, ref.head); \
            }                                            \
            ref.head = NC_NULL;                          \
            ref.back = NC_NULL;                          \
            ref.numb = NC_ZERO;                          \
        })
/* getters */
#       define nc_list2_get_numb(tname, ref, numb) ({ \
            nc_list2_iter_t(tname)* iter = ref.head;  \
            numb = NC_ZERO;                           \
            while (iter != ref.back) {                \
                iter = iter->next;                    \
                numb = numb + NC_UNIT;                \
            }                                         \
        })
#       define nc_list2_get_iter(tname, ref, indx, iter) ({ \
            size_t numb = NC_ZERO;                          \
            iter = ref.head;                                \
            while (numb < indx) {                           \
                iter = iter->next;                          \
                numb = numb + NC_UNIT;                      \
            }                                               \
        })
/* setters */
#       define nc_list2_set_elem(tname, ref, indx, elem) ({ \
            nc_list2_iter_t(tname)* temp = ref.head;        \
            size_t numb = NC_ZERO;                          \
            while(numb < indx) {                            \
                temp = temp->next;                          \
                numb = numb + NC_UNIT;                      \
            }                                               \
            temp->data = elem;                              \
        })
#       define nc_list2_add_iter(tname, ref, iter) ({     \
            nc_list2_iter_t(tname)* next;                 \
            size_t size = sizeof(nc_list2_iter_t(tname)); \
            NC_MEM_TAKE(next, size); /*create new node*/  \
            if (ref.head) { /*fix iter and iter->next*/   \
                ref.numb = ref.numb + NC_UNIT;            \
                next->next = iter->next;                  \
                next->prev = iter;                        \
                if (iter->next) { /*iter is not prev*/    \
                    iter->next->prev = next; /*anymore*/  \
                }                                         \
                iter->next = next; /*iter->next->i_next*/ \
            } else { /*set the first link as a head*/     \
                ref.head = next;                          \
                ref.back = NC_NULL;                       \
                ref.numb = NC_UNIT;                       \
                ref.head->next = ref.back;                \
            }                                             \
        })
#       define nc_list2_rmv_iter(tname, ref, iter) ({ \
            if (iter->prev) {                         \
                iter->prev->next = iter->next;        \
            }                                         \
            if (iter->next) {                         \
                iter->next->prev = iter->prev;        \
            }                                         \
            size_t size = NC_ZERO;                    \
            size = sizeof(nc_list2_iter_t(tname));    \
            ref.numb = ref.numb - NC_UNIT;            \
            NC_MEM_FREE(iter, size);                  \
        })
/* commands */
#       define nc_list2_each(tname, ref, actn) ({    \
            nc_list2_iter_t(tname)* each = ref.head; \
            indx_t indx = NC_ZERO;                   \
            while (each != ref.back) {               \
                actn; indx++; each = each->next;     \
            }                                        \
        })
#       define nc_list2_swap(tname, ref, iter0, iter1) ({ \
            nc_list2_iter_t(tname)* prev0 = iter0->prev;  \
            nc_list2_iter_t(tname)* prev1 = iter1->prev;  \
            iter1->prev = prev0;                          \
            if (prev0 != NC_NULL) {                       \
                prev0->next = iter1;                      \
            }                                             \
            iter0->prev = prev1;                          \
            if (prev1 != NC_NULL) {                       \
                prev1->next = iter0;                      \
            }                                             \
            nc_list2_iter_t(tname)* next0 = iter0->next;  \
            nc_list2_iter_t(tname)* next1 = iter1->next;  \
            iter1->next = next0;                          \
            if (next0 != NC_NULL) {                       \
                next0->prev = iter1;                      \
            }                                             \
            iter0->next = next1;                          \
            if (next1 != NC_NULL) {                       \
                next1->prev = iter0;                      \
            }                                             \
        })
#       define nc_list2_oput(tname, ref) ({ \
            \
        })
#       define nc_list2_olog(tname, ref) ({          \
            size_t numb = NC_ZERO;                   \
            nc_list2_get_numb(tname, ref, numb);     \
            NC_OLOG("list2:");                       \
            NC_OPUT("{" NC_EOL);                     \
            NC_OPUT(NC_TAB "numb:%d;" NC_EOL, numb); \
            nc_list2_each(tname, ref, {              \
                NC_OPUT(                             \
                    NC_TAB "{" NC_EOL                \
                    NC_TAB NC_TAB "indx:%d;" NC_EOL  \
                    NC_TAB NC_TAB "data:%d;" NC_EOL  \
                    NC_TAB "};" NC_EOL               \
                    , indx                           \
                    , each ? each->data : NC_ZERO    \
                );                                   \
            });                                      \
            NC_OPUT("};" NC_EOL);                    \
        })
#       define nc_list2_move(tname, iter, numb) ({ \
            size_t indx = NC_ZERO;                 \
            while(indx < numb) {                   \
                iter = iter.next;                  \
                indx = indx + NC_UNIT;             \
            }                                      \
        })
// other_names //
#       define nc_list2_t(tname) nc_list2_main_t(tname)
#       define NC_TYPEDEF_LIST2(tname)    \
            NC_TYPEDEF_LIST2_ITER(tname); \
            NC_TYPEDEF_LIST2_MAIN(tname); \
// type is defined //
#	endif   /* NC_API */
/* end_of_file */
#endif // NC_LIB_LIST2_H //