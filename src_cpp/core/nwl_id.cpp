#include <nwl_pch.hpp>
#include "nwl_id.h"

namespace NW
{
	id_stack::id_stack(v1ui first_id) :
		std::stack<v1ui>()
	{
		push(first_id);
	}
	// --setters
	void id_stack::set_id(v1ui free_id) {
		if (free_id != top()) { push(free_id); }
	}
}
namespace NW
{
	a_id_owner::a_id_owner() { }
	a_id_owner::~a_id_owner() { }
}