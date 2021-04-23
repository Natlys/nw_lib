#include "nw_lib_pch.hpp"
#include "nw_info_name.h"
#if (defined NW_API)
namespace NW
{
	a_name_owner::a_name_owner() : m_name("") { }
	a_name_owner::a_name_owner(cstr_t name) : m_name(name) { }
	a_name_owner::a_name_owner(owner_tc& copy) : m_name(copy.m_name) { }
	a_name_owner::a_name_owner(owner_t&& copy) : m_name(copy.m_name) { }
	// --setters
	v1nil a_name_owner::set_name(cstr_t name) { m_name = name; }
}
#endif	// NW_API