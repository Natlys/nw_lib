#ifndef NC_LIB_TABLE_HPP
#	define NC_LIB_TABLE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#       include <map>
#       include <unordered_map>
#       include <set>
#       include <unordered_set>
// types //
template <typename tkey, typename tval> using nc_table_t = std::unordered_map<tkey, tval>;
template <typename tkey, typename tval> using nc_table_tc = const nc_table_t<tkey, tval>;
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_TABLE_HPP //