#ifndef NC_LIB_LIST1_H
#	define NC_LIB_LIST1_H
#	include "../nc_lib_core.h"
#	if (defined NC_API)
#		if !(defined NC_DEFAULT_NUMB_LIST1)
#			define NC_MINIMAL_NUMB_LIST1 0u
#			define NC_AVERAGE_NUMB_LIST1 3u
#			define NC_MAXIMAL_NUMB_LIST1 10u
#			define NC_DEFAULT_NUMB_LIST1 NC_MINIMAL_NUMB_LIST1
#		endif	// NC_DEFAULT_NUMB_LIST1 //
/// list1_iterator_type
/// description:
/// ->one-linked list iterator;
#       define nc_list1_iter_t(tname) nc_list1_iter##_##tname
#       define NC_TYPEDEF_LIST1_ITER(tname) /*iterator type__*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list1_iter_t(tname)  /*base name__________*/ \
                nc_list1_iter_t(tname); /*same as above______*/ \
            typedef struct nc_list1_iter_t(tname) { /*name___*/ \
                nc_list1_iter_t(tname)* next; /*next link____*/ \
                tname data; /*the actual data________________*/ \
            } nc_list1_iter_t(tname); /*template name________*/ \
// type is defined //
/// list1_main_type
/// description:
/// ->one-linked forward list;
/// ->can grow linearly in front;
/// ->has own iterator type;
/// ->uses 2 iterators as begin-end pointers;
#       define nc_list1_main_t(tname) nc_list1_main##_##tname
#       define NC_TYPEDEF_LIST1_MAIN(tname) /*main type______*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_list1_main_t(tname)  /*base name__________*/ \
                nc_list1_main_t(tname); /*same as above______*/ \
            typedef struct nc_list1_main_t(tname) { /*name___*/ \
                nc_list1_iter_t(tname)* head; /*first link___*/ \
            } nc_list1_main_t(tname); /*template name________*/ \
// type is defined //
// ctor_dtor //
#       define nc_list1_ctor(tname, ref) ({ \
            ref.head = NC_NULL;             \
        })
#       define nc_list1_dtor(tname, ref) ({              \
            while(ref.head != NC_NULL) {                 \
                nc_list1_rmv_iter(tname, ref, ref.head); \
            }                                            \
        })
// getters //
#       define nc_list1_get_numb(tname, ref, numb) ({ \
            nc_list1_iter_t(tname)* iter = ref.head;  \
            numb = NC_ZERO;                           \
            while (iter != NC_NULL) {                 \
                iter = iter->next;                    \
                numb = numb + 1u;                     \
            }                                         \
        })
#       define nc_list1_get_iter(tname, ref, indx, iter) ({ \
            size_t numb = NC_ZERO;                          \
            iter = ref.head;                                \
            while (numb < indx) {                           \
                iter = iter->next;                          \
                numb = numb + 1u;                           \
            }                                               \
        })
// setters //
#       define nc_list1_set_elem(tname, ref, indx, elem) ({ \
            nc_list1_iter_t(tname)* temp = ref.head;        \
            size_t numb = NC_ZERO;                          \
            while(numb < indx) {                            \
                temp = temp->next;                          \
                numb = numb + 1u;                           \
            }                                               \
            temp->data = elem;                              \
        })
#       define nc_list1_add_iter(tname, ref, iter) ({     \
            nc_list1_iter_t(tname)* temp = ref.head;      \
            while (temp != iter) { /*check if exists*/    \
                temp = temp->next;                        \
                NC_CHECK(                                 \
                    temp != NC_NULL,                      \
                    "iter error!", break                  \
                );                                        \
            } /*the iterator is found*/                   \
            nc_list1_iter_t(tname)* next;                 \
            size_t size = sizeof(nc_list1_iter_t(tname)); \
            NC_MEM_TAKE(next, size); /*create new node*/  \
            if (ref.head != NC_NULL) {                    \
                next->next = iter->next;                  \
                temp->next = next;                        \
            } else { /*set it as a head*/                 \
                ref.head = next;                          \
            }                                             \
        })
#       define nc_list1_rmv_iter(tname, ref, iter) ({ \
            nc_list1_iter_t(tname)* temp = ref.head;  \
            if ((iter == temp) && temp) {             \
                ref.head = ref.head->next;            \
                NC_MEM_FREE(temp, sizeof(*temp));     \
            } else if (iter != temp && temp) {        \
                nc_list1_iter_t(tname)* prev;         \
                while (temp != iter) {                \
                    prev = temp; temp = temp->next;   \
                    NC_CHECK(                         \
                        temp != NC_NULL,              \
                        "iter error!", break          \
                    );                                \
                } /*the iterator is found*/           \
                prev->next = temp->next;              \
                NC_MEM_FREE(temp, sizeof(*temp));     \
            }                                         \
        })
// commands //
#       define nc_list1_each(tname, ref, actn) ({    \
            nc_list1_iter_t(tname)* each = ref.head; \
            indx_t indx = NC_ZERO;                   \
            while (each != NC_NULL) {                \
                actn; indx++; each = each->next;     \
            }                                        \
        })
#       define nc_list1_oput(tname, ref) ({ \
            \
        })
#       define nc_list1_olog(tname, ref) ({      \
            size_t numb = NC_ZERO;               \
            nc_list1_get_numb(tname, ref, numb); \
            NC_OLOG(                             \
                "list1:" "{" NC_STR_EOL          \
                "   numb:%d;" NC_STR_EOL         \
                "   data:{"                      \
                , numb                           \
            );                                   \
            nc_list1_each(tname, ref, {          \
                NC_OPUT(                         \
                    "   {indx:%d;data:%d;}"      \
                    NC_STR_EOL                   \
                    , indx, each->data           \
                );                               \
            });                                  \
            NC_OPUT("   };" NC_STR_EOL);         \
            NC_OPUT("};" NC_STR_EOL);            \
        })
#       define nc_list1_move(tname, iter, numb) ({ \
            size_t indx = NC_ZERO;                 \
            while(indx < numb) {                   \
                indx = indx + 1u;                  \
                iter = iter.next;                  \
            }                                      \
        })
// other_names //
#       define nc_list1_t(tname) nc_list1_main_t(tname)
#       define NC_TYPEDEF_LIST1(tname)    \
            NC_TYPEDEF_LIST1_ITER(tname); \
            NC_TYPEDEF_LIST1_MAIN(tname); \
// type is defined //
#	endif   // NC_API //
// end_of_file //
#endif // NC_LIB_LIST1_H //