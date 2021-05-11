#ifndef NC_LIB_ARRAY_HPP
#	define NC_LIB_ARRAY_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#       include <vector>
// types //
template <typename tval> using nc_array_tt = std::vector<tval>;
template <typename tval> using nc_array_ttc = const nc_array_tt<tval>;
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_ARRAY_HPP //