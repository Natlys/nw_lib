#ifndef NC_LIB_STACK_HPP
#	define NC_LIB_STACK_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_STACK)
#       if (NC_STACK & NC_STACK_STD)
#           include <stack>
#           define nc_stack_tt     std::stack
#           define nc_stack_ttc    const std::stack
//template <typename tval> using nc_stack_tt = std::stack<tval>;
//template <typename tval> using nc_stack_ttc = const stack_t<tval>;
#       endif   // NC_STACK_STD //
#       if (NC_STACK & NC_STACK_OWN)
#       endif   // NC_STACK_OWN //
#	endif	// NC_STACK //
// end_of_file //
#endif // NC_LIB_STACK_HPP //