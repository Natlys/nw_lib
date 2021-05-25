#ifndef NC_LIB_FUNCTIONAL_HPP
#	define NC_LIB_FUNCTIONAL_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#       include <functional>
#       define nc_func_tt  std::function
#       define nc_func_ttc const std::function
#	endif	/* NC_API */
/* end_of_file */
#endif	// NC_LIB_FUNCTIONAL_HPP //