#ifndef NWL_ID_H
#define NWL_ID_H
#include <nwl_core.hpp>
namespace NW
{
	/// id_stack class
	/// description:
	/// --it's like a simple stack of unsigned 32-bit integers but for identificators;
	/// --contains one single id for any class;
	/// --you can get new id during construction of and object and put it back into the stack;
	/// --if any destroyed instance gives back own id to the stack - there is no loss;
	class NW_API id_stack : protected std::stack<ui32>
	{
	public:
		id_stack(ui32 first_id = 1);
		// -- getters
		inline ui32 get_id() { ui32 free_id = top(); if (size() == 1) { top()++; } else { pop(); } return free_id; }
		// -- setters
		void set_id(ui32 free_id);
	};
}
namespace NW
{
	/// id_indexator class
	class NW_API id_indexator
	{
		using stack = id_stack;
	public:
		template<typename it> static ui32 get_id()			{ return get_stack<it>().get_id(); }
		template<typename it> static void set_id(ui32 id)	{ get_stack<it>().set_id(id); }
	private:
		template<typename it> static stack& get_stack()		{ static stack s_stack(0); return s_stack; }
	};
}
namespace NW
{
	/// abstract id_owner class
	class NW_API a_id_owner
	{
	protected:
		a_id_owner();
	public:
		virtual ~a_id_owner();
		// --getters
		virtual inline ui32 get_id() const = 0;
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
		virtual inline ui32 get_id() const override	{ return m_id; }
	protected:
		ui32 m_id;
	};
}
#endif	// NWL_ID_H