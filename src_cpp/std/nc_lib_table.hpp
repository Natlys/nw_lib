#ifndef NC_LIB_TABLE_HPP
#	define NC_LIB_TABLE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_TABLE)
#	    if (NC_TABLE & NC_TABLE_STD)
#           include <map>
#           include <unordered_map>
#           define nc_table_tt     std::unordered_map
#           define nc_table_ttc    const std::unordered_map
//template <typename tkey, typename tval> using nc_table_tt = std::unordered_map<tkey, tval>;
//template <typename tkey, typename tval> using nc_table_ttc = const nc_table_tt<tkey, tval>;
#       endif   // NC_TABLE_STD //
#	    if (NC_TABLE & NC_TABLE_OWN)
#       endif   // NC_TABLE_OWN //
#	endif	// NC_TABLE //
// end_of_file //
#endif	// NC_LIB_TABLE_HPP //