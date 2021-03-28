#ifndef NWLIB_ECS_COMPONENT_H
#define NWLIB_ECS_COMPONENT_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "std/nwlib_std_id.h"
#include "std/nwlib_std_type.h"
#include "std/nwlib_std_type_id.h"
#include "mem/nwlib_mem_sys.h"
namespace NWLIB
{
	/// abstract component class
	class NW_API a_cmp : public a_type_id_owner, public a_mem_user
	{
	protected:
		a_cmp() : a_type_id_owner(), a_mem_user() { }
	public:
		virtual ~a_cmp() = default;
	};
}
namespace NWLIB
{
	/// templated component class
	template<class ct>
	class NW_API t_cmp : public t_type_id_owner<ct, a_cmp>
	{
	protected:
		t_cmp() : t_type_id_owner() { }
	public:
		virtual ~t_cmp() = default;
	};
}
#endif	// NW_API
#endif	// NWLIB_ECS_COMPONENT_H