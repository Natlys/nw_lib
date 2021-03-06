#ifndef NC_LIB_LIST1_HXX
#	define NC_LIB_LIST1_HXX
#	include "../nc_lib_core.hxx"
#	if (defined(NC_API))
/* includes */
/* defines */
#       if (NC_LANG & NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
#		if (!(defined(NC_USE_NUMB_LIST1)))
#			define NC_MIN_NUMB_LIST1 0u
#			define NC_MID_NUMB_LIST1 3u
#			define NC_MAX_NUMB_LIST1 10u
#			define NC_USE_NUMB_LIST1 NC_MIN_NUMB_LIST1
#		endif	/* NC_USE_NUMB_LIST1 */
/* list1_iterator_type
 * description:
 * -> one-linked list iterator;
*/
#       define nc_list1_iter_t(tname) nc_list1_iter##_##tname
#       define NC_TYPEDEF_LIST1_ITER(tname) /*iterator type__*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list1_iter_t(tname)  /*base name__________*/ \
                nc_list1_iter_t(tname); /*same as above______*/ \
            typedef struct nc_list1_iter_t(tname) { /*name___*/ \
                nc_list1_iter_t(tname)* next; /*next link____*/ \
                tname data; /*the actual data________________*/ \
            } nc_list1_iter_t(tname); /*template name________*/ \
/* type is defined */
/* list1_main_type
 * description:
 * -> one-linked forward list;
 * -> can grow linearly in front;
 * -> has own iterator type;
 * -> uses 2 iterators as begin-end pointers;
*/
#       define nc_list1_main_t(tname) nc_list1_main##_##tname
#       define NC_TYPEDEF_LIST1_MAIN(tname) /*main type______*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list1_main_t(tname)  /*base name__________*/ \
                nc_list1_main_t(tname); /*same as above______*/ \
            typedef struct nc_list1_main_t(tname) { /*name___*/ \
                nc_list1_iter_t(tname)* head; /*first link___*/ \
                nc_list1_iter_t(tname)* back; /*last link____*/ \
                size_t numb; /*number of links_______________*/ \
            } nc_list1_main_t(tname); /*template name________*/ \
/* type is defined */
/* codetor */
#       define nc_list1_ctor(tname, ref) ({              \
            ref.head = NC_NULL;                          \
            ref.back = NC_NULL;                          \
            ref.numb = NC_ZERO;                          \
            while(ref.numb < NC_USE_NUMB_LIST1) {    \
                nc_list1_add_iter(tname, ref, ref.head); \
            }                                            \
        })
#       define nc_list1_dtor(tname, ref) ({              \
            while(ref.head != ref.back) {                \
                nc_list1_rmv_iter(tname, ref, ref.head); \
            }                                            \
            ref.head = NC_NULL;                          \
            ref.back = NC_NULL;                          \
            ref.numb = NC_ZERO;                          \
        })
/* getters */
#       define nc_list1_get_numb(tname, ref, numb) ({ \
            nc_list1_iter_t(tname)* iter = ref.head;  \
            numb = NC_ZERO;                           \
            while (iter != ref.back) {                \
                iter = iter->next;                    \
                numb = numb + NC_UNIT;                \
            }                                         \
        })
#       define nc_list1_get_iter(tname, ref, indx, iter) ({ \
            size_t numb = NC_ZERO;                          \
            nc_list1_iter_t(tname)* temp = ref.head;        \
            while (numb < indx) {                           \
                temp = temp->next;                          \
                numb = numb + NC_UNIT;                      \
            }                                               \
            iter = temp;                                    \
        })
#       define nc_list1_get_elem(tname, ref, indx, elem) ({ \
            size_t numb = NC_ZERO;                          \
            nc_list1_iter_t(tname)* temp = ref.head;        \
            while (numb < indx) {                           \
                temp = temp->next;                          \
                numb = numb + NC_UNIT;                      \
            }                                               \
            elem = temp->data;                              \
        })
/* setters */
#       define nc_list1_set_elem(tname, ref, indx, elem) ({ \
            nc_list1_iter_t(tname)* temp = ref.head;        \
            size_t numb = NC_ZERO;                          \
            while(numb < indx) {                            \
                temp = temp->next;                          \
                numb = numb + NC_UNIT;                      \
            }                                               \
            temp->data = elem;                              \
        })
