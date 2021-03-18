#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H
#include <nwl_core.hpp>
#include <core/nwl_id.h>
#include <core/nwl_type.h>
#include <mem/mem_ref.h>
namespace NW
{
	/// abstract component class
	class NW_API a_cmp : public a_type_owner
	{
	protected:
		a_cmp();
		a_cmp(const a_cmp& copy) = delete;
	public:
		virtual ~a_cmp();
		// --getters
		virtual inline ui32 get_type_id() const = 0;
		virtual inline ui32 get_cmp_id() const = 0;
		// --operators
		inline void operator=(const a_cmp& copy) = delete;
	};
}
namespace NW
{
	/// templated component class
	template <class ctype, class actype = a_cmp>
	class NW_API t_cmp : public actype
	{
	protected:
		template<typename ... args>
		t_cmp(args&& ... arguments) :
			actype(std::forward<args>(arguments)...),
			m_cmp_id(id_indexator::get_id<ctype>())
		{
		}
	public:
		virtual ~t_cmp()
		{
			id_indexator::set_id<ctype>(m_cmp_id);
		}
		// --getters
		static inline ui32 get_type_id_static()				{ return type_indexator::get_id<ctype>(); }
		virtual inline ui32 get_type_id() const override	{ return type_indexator::get_id<ctype>(); }
		virtual inline ui32 get_cmp_id() const override		{ return m_cmp_id; }
	protected:
		const ui32 m_cmp_id;
	private:
		//static id_stack& get_id_stack() { static id_stack s_id_stack(1); return s_id_stack; }
	};
}
#endif	// NWL_ECS_COMPONENT_H