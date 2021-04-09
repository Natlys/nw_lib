#include "nw_lib_pch.hpp"
#include "nw_info_type.h"
#	if (defined NW_API)
namespace NW
{
	type_info::type_info(cv1u tid, cstr tname, csize tsize, csize talign) :
		id(tid),
		name(tname),
		size(tsize),
		align(talign)
	{
		get_tab_static().push_back(*this);
	}
	// --operators
	stm_out& type_info::operator<<(stm_out& stm) const {
		return stm << "{"
			<< "id:" << id << ";"
			<< "name:" << name << ";"
			<< "size:" << size << ";"
			<< "align:" << align << ";"
			<< "}";
	}
}
#	endif	// NW_API