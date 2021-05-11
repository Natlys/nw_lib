#ifndef NC_LIB_STACK_HPP
#	define NC_LIB_STACK_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#       include <stack>
// types //
template <typename tval> using stack_t = std::stack<tval>;
template <typename tval> using stack_tc = const stack_t<tval>;
#	endif	// NC_API //
// end_of_file //
#endif // NC_LIB_STACK_HPP //