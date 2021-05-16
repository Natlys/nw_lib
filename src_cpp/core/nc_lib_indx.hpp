#ifndef NC_LIB_INDEX_HPP
#	define NC_LIB_INDEX_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "../std/nc_lib_stack.hpp"
#		include "../std/nc_lib_array.hpp"
// types //
/// index_stack_type
/// description:
/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
/// --contains one single id for any class;
/// --you can get new id during construction of and object and put it back into the stack;
/// --if any destroyed instance gives back own id to the stack - there is no loss;
class nc_indx_stack_t
{
public:
	using stack_t = nc_indx_stack_t;
	using indx_t = v1u_t;
	using indx_tc = const indx_t;
public:
	// ctor_dtor //
	inline nc_indx_stack_t() { m_stack.push(NC_DEFAULT_VAL); }
	inline nc_indx_stack_t(indx_t first) : nc_indx_stack_t() { m_stack.top() = first; }
	inline ~nc_indx_stack_t() = default;
	// getters //
	inline indx_tc get_indx() {
		indx_t indx = m_stack.top();
		if (m_stack.size() == NC_UNIT) { m_stack.top()++; }
		else { m_stack.pop(); }
		return indx;
	}
	// setters //
	inline stack_t& set_indx(indx_t indx) {
		if (indx != m_stack.top()) { m_stack.push(indx); }
		return *this;
	}
	// predicates //
	// commands //
private:
	nc_stack_tt<v1u_t> m_stack;
};
/// index_info_type
class nc_indx_info_t
{
public:
	using indx_t = v1u_t;
	using indx_tc = const indx_t;
	using stack_t = nc_indx_stack_t;
	using stack_tc = const stack_t;
public:
	template<typename tname> static indx_tc get_indx()             { return get_stack<tname>().get_indx(); }
	template<typename tname> static v1nil_t set_indx(indx_tc indx) { get_stack<tname>().set_indx(indx); }
private:
	template<typename tname> static stack_t& get_stack()  { static stack_t s_stack(NC_NULL); return s_stack; }
};
/// index_owner_type
class nc_indx_owner_t
{
public:
	using indx_t = v1u_t;
	using indx_tc = const indx_t;
public:
	// ctor_dtor //
	constexpr inline nc_indx_owner_t() = default;
	virtual inline ~nc_indx_owner_t() = default;
	// getters //
	virtual inline indx_tc get_indx() const = 0;
	// setters //
	// predicates //
	// commands //
	// operators //
};
/// typed_index_owner
template<class tname>
class nc_indx_owner_tt : nc_indx_owner_t
{
public:
	inline nc_indx_owner_tt() : nc_indx_owner_t(), m_indx(nc_indx_info_t::get_indx<tname>()) { }
	virtual inline ~nc_indx_owner_tt() { nc_indx_info_t::set_indx<tname>(m_indx); }
	// getters //
	virtual inline indx_tc get_indx() const override { return m_indx; }
protected:
	indx_t m_indx;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_INDEX_HPP //