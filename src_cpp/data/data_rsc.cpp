#include <nwl_pch.hpp>
#include "data_rsc.h"
#include "data_sys.h"
namespace NW
{
	a_data_rsc::a_data_rsc()
	{
	}
	a_data_rsc::~a_data_rsc() { }
	// --setters
	// --operators
	stm_out& a_data_rsc::operator<<(stm_out& stm) const {
		return stm << "empty resource;";
	}
	stm_out& operator<<(stm_out& stm, const a_data_rsc& rsc) { return rsc.operator<<(stm); }
	stm_in& a_data_rsc::operator>>(stm_in& stm) {
		return stm;
	}
	stm_in& operator>>(stm_in& stm, a_data_rsc& rsc) { return rsc.operator>>(stm); }
	// --==<core_methods>==--
	// --==</core_methods>==--
}