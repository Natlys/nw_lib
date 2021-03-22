#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H
#include <nwl_core.hpp>
#include <core/nwl_id.h>
#include <core/nwl_type.h>
#include <mem/mem_ref.h>
namespace NW
{
	/// abstract component class
	class NW_API a_cmp : public a_type_owner, public a_id_owner
	{
	protected:
		a_cmp();
		a_cmp(const a_cmp& copy) = delete;
	public:
		virtual ~a_cmp();
		// --getters
		virtual inline ui32 get_type() const = 0;
		virtual inline ui32 get_id() const = 0;
		// --operators
		inline void operator=(const a_cmp& copy) = delete;
	};
}
namespace NW
{
	/// templated component class
	template <class ctype, class actype = a_cmp>
	class NW_API t_cmp : public t_type_owner<ctype, actype>, t_id_owner<ctype>
	{
	protected:
		template<typename ... args>
		t_cmp(args&& ... arguments) : t_type_owner(std::forward<args>(arguments)...) { }
	public:
		virtual ~t_cmp() = default;
	};
}
#endif	// NWL_ECS_COMPONENT_H