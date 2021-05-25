#ifndef NC_LIB_LIST1_HPP
#	define NC_LIB_LIST1_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/// list1_iterator_type_template
template<typename tdata>
class nc_list1_iter_t
{
	using iter_t = nc_link1_iter_t<tdata>;
	using iter_tc = const iter_t;
	using data_t = tdata;
	using data_tc = const data_t;
public:
	// ctor_dtor //
	constexpr inline nc_list1_t() : m_next(NC_NULL), m_data(NC_NULL) { }
	inline ~nc_list1_t() { }
	/* getters */
	inline iter_t* get_next()        { return m_next; }
	inline iter_tc* get_next() const { return m_next; }
	inline data_t* get_data()        { return m_data; }
	inline data_tc* get_data() const { return m_data; }
	/* setters */
	inline iter_t& set_next(iter_t* next) { m_next = next; return *this; }
	inline iter_t& set_data(data_t* data) { NC_MEM_DEL_ONE(tdata, m_data); m_data = data; return *this; }
	/* predicates */
	/* commands */
	/* operators */
public:
	iter_t* m_next;
	data_t* m_data;
};
// other names //
#	endif   /* NC_API */
/* end_of_file */
#endif // NC_LIB_LIST1_HPP //