#include "nc_lib_pch.h"
#include "nc_lib.h"

#if (defined NC_BUILD)
#   if (NC_BUILD & NC_BUILD_EXE || NC_TRUTH)

NC_TYPEDEF_ARRAY(v1u_t);
NC_TYPEDEF_LIST1(v1u_t);
NC_TYPEDEF_TABLE(v1u_t);

int main(int arg_num, const char* arg_str[])
{

    NC_OLOG(NC_GREETING);
#   if (NC_FALSE)
    nc_array_t(v1u_t) array;
    nc_array_ctor(v1u_t, array);
    nc_array_set_numb(v1u_t, array, 10u);
    nc_array_olog(v1u_t, array);
    nc_array_each(v1u_t, array,
        {
            size_t dist;
            nc_array_get_dist(v1u_t, array.head, each, dist);
            nc_array_set_elem(v1u_t, array, indx, indx);
        }
    );
    nc_array_olog(v1u_t, array);
    nc_array_set_numb(v1u_t, array, 3u);
    nc_array_olog(v1u_t, array);
    nc_array_dtor(v1u_t, array);
#   endif
#   if (NC_FALSE)
    nc_list1_t(v1u_t) list1;
    nc_list1_ctor(v1u_t, list1);
    nc_list1_olog(v1u_t, list1);
    nc_list1_add_iter(v1u_t, list1, list1.head);
    nc_list1_add_iter(v1u_t, list1, list1.head);
    nc_list1_add_iter(v1u_t, list1, list1.head);
    nc_list1_add_iter(v1u_t, list1, list1.head);
    nc_list1_olog(v1u_t, list1);
    nc_list1_set_elem(v1u_t, list1, 0u, 1u);
    nc_list1_set_elem(v1u_t, list1, 1u, 2u);
    nc_list1_set_elem(v1u_t, list1, 2u, 3u);
    nc_list1_set_elem(v1u_t, list1, 3u, 4u);
    nc_list1_olog(v1u_t, list1);
    nc_list1_dtor(v1u_t, list1);
#   endif
#   if (NC_FALSE)
    nc_table_t(v1u_t) table;
    nc_table_ctor(v1u_t, table);
    nc_table_olog(v1u_t, table);
    nc_table_set_elem(v1u_t, table, "00", 0b00u);
    nc_table_set_elem(v1u_t, table, "01", 0b01u);
    nc_table_set_elem(v1u_t, table, "02", 0b10u);
    nc_table_set_elem(v1u_t, table, "03", 0b11u);
    nc_table_set_elem(v1u_t, table, "fsd", 0b00u);
    nc_table_set_elem(v1u_t, table, "fas", 0b01u);
    nc_table_set_elem(v1u_t, table, "hsd", 0b10u);
    nc_table_set_elem(v1u_t, table, "gdd", 0b11u);
    nc_table_olog(v1u_t, table);
    nc_table_iter_t(v1u_t) iter;
    nc_table_get_iter(v1u_t, table, "03", iter);
    NC_OLOG("table[%d] = {%d};", iter.hash, iter.data);
    nc_table_get_iter(v1u_t, table, "hsd", iter);
    NC_OLOG("table[%d] = {%d};", iter.hash, iter.data);
    nc_table_dtor(v1u_t, table);
#   endif
#   if (NC_TRUTH)
    struct nc_mem_arena_t giver = { NC_ZERO };
    nc_mem_arena_ctor(giver);
    ptr_t data;
    nc_mem_arena_set(giver, NC_MEM_USE_SIZE_FULL);
    nc_mem_arena_new_one(v1u_t, giver, data);
    nc_mem_arena_del_one(v1u_t, giver, data);
    nc_mem_arena_dtor(giver);
#   endif
    NC_BREAK();
    return 0;
}
#   endif   // NC_BUILD_EXE //
#endif  // NC_BUILD //
// end_of_file //