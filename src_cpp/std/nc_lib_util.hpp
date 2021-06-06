#ifndef NC_LIB_UTILITY_HPP
#	define NC_LIB_UTILITY_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
#		include <utility>
/* defines */
/* typedefs */
#		define nc_pair_tt         std::pair
#		define nc_pair_ttc        const std::pair
#		define nc_init_list_tt    std::initializer_list
#		define nc_init_list_ttc   const std::initializer_list
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_UTILITY_HPP */