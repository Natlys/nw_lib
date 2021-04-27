#ifndef NW_STD_INDEX_H
#define NW_STD_INDEX_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../std/nw_std_stack.h"
#	include "../std/nw_std_array.h"
namespace NW
{
	/// id_stack class
	/// description:
	/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
	/// --contains one single id for any class;
	/// --you can get new id during construction of and object and put it back into the stack;
	/// --if any destroyed instance gives back own id to the stack - there is no loss;
	class NW_API idx_stack : protected t_stack<v1u>
	{
	public:
		using idx_t = v1u;
		using idx_tc = const idx_t;
	public:
		idx_stack(idx_t first = 1u) : t_stack<idx_t>() { push(first); }
		// -- getters
		inline idx_t get_idx() { idx_t idx = top(); if (size() == 1) { top()++; } else { pop(); } return idx; }
		// -- setters
		inline v1nil set_idx(idx_t idx) { if (idx != top()) { push(idx); } }
	};
}
namespace NW
{
	/// idx_info class
	class NW_API idx_info
	{
	public:
		using idx_t = v1u;
		using idx_tc = const idx_t;
		using stack_t = idx_stack;
		using stack_tc = const stack_t;
	public:
		template<typename tname> static idx_tc get_idx()          { return get_stack<tname>().get_idx(); }
		template<typename tname> static v1nil set_idx(idx_tc idx) { get_stack<tname>().set_idx(idx); }
	private:
		template<typename tname> static stack_t& get_stack()  { static stack_t s_stack(0); return s_stack; }
	};
}
namespace NW
{
	/// abstract idx_owner class
	class NW_API a_idx_owner
	{
	public:
		using idx_t = v1u;
		using idx_tc = const idx_t;
	public:
		a_idx_owner() = default;
		virtual ~a_idx_owner() = default;
		// --getters
		virtual inline idx_tc get_idx() const = 0;
	};
	/// templated idx_owner class
	template<class tname>
	class NW_API t_idx_owner : a_idx_owner
	{
	public:
		using idx_t = v1u;
		using idx_tc = const idx_t;
	public:
		t_idx_owner() : a_idx_owner(), m_idx(idx_info::get_idx<tname>()) { }
		virtual ~t_idx_owner() { idx_info::set_idx<tname>(m_idx); }
		// --getters
		virtual inline idx_tc get_idx() const override { return m_idx; }
	protected:
		idx_t m_idx;
	};
}
#endif	// NW_API
#endif	// NW_STD_INDEX_H