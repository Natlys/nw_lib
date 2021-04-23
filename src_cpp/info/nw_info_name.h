#ifndef NW_INFO_NAME_H
#define NW_INFO_NAME_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	class NW_API a_name_owner
	{
	public:
		using owner_t = a_name_owner;
		using owner_tc = const owner_t;
	public:
		a_name_owner();
		a_name_owner(cstr_t name);
		a_name_owner(owner_tc& copy);
		a_name_owner(owner_t&& copy);
		virtual ~a_name_owner() = default;
		// --getters
		inline cstr_t get_name() const { return &m_name[0]; }
		// --setters
		v1nil set_name(cstr_t name);
		// --predicates
		inline v1bit has_name(cstr_t name) const { return name == NW_NULL ? (m_name != "") : (m_name == name); }
		// --operators
		inline v1nil operator=(owner_tc& copy) { set_name(copy.get_name()); }
		inline v1nil operator=(owner_t&& copy) { set_name(copy.get_name()); }
		// --core_methods
	protected:
		dstr_t m_name;
	};
}
#endif	// NW_API
#endif	// NW_INFO_NAME_H