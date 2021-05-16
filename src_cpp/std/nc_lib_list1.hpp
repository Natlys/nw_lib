#ifndef NC_LIB_LIST1_HPP
#	define NC_LIB_LIST1_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_LIST1)
#		if (NC_LIST1 & NC_LIST_STD)
#		endif   // NC_LINK1_STD //
#		if (NC_LIST1 & NC_LIST_OWN)
/// link_one_type
template<typename tdata>
class nc_link1_t
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
	// setters //
	// predicates //
	// commands //
	// operators //
	inline link_t* operator++(void)        { return m_link; }
	inline link_tc* operator++(void) const { return m_link; }
	inline link_t* operator++(int)         { return m_link; }
	inline link_tc* operator++(int) const  { return m_link; }
	template <typename tname> operator tname* () { return static_cast<tname*>(m_data); }
	template <typename tname> operator const tname* () const { return static_cast<const tname*>(m_data); }
	template <typename tname> operator tname& () { return *static_cast<tname*>(m_data); }
	template <typename tname> operator const tname& () const { return *static_cast<const tname*>(m_data); }
public:
	link_t* m_link;
	data_t* m_data;
};
#		endif   // NC_LINK1_OWN //
#	endif   // NC_API //
// end_of_file //
#endif // NC_LIB_LIST1_HPP //