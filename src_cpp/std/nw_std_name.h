#ifndef NW_STD_NAME_H
#define NW_STD_NAME_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	class NW_API a_name_owner
	{
	public:
		using name_t = dstr_t;
		using name_tc = const name_t;
		using owner_t = a_name_owner;
		using owner_tc = const owner_t;
	public:
		inline a_name_owner() : m_name(NW_DEFAULT_STR) { }
		inline a_name_owner(cstr_t name) : m_name(name) { }
		inline a_name_owner(name_tc& name) : m_name(name) { }
		inline a_name_owner(owner_tc& copy) : a_name_owner(copy.get_name()) { }
		inline a_name_owner(owner_t&& copy) : a_name_owner(copy.get_name()) { }
		virtual ~a_name_owner() = default;
		// --getters
		inline cstr_t get_name() const { return &m_name[0]; }
		// --setters
		inline v1nil set_name(cstr_t name)   { m_name = name; }
		inline v1nil set_name(name_tc& name) { m_name = name; }
		// --predicates
		inline v1bit has_name() const              { return m_name != ""; }
		inline v1bit has_name(cstr_t name) const   { return m_name == name; }
		inline v1bit has_name(name_tc& name) const { return m_name == name; }
		// --operators
		inline v1nil operator=(owner_tc& copy) { set_name(copy.get_name()); }
		inline v1nil operator=(owner_t&& copy) { set_name(copy.get_name()); }
		// --core_methods
	protected:
		name_t m_name;
	};
}
#endif	// NW_API
#endif	// NW_INFO_NAME_H