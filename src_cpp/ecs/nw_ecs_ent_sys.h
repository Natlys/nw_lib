#ifndef NW_ECS_ENTITY_SYSTEM_H
#define NW_ECS_ENTITY_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_sing.h"
#include "std/nw_std_cont.h"
#include "mem/nw_mem_ref.h"
#include "info/nw_info_type.h"
#include "nw_ecs_ent.h"
#include "nw_ecs_cmp.h"
#include "nw_ecs_cmp_sys.h"
namespace NW
{
	/// templated entity_system class
	template<class rt>
	class NW_API t_ent_sys
	{
	public:
		using ent_ref = mem_ref<rt>;				// base reference to an abstract entity
		using ent_tab = dictionary<v1u, ent_ref>;	// table of t_id and entity references
		using ent_reg = dictionary<v1u, ent_tab>;	// table of cmp_id and entity containers
		template<class et>
		using ent = mem_ref<et>;					// reference to some typed entity
	protected:
		t_ent_sys() = default;
	public:
		virtual ~t_ent_sys() = default;
		// --getters
		inline ent_reg& get_ent_reg()                     { return m_ent_reg; }
		inline ent_tab& get_ent_tab(v1u t_id)             { return m_ent_reg[t_id]; }
		template<class et> ent_tab& get_ent_tab()         { return get_ent_tab(et::get_type_static()); }
		inline ent_ref& get_ent_ref(v1u t_id, v1u e_id)   { return m_ent_reg[t_id][e_id]; }
		template<class et> ent_ref& get_ent_ref(v1u e_id) { return get_ent_ref(et::get_type_static(), e_id); }
		template<class et> ent<et> get_ent(v1u e_id)      { return ent<et>(get_ent_ref<et>(e_id)); }
		// --predicates
		inline v1b has_ent(v1u t_id, v1u e_id)   { return m_ent_reg[t_id].find(e_id) != m_ent_reg[t_id].end(); }
		template<class et> v1b has_ent(v1u e_id) { return has_ent(et::get_type_static(), e_id); }
	protected:
		ent_reg m_ent_reg;
	};
	/// entity_system singleton class
	class NW_API ent_sys : public singleton_t<ent_sys>, public t_ent_sys<a_ent>
	{
		friend class singleton_t<ent_sys>;
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
		void del_ent(v1u t_id, v1u e_id) {
			if (!has_ent(t_id, e_id)) { return; }
			m_ent_reg[t_id].erase(e_id);
		}
		template<class et>
		void del_ent(v1u e_id) {
			NW_CHECK_TYPE_BASE(a_ent, et);
			del_ent(et::get_type_static(), e_id);
		}
	};
}
#endif	// NW_API
#endif // NW_ECS_ENTITY_SYSTEM_H
