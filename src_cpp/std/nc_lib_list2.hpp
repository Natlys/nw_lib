#ifndef NC_LIB_LIST2_HPP
#	define NC_LIB_LIST2_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_LIST2)
#		if (NC_LIST2 & NC_LIST2_STD)
#   		include <list>
#       	define nc_list2_tt     std::list
#       	define nc_list2_ttc    const std::list
//template <typename tval> using nc_list2_tt = std::list<tval>;
//template <typename tval> using nc_list2_ttc = const nc_list2_tt<tval>;
#		endif // NC_LIST2_STD //
template <typename tval>
class nc_list2_tt
{
public:
	using list_t = std::list<tval>;
	using list_tc = const list_t;
	using val_t = tval;
	using val_tc = const val_t;
public:
	inline nc_list2_tt() : m_list(list_t()) { }
	inline nc_list2_tt(list_t& copy) : m_list(list_t()) { }
	inline ~nc_list2_tt() { }
	// getters //
	// setters //
	// predicates //
	// commands //
	// operators //
private:
	list_t m_list;
};
template <typename tval>
using nc_list2_ttc = const nc_list2_tt<tval>;
#		if (NC_LIST2 & NC_LIST2_OWN)
#		endif // NC_LIST2_OWN //
#	endif	// NC_LIST2 //
// end_of_file //
#endif // NC_LIB_LIST2_HPP //