#ifndef NC_LIB_FUNCTIONAL_HPP
#	define NC_LIB_FUNCTIONAL_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_FUNC)
#       if (NC_FUNC & NC_FUNC_STD)
#           include <functional>
#           define nc_func_tt  std::function
#           define nc_func_ttc const std::function
//template<typename...targs> using nc_func_tt = std::function<targs...>;
//template<typename...targs> using nc_func_ttc = const std::function<targs...>;
#       endif   // NC_FUNC_STD //
#       if (NC_FUNC & NC_FUNC_OWN)
#       endif   // NC_FUNC_OWN //
#	endif	// NC_FUNC //
// end_of_file //
#endif	// NC_LIB_FUNCTIONAL_HPP //