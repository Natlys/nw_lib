#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H
#include <nwl_core.hpp>
#include <core/nwl_id.h>
#include <core/nwl_type.h>
#include <core/nwl_type_id.h>
#include <mem/mem_ref.h>
namespace NW
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
namespace NW
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
#endif	// NWL_ECS_COMPONENT_H