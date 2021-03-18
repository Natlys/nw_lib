#include <nwl_pch.hpp>
#include "data_rsc.h"
namespace NW
{
	a_data_rsc::a_data_rsc(cstr name) :
		m_name(name) { }
	a_data_rsc::~a_data_rsc() { }
	// -- setters
	void a_data_rsc::set_name(cstr name) { m_name = name; }
	// operators
	stm_out& a_data_rsc::operator<<(stm_out& stm) const {
		return stm << m_name << ";";
	}
	stm_in& a_data_rsc::operator>>(stm_in& stm) {
		return stm;
	}

	stm_out& operator<<(stm_out& stm, const a_data_rsc& rsc) { return rsc.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_data_rsc& rsc) { return rsc.operator>>(stm); }
}