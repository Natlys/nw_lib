#ifndef NC_LIB_FUNCTIONAL_HPP
#	define NC_LIB_FUNCTIONAL_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#       include <functional>
// types //
template <typename ... args> using functor_tt = std::function<args...>;
template <typename ... args> using functor_ttc = const functor_t<args...>;
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_FUNCTIONAL_HPP //