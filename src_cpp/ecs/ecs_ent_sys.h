#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_sing.h>
#include <core/nwl_cln.h>
#include <core/nwl_type.h>
#include <mem/mem_ref.h>
#include "ecs_ent.h"
#include "ecs_cmp.h"
#include "ecs_cmp_sys.h"
namespace NW
{
	/// templated entity_system class
	template<class rt>
	class NW_API t_ent_sys
	{
	public:
		using ent_ref = mem_ref<rt>;				// base reference to an abstract entity
		using ent_tab = dictionary<ui32, ent_ref>;	// table of t_id and entity references
		using ent_reg = dictionary<ui32, ent_tab>;	// table of cmp_id and entity containers
		template<class et>
		using ent = mem_ref<et>;					// reference to some typed entity
	protected:
		t_ent_sys() = default;
	public:
		virtual ~t_ent_sys() = default;
		// --getters
		inline ent_reg& get_ent_reg()						{ return m_ent_reg; }
		inline ent_tab& get_ent_tab(ui32 t_id)				{ return m_ent_reg[t_id]; }
		template<class et> ent_tab& get_ent_tab()			{ return get_ent_tab(et::get_type_static()); }
		inline ent_ref& get_ent_ref(ui32 t_id, ui32 e_id)	{ return m_ent_reg[t_id][e_id]; }
		template<class et> ent_ref& get_ent_ref(ui32 e_id)	{ return get_ent_ref(et::get_type_static(), e_id); }
		template<class et> ent<et> get_ent(ui32 e_id)		{ return ent<et>(get_ent_ref<et>(e_id)); }
		// --predicates
		inline bit has_ent(ui32 t_id, ui32 e_id)			{ return m_ent_reg[t_id].find(e_id) != m_ent_reg[t_id].end(); }
		template<class et> bit has_ent(ui32 e_id)			{ return has_ent(et::get_type_static(), e_id); }
	protected:
		ent_reg m_ent_reg;
	};
	/// entity_system singleton class
	class NW_API ent_sys : public t_singleton<ent_sys>, public t_ent_sys<a_ent>
	{
		friend class t_singleton<ent_sys>;
	protected:
		ent_sys();
	public:
		~ent_sys();
		// --core_methods
		template<class et, typename ... args>
		mem_ref<et> new_ent(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(a_ent, et);
			mem_ref<et> ref;
			ref.make_ref<et>(std::forward<args>(arguments)...);
			m_ent_reg[ref->get_type()][ref->get_id()].set_ref<et>(ref);
			return ref;
		}
		template<class aet, class et, typename ... args>
		mem_ref<aet> new_ent(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(a_ent, et); NW_CHECK_TYPE_BASE(a_ent, aet);
			mem_ref<aet> ref;
			ref.make_ref<et>(std::forward<args>(arguments)...);
			m_ent_reg[ref->get_type()][ref->get_id()].set_ref<aet>(ref);
			return ref;
		}
		void del_ent(ui32 t_id, ui32 e_id) {
			if (!has_ent(t_id, e_id)) { return; }
			m_ent_reg[t_id].erase(e_id);
		}
		template<class et>
		void del_ent(ui32 e_id) {
			NW_CHECK_TYPE_BASE(a_ent, et);
			del_ent(et::get_type_static(), e_id);
		}
	};
}
#endif // NWL_ECS_ENTITY_SYSTEM_H