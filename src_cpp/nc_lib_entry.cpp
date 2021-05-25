#include "nc_lib_pch.hpp"
#include "nc_lib.hpp"
#if (defined NC_BUILD)
#   if (NC_BUILD & NC_BUILD_EXE)
int main(int arg_num, const char* arg_str[])
{
    NC_OLOG(NC_GREETING);
#   if (NC_TRUTH)
    nc_array_main_t<v1u_t> array;
    array.remake(10u);
    NC_BREAK();
    array.add_elem(array.get_iter(0u), 0u);
    array.set_elem(array.get_iter(1u), 1u);
    array.set_elem(array.get_iter(2u), 2u);
#   endif
#   if (NC_FALSE)
    v1u_t nums[] = { NC_ZERO, NC_ZERO, NC_ZERO };
    nc_array_iter_t<v1u_t> iter0(nums + 0u);
    nc_array_iter_t<v1u_t> iter1(nums + 1u);
    nc_array_iter_t<v1u_t> iter2(nums + 2u);
    NC_BREAK();
    NC_OLOG("ptr0: %d", iter0.get_data());
    NC_OLOG("ptr1: %d", iter1.get_data());
    NC_OLOG("ptr2: %d", iter2.get_data());
    NC_OLOG("dist_0_1: %d", iter0.get_dist(iter1));
    NC_OLOG("dist_0_2: %d", iter0.get_dist(iter2));
#   endif
    NC_BREAK();
    return 0;
}
#   endif   /* NC_BUILD_EXE */
#endif  /* NC_BUILD */
/* end_of_file */