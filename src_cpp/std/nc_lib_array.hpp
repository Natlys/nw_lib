#ifndef NC_LIB_ARRAY_HPP
#	define NC_LIB_ARRAY_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_ARRAY)
// defines //
#       if (NC_ARRAY & NC_ARRAY_STD)
#           include <vector>
#           define nc_array_tt     std::vector
#           define nc_array_ttc    const std::vector
//template <typename tval> using nc_array_tt = std::vector<tval>;
//template <typename tval> using nc_array_ttc = const nc_array_tt<tval>;
#       endif   // NC_ARRAY_STD //
#       if (NC_ARRAY & NC_ARRAY_OWN)
#       endif   // NC_ARRAY_OWN //
#	endif	// NC_ARRAY //
// end_of_file //
#endif	// NC_LIB_ARRAY_HPP //