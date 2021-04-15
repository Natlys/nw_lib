#include "nw_lib_pch.hpp"
#include "nw_info_type.h"
#if (defined NW_API)
namespace NW
{
	type_info::type_info(type_t type, cstr tname, size_t tsize, size_t talign) :
		type(type),
		name(tname),
		size(tsize),
		align(talign)
	{
		get_tab_static().push_back(*this);
	}
	// --operators
	stm_out& type_info::operator<<(stm_out& stm) const {
		return stm << "{"
			<< "type:" << type << ";"
			<< "name:" << name << ";"
			<< "size:" << size << ";"
			<< "align:" << align << ";"
			<< "}";
	}
	stm_in& type_info::operator>>(stm_in& stm)
	{
		schar buf[512];
		stm.getline(buf, 512, '}');
		return stm;
	}
}
namespace NW
{
	v_type_owner::v_type_owner() :
		m_vtype(type_info::get_type<owner_t>())
	{
	}
	v_type_owner::v_type_owner(vtype_tc type) : m_vtype(type)
	{
	}
	v_type_owner::v_type_owner(owner_tc& copy) :
		m_vtype(copy.m_vtype)
	{
	}
	v_type_owner::v_type_owner(owner_t&& copy) :
		m_vtype(copy.m_vtype)
	{
	}
	// --setters
	inline v1nil v_type_owner::set_vtype(vtype_tc type) {
		m_vtype = type;
	}
}
#endif	// NW_API