#       define nc_list1_add_iter(tname, ref, iter) ({     \
            nc_list1_iter_t(tname)* next = NC_NULL;       \
            size_t size = sizeof(nc_list1_iter_t(tname)); \
            nc_lib_sys_mset(&next, NC_ZERO, size);        \
            if (ref.head) { /*insert in front*/           \
                next->next = iter->next;                  \
                iter->next = next;                        \
            } else { /*set this as a new head*/           \
                next->next = NC_NULL;                     \
                ref.head = next;                          \
            }                                             \
            ref.numb = ref.numb + NC_UNIT;                \
        })
#       define nc_list1_rmv_iter(tname, ref, iter) ({ \
            size_t size = sizeof(nc_list1_t(tname));  \
            if (iter == ref.head) { /*just move it*/  \
                ref.head = iter->next;                \
                ref.back = NC_NULL;                   \
                ref.numb = ref.numb - NC_UNIT;        \
                NC_MEM_FREE(iter, size);                 \
            } else { /*iter->prev must be changed*/   \
                nc_list1_iter_t(tname)* temp;         \
                temp = ref.head;                      \
                while(temp != ref.back) {             \
                    if (temp->next == iter) {         \
                        break;                        \
                    }                                 \
                    temp = temp->next;                \
                }                                     \
                temp->next = iter->next;              \
                nc_lib_sys_mset(iter, size, NC_ZERO); \
                ref.numb = ref.numb - NC_UNIT;        \
            }                                         \
        })
/* command */
#       define nc_list1_each(tname, ref, actn) ({    \
            nc_list1_iter_t(tname)* each = ref.head; \
            indx_t indx = NC_ZERO;                   \
            while (each != NC_NULL) {                \
                actn; indx++; each = each->next;     \
            }                                        \
        })
#       define nc_list1_swap(tname, ref, iter0, iter1) ({ \
            nc_list1_iter_t(tname)* head = ref.head;      \
            nc_list1_iter_t(tname)* next0 = iter0->next;  \
            nc_list1_iter_t(tname)* next1 = iter1->next;  \
            nc_list1_iter_t(tname)* prev0 = head;         \
            nc_list1_iter_t(tname)* prev1 = head;         \
            iter0->next = next1;                          \
            iter1->next = next0;                          \
            if (iter0 != ref.head) {                      \
                while(prev0->next != iter0) {             \
                    prev0 = prev0->next;                  \
                }                                         \
            } else { head = iter1; }                      \
            if (iter1 != ref.head) {                      \
                while(prev1->next != iter1) {             \
                    prev1 = prev1->next;                  \
                }                                         \
            } else { head = iter0; }                      \
            prev0->next = iter1;                          \
            prev1->next = iter0;                          \
            ref.head = head;                              \
        })
#       define nc_list1_oput(tname, ref) ({ \
            \
        })
#       define nc_list1_olog(tname, ref) ({          \
            size_t numb = NC_ZERO;                   \
            nc_list1_get_numb(tname, ref, numb);     \
            NC_OLOG("list1:");                       \
            NC_OPUT("{" NC_ENDL);                     \
            NC_OPUT(NC_TABL "numb:%d;" NC_ENDL, numb); \
            nc_list1_each(tname, ref, {              \
                NC_OPUT(                             \
                    NC_TABL "{" NC_ENDL                \
                    NC_TABL NC_TABL "indx:%d;" NC_ENDL  \
                    NC_TABL NC_TABL "data:%d;" NC_ENDL  \
                    NC_TABL "};" NC_ENDL               \
                    , indx                           \
                    , each ? each->data : NC_ZERO    \
                );                                   \
            });                                      \
            NC_OPUT("};" NC_ENDL);                    \
        })
#       define nc_list1_move(tname, iter, numb) ({ \
            size_t indx = NC_ZERO;                 \
            while(indx < numb) {                   \
                indx = indx + NC_UNIT;             \
                iter = iter.next;                  \
            }                                      \
        })
/* other_names */
#       define nc_list1_t(tname) nc_list1_main_t(tname)
#       define NC_TYPEDEF_LIST1(tname)    \
            NC_TYPEDEF_LIST1_ITER(tname); \
            NC_TYPEDEF_LIST1_MAIN(tname); \
/* type is defined */
#       if (NC_LANG & NC_LANG_CPP)
}
#       endif   /* NC_LANG_CPP */
#	endif   /* NC_API */
/* end_of_file */
#endif /* NC_LIB_LIST1_HXX */