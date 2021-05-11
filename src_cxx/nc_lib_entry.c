#include "nc_lib_pch.h"
#include "nc_lib.h"

#if (defined NC_BUILD)
#   if (NC_BUILD & NC_BUILD_EXE)
int main(int arg_num, const char* arg_str[])
{
    printf(NC_GREETING);
    system("pause");
    return 0;
}
#   endif   // NC_BUILD_EXE //
#endif  // NC_BUILD //
// end_of_file //