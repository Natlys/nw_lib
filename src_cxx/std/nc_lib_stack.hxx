#ifndef NC_LIB_STACK_H
#	define NC_LIB_STACK_H
#	include "../nc_lib_core.hxx"
#	if (defined NC_API)
#		if !(defined NC_USE_NUMB_STACK)
#			define NC_MIN_NUMB_STACK 0x000u // empty stack //
#			define NC_MID_NUMB_STACK 0x010u // normal stack //
#			define NC_MAX_NUMB_STACK 0x100u // stack overflow //
#			define NC_USE_NUMB_STACK NC_MIN_NUMB_STACK
#		endif	// NC_USE_NUMB_STACK //
/// stack_iterator_type
/// description:
#       define nc_stack_iter_t(tname) nc_stack_iter##_##tname
#       define NC_TYPEDEF_STACK_ITER(tname) /*iterator type__*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_stack_iter_t(tname)  /*base name__________*/ \
                nc_stack_iter_t(tname); /*same as above______*/ \
            typedef struct nc_stack_iter_t(tname) { /*name___*/ \
                nc_stack_iter_t(tname)* next; /*next link____*/ \
                tname data; /*the actual data________________*/ \
            } nc_stack_iter_t(tname); /*template name________*/ \
// type is defined //
/// stack_main_type
/// description:
#       define nc_stack_main_t(tname) nc_stack_main##_##tname
#       define NC_TYPEDEF_STACK_MAIN(tname) /*main type______*/ \
            typedef struct /*forward declaration for pointers*/ \
                nc_stack_main_t(tname)  /*base name__________*/ \
                nc_stack_main_t(tname); /*same as above______*/ \
            typedef struct nc_stack_main_t(tname) { /*name___*/ \
                nc_stack_iter_t(tname)* head; /*topic value__*/ \
                size_t numb; /*total count of values_________*/ \
            } nc_stack_main_t(tname); /*template name________*/ \
// type is defined //
// ctor_dtor //
#       define nc_stack_ctor(tname, ref) ({           \
            ref.head = NC_NULL;                       \
            ref.numb = NC_ZERO;                       \
            while(ref.numb < NC_USE_NUMB_STACK) { \
                nc_stack_add(tname, ref);             \
                nc_stack_set(tname, ref, ref.numb);   \
            }                                         \
        })
#       define nc_stack_dtor(tname, ref) ({ \
            while(ref.head) {               \
                nc_stack_rmv(tname, ref);   \
            }                               \
            ref.head = NC_NULL;             \
            ref.numb = NC_ZERO;             \
        })
/* getters */
#       define nc_stack_get(tname, ref, elem) ({ \
            elem = ref.head->data;               \
        })
/* setters */
#       define nc_stack_set(tname, ref, elem) ({ \
            ref.head->data = elem;               \
        })
#       define nc_stack_add(tname, ref) ({           \
            if (ref.numb >= NC_MAX_NUMB_STACK) { \
                NC_ERROR("size error!", NC_VOID); \
            }                                        \
            nc_stack_iter_t(tname)* temp;            \
            temp = ref.head;                         \
            size_t size;                             \
            size = sizeof(nc_stack_iter_t(tname));   \
            NC_MEM_TAKE(ref.head, size);             \
            ref.head->next = temp;                   \
            ref.numb = ref.numb + 1u;                \
        })
#       define nc_stack_rmv(tname, ref) ({           \
            if (ref.numb <= NC_MIN_NUMB_STACK) { \
                NC_ERROR("size error!", NC_VOID); \
            }                                        \
            nc_stack_iter_t(tname)* temp;            \
            temp = ref.head->next;                   \
            size_t size;                             \
            size = sizeof(nc_stack_iter_t(tname));   \
            NC_MEM_FREE(ref.head, size);             \
            ref.head = temp;                         \
            ref.numb = ref.numb - 1u;                \
        })
/* commands */
#       define nc_stack_oput(tname, ref) ({  \
            NC_OPUT(                         \
                "{"                          \
                "numb:%d;"                   \
                "data:%d"                    \
                "};"                         \
                , ref.numb,                  \
                ref.head ?                   \
                    ref.head->data : NC_ZERO \
            );                               \
        })
#       define nc_stack_olog(tname, ref) ({  \
            NC_OLOG(                         \
                "stack:" "{" NC_EOL          \
                NC_TAB "numb:%d;" NC_EOL     \
                NC_TAB "data:%d" NC_EOL      \
                "};"                         \
                , ref.numb,                  \
                ref.head ?                   \
                    ref.head->data : NC_ZERO \
            );                               \
        })
// other_names //
#       define nc_stack_t(tname) nc_stack_main_t(tname)
#       define NC_TYPEDEF_STACK(tname)    \
            NC_TYPEDEF_STACK_ITER(tname); \
            NC_TYPEDEF_STACK_MAIN(tname); \
// type is defined //
#	endif   /* NC_API */
/* end_of_file */
#endif // NC_LIB_STACK_H //