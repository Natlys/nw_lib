#ifndef NW_ECS_COMPONENT_H
#define NW_ECS_COMPONENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "../mem/nw_mem_sys.h"
#include "../info/nw_info_type_idx.h"
namespace NW
{
	/// abstract component class
	class NW_API a_cmp : public a_type_idx_owner
	{
	protected:
		a_cmp() : a_type_idx_owner() { }
	public:
		virtual ~a_cmp() = default;
	};
}
namespace NW
{
	/// templated component class
	template<class ct>
	class NW_API t_cmp : public t_type_idx_owner<ct, a_cmp>
	{
	protected:
		t_cmp() : t_type_idx_owner() { }
	public:
		virtual ~t_cmp() = default;
	};
}
#endif	// NW_API
#endif	// NW_ECS_COMPONENT_H
