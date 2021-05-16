#ifndef NC_LIB_ARRAY_H
#	define NC_LIB_ARRAY_H
#	include "../nc_lib_core.h"
#	if (defined NC_API)
#		if !(defined NC_DEFAULT_NUMB_ARRAY)
#			define NC_MINIMAL_NUMB_ARRAY 0u
#			define NC_AVERAGE_NUMB_ARRAY 3u
#			define NC_MAXIMAL_NUMB_ARRAY 10u
#			define NC_DEFAULT_NUMB_ARRAY NC_MINIMAL_NUMB_ARRAY
#		endif	// NC_DEFAULT_NUMB_ARRAY //
/// array_iter_type
#       define nc_array_iter_t(tname) nc_array_iter##_##tname
#       if (NC_FALSE)
#       define NC_TYPEDEF_ARRAY_ITER(tname) /*iter type*/ \
            typedef struct /*forward declaration_______*/ \
                nc_array_iter_t(name) /*base name______*/ \
                nc_array_iter_t(name); /*same thing____*/ \
            typedef struct nc_array_iter_t(tname) { /*_*/ \
                tname* data; /*value address___________*/ \
            } nc_array_iter_t(tname); /*template name__*/ \
// type is defined //
#       endif
#       define NC_TYPEDEF_ARRAY_ITER(tname) /*iter type*/ \
            typedef tname* nc_array_iter_t(tname);
// type is defined //
/// array_main_type
/// description:
/// ->random-access-memory array;
#       define nc_array_main_t(tname) nc_array_main##_##tname
#       define NC_TYPEDEF_ARRAY_MAIN(tname) /*main type*/ \
            typedef struct /*forward declaration_______*/ \
                nc_array_main_t(tname)  /*base name____*/ \
                nc_array_main_t(tname); /*same as above*/ \
            typedef struct nc_array_main_t(tname) { /*_*/ \
                nc_array_iter_t(tname) head; /*elem beg*/ \
                nc_array_iter_t(tname) back; /*elem end*/ \
            } nc_array_main_t(tname); /*template name__*/ \
// type is defined //
// ctor_dtor //
#       define nc_array_ctor(tname, ref) ({ /*_________________*/ \
            memset(&ref, NC_ZERO, sizeof(ref)); /*_____________*/ \
            nc_array_set_numb(tname, ref, NC_DEFAULT_NUMB_ARRAY); \
        })
#       define nc_array_dtor(tname, ref) ({ /*_________________*/ \
            nc_array_set_numb(tname, ref, NC_ZERO); /*_________*/ \
            memset(&ref, NC_ZERO, sizeof(ref)); /*_____________*/ \
        })
// getters //
#       define nc_array_get_numb(tname, ref, numb) ({ \
            numb = ref.back - ref.head;               \
        })
#       define nc_array_get_size(tname, ref, size) ({ \
			size = sizeof(tname);                     \
			size *= (ref.back - ref.head);            \
        })
#       define nc_array_get_iter(tname, ref, indx, iter) ({ \
            iter = &ref.head[indx];                         \
        })
#       define nc_array_get_elem(tname, ref, indx, elem) ({ \
            elem = ref.head[indx];                          \
        })
#       define nc_array_get_dist(tname, iter0, iter1, dist) ({ \
            dist = (iter1 - iter0);                            \
        })
// setters //
#       define nc_array_set_numb(tname, ref, numb) ({ \
            size_t sz_old, sz_new;                    \
            sz_old = sizeof(tname);                   \
            sz_old *= (ref.back - ref.head);          \
            sz_new = sizeof(tname);                   \
            sz_new *= numb;                           \
            NC_MEM_MOVE(ref.head, sz_old, sz_new);    \
            ref.back = ref.head + numb;               \
        })
#       define nc_array_set_elem(tname, ref, indx, elem) ({ \
            ref.head[indx] = elem;                          \
        })
#		define nc_array_add_elem(tname, ref) ({  \
			size_t numb;                         \
            nc_array_get_numb(tname, ref, numb); \
            numb += 1u;                          \
			nc_array_set_numb(tname, ref, numb); \
        })
#       define nc_array_rmv_elem(tname, ref) ({  \
			size_t numb;                         \
            nc_array_get_numb(tname, ref, numb); \
            numb -= 1u;                          \
			nc_array_set_numb(tname, ref, numb); \
        })
// commands //
#       define nc_array_each(tname, ref, actn) ({   \
            nc_array_iter_t(tname) each = ref.head; \
            size_t indx = NC_ZERO;                  \
            while(each < ref.back) {                \
                actn; indx++; each++;               \
            }                                       \
        })
#		define nc_array_oput(tname, ref) ({   \
			NC_OPUT("{");                     \
			nc_array_each(tname, ref, {       \
                    NC_OPUT(                  \
                        "{indx:%d;data:%d;};" \
                        , indx, *each         \
                    );                        \
				}                             \
			);                                \
			NC_OPUT("};");                    \
		})
#		define nc_array_olog(tname, ref) ({    \
			NC_OLOG(                           \
                "array:" "{" NC_STR_EOL        \
                "   numb: %d;" NC_STR_EOL      \
                "   data:" "{"                 \
                , ref.back - ref.head          \
            );                                 \
			nc_array_each(tname, ref, {        \
                    NC_OPUT(                   \
                    "   {indx:%d;data:%d};"    \
                        NC_STR_EOL             \
                        , indx, *each          \
                    );                         \
				}                              \
			);                                 \
			NC_OPUT("   };" NC_STR_EOL);       \
			NC_OPUT("};" NC_STR_EOL);          \
		})
// other_names //
#       define nc_array_t(tname) nc_array_main_t(tname)
#       define NC_TYPEDEF_ARRAY(tname)    \
            NC_TYPEDEF_ARRAY_ITER(tname); \
            NC_TYPEDEF_ARRAY_MAIN(tname); \
// type is defined //
#	endif   // NC_API //
// end_of_file //
#endif	// NC_LIB_ARRAY_H //