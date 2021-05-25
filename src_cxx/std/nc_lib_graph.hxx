#ifndef NC_LIB_GRAPH_H
#   define NC_LIB_GRAPH_H
#   include "../nc_lib_core.hxx"
#   if (defined NC_API)
#       include "nc_lib_util.hxx"
#       include "nc_lib_list1.hxx"
/// graph_iterator_type
/// description:
/// ->poly-linked graph iterator;
#       define nc_graph_iter_t(tkey, tval) nc_graph_iter##_##tkey##_##tval
#       define NC_TYPEDEF_GRAPH_ITER(tkey, tval) /*iterator type___*/ \
            typedef struct /*forward declaration for pointers______*/ \
                nc_graph_iter_t(tkey, tval)  /*base name___________*/ \
                nc_graph_iter_t(tkey, tval); /*same as above_______*/ \
            typedef struct nc_graph_iter##_##tkey##_##tval { /*name*/ \
            } nc_graph_iter##_##tkey##_##tval /*template name______*/ \
// type is defined //
/// graph_main_type
/// description:
#       define nc_graph_main_t(tkey, tval) nc_graph_main##_##tkey##_##tval
#       define NC_TYPEDEF_GRAPH_MAIN(tkey, tval) /*main type_______*/ \
            typedef struct /*forward declaration for pointers______*/ \
                nc_graph_main_t(tkey, tval)  /*base name___________*/ \
                nc_graph_main_t(tkey, tval); /*same as above_______*/ \
            typedef struct nc_graph_main##_##tkey##_##tval { /*name*/ \
            } nc_graph_main##_##tkey##_##tval /*template name______*/ \
// type is defined //
// other names //
#       define nc_graph_t(tkey, tval) nc_graph_main_t(tkey, tval)
#       define NC_TYPEDEF_GRAPH(tkey, tval)   \
            NC_TYPEDEF_GRAPH_MAIN(tkey, tval) \
            NC_TYPEDEF_GRAPH_ITER(tkey, tval) \
// type is defined //
#   endif   /* NC_API */
/* end_of_file */
#endif  // NC_LIB_GRAPH_H //