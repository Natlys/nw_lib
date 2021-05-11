#ifndef NC_LIB_LIST_HPP
#	define NC_LIB_LIST_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#   	include <list>
// types //
#		if (NC_FALSE)
template <typename tval>
class nc_list2_t
{
public:
	using nc_list2_tc = const nc_list2_t<tval>;
	using list_t = std::list<tval>;
	using list_tc = const list_t;
	using val_t = tval;
	using val_tc = const val_t;
public:
	inline nc_list2_t() : m_list(list_t()) { }
	inline nc_list2_t(list_t& copy) : m_list(list_t()) { }
	inline ~nc_list2_t() { }
	// getters //
	// setters //
	// predicates //
	// operators //
	// commands //
private:
	list_t m_list;
};
template <typename tval>
using nc_list2_tc = const nc_list2_t<tval>;
#		endif
#		if (NC_TRUTH)
		/// link_one_type
template<typename tdata>
struct nc_link1_t
{
	using link_t = nc_link1_t<tdata>;
	using link_tc = const link_t;
	using data_t = tdata;
	using data_tc = const data_t;
public:
	// ctor_dtor //
	constexpr inline nc_link1_t() : m_link(NC_NULL), m_data(NC_NULL) { }
	inline ~nc_link1_t() { }
	// getters //
	// operators //
	inline link_t* operator++(void) { return m_link; }
	inline link_tc* operator++(void) const { return m_link; }
	inline link_t* operator++(int) { return m_link; }
	inline link_tc* operator++(int) const { return m_link; }
	template <typename tname> operator tname* () { return static_cast<tname*>(m_data); }
	template <typename tname> operator const tname* () const { return static_cast<const tname*>(m_data); }
	template <typename tname> operator tname& () { return *static_cast<tname*>(m_data); }
	template <typename tname> operator const tname& () const { return *static_cast<const tname*>(m_data); }
public:
	link_t* m_link;
	data_t* m_data;
};
#		endif
template <typename tval> using nc_list2_t = std::list<tval>;
template <typename tval> using nc_list2_tc = const nc_list2_t<tval>;
#	endif	// NC_API //
// end_of_file //
#endif // NC_LIB_LIST_HPP //