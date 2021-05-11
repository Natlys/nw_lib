#ifndef NC_LIB_INDEX_HPP
#	define NC_LIB_INDEX_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "nc_lib_stack.h"
#		include "nc_lib_array.h"
// types //
/// index_stack_type
/// description:
/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
/// --contains one single id for any class;
/// --you can get new id during construction of and object and put it back into the stack;
/// --if any destroyed instance gives back own id to the stack - there is no loss;
class NC_API indx_stack_t : protected stack_t<v1u_t>
{
public:
	using indx_t = v1u_t;
	using indx_tc = const idx_t;
public:
	// ctor_dtor //
	inline indx_stack_t(indx_t first = 1u) : stack_t<idx_t>() { push(first); }
	// getters //
	inline indx_tc get_indx() { idx_t indx = top(); if (size() == 1) { top()++; } else { pop(); } return indx; }
	// setters //
	inline v1nil_t set_indx(indx_t indx) { if (indx != top()) { push(indx); } }
	// predicates //
	// commands //
private:
};
/// index_info_type
class NC_API indx_info_t
{
public:
	using indx_t = v1u_t;
	using indx_tc = const indx_t;
	using stack_t = indx_stack_t;
	using stack_tc = const stack_t;
public:
	template<typename tname> static indx_tc get_indx()             { return get_stack<tname>().get_indx(); }
	template<typename tname> static v1nil_t set_indx(indx_tc indx) { get_stack<tname>().set_indx(indx); }
private:
	template<typename tname> static stack_t& get_stack()  { static stack_t s_stack(NC_NULL); return s_stack; }
};
/// index_owner_type
class NC_API nc_indx_owner_t
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
	inline nc_indx_owner_tt() : nc_indx_owner_t(), m_indx(idx_info_t::get_indx<tname>()) { }
	virtual inline ~nc_indx_owner_tt() { indx_info_t::set_indx<tname>(m_indx); }
	// getters //
	virtual inline indx_tc get_indx() const override { return m_indx; }
protected:
	indx_t m_indx;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_INDEX_HPP //