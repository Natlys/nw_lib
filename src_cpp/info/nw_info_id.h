#ifndef NW_INFO_ID_H
#define NW_INFO_ID_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_cont.h"
namespace NW
{
	/// id_stack class
	/// description:
	/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
	/// --contains one single id for any class;
	/// --you can get new id during construction of and object and put it back into the stack;
	/// --if any destroyed instance gives back own id to the stack - there is no loss;
	class NW_API id_stack : protected dstack<v1u>
	{
	public:
		id_stack(v1u first_id = 1) : dstack<v1u>() { push(first_id); }
		// -- getters
		inline v1u get_id() { v1u free_id = top(); if (size() == 1) { top()++; } else { pop(); } return free_id; }
		// -- setters
		inline void set_id(v1u free_id) { if (free_id != top()) { push(free_id); } }
	};
}
namespace NW
{
	/// id_indexator class
	class NW_API id_indexator
	{
		using stack = id_stack;
	public:
		template<typename it> static v1u get_id()        { return get_stack<it>().get_id(); }
		template<typename it> static void set_id(v1u id) { get_stack<it>().set_id(id); }
	private:
		template<typename it> static stack& get_stack()  { static stack s_stack(0); return s_stack; }
	};
}
namespace NW
{
	/// abstract id_owner class
	class NW_API a_id_owner
	{
	protected:
		a_id_owner() = default;
	public:
		virtual ~a_id_owner() = default;
		// --getters
		virtual inline cv1u get_id() const = 0;
	};
	/// templated id_owner class
	template<class type>
	class NW_API t_id_owner : a_id_owner
	{
	protected:
		t_id_owner() : a_id_owner(), m_id(id_indexator::get_id<type>()) { }
	public:
		virtual ~t_id_owner() { id_indexator::set_id<type>(m_id); }
		// --getters
		virtual inline cv1u get_id() const override { return m_id; }
	protected:
		v1u m_id;
	};
}
#endif	// NW_API
#endif	// NW_INFO_ID_H