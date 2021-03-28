#ifndef NW_ECS_COMPONENT_SYSTEM_H
#define NW_ECS_COMPONENT_SYSTEM_H
#include "nwlib_core.hpp"
#include "std/nwlib_std_sing.h"
#include "std/nwlib_std_cont.h"
#include "mem/nwlib_mem_ref.h"
#include "nwlib_ecs_cmp.h"
namespace NWLIB
{
	/// templated component_system static class
	/// description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: t_id-ref;
	template<class rt>
	class NW_API t_cmp_sys
	{
	public:
		using cmp_ref = mem_ref<rt>;				// base reference to an abstract component
		using cmp_tab = dictionary<v1u, cmp_ref>;	// table of t_id and component references
		using cmp_reg = dictionary<v1u, cmp_tab>;	// table of c_id and component containers
		template<class ct>
		using cmp = mem_ref<ct>;					// reference to some typed component
	protected:
		t_cmp_sys() = default;
	public:
		virtual ~t_cmp_sys() = default;
		// --getters
		inline cmp_reg& get_cmp_reg()                     { return m_cmp_reg; }
		inline cmp_tab& get_cmp_tab(v1u t_id)             { return m_cmp_reg[t_id]; }
		template<class ct> cmp_tab& get_tab()             { return get_cmp_tab(ct::get_type_static()); }
		inline cmp_ref& get_cmp_ref(v1u t_id, v1u c_id)   { return m_cmp_reg[t_id][c_id]; }
		template<class ct> cmp_ref& get_cmp_ref(v1u c_id) { return get_cmp_ref(ct::get_type_static(), c_id); }
		template<class ct> cmp<ct> get_cmp(v1u c_id)      { return cmp<ct>(get_cmp_ref<ct>(c_id)); }
		// --predicates
		inline v1b has_cmp(v1u t_id, v1u c_id)            { return m_cmp_reg[t_id].find(c_id) != m_cmp_reg[t_id].end(); }
		template<class ct> v1b has_cmp(v1u c_id)          { return has_cmp(ct::get_type_static(), c_id); }
	protected:
		cmp_reg m_cmp_reg;
	};
	/// component_system singleton class
	class NW_API cmp_sys : public t_cmp_sys<a_cmp>, public t_singleton<cmp_sys>
	{
		friend class t_singleton<cmp_sys>;
	private:
		cmp_sys();
	public:
		~cmp_sys();
		// --core_methods
		template<class ct, typename ... args>
		cmp<ct> new_cmp(args& ... arguments) {
			cmp<ct> ref;
			ref.make_ref<ct>(std::forward<args&>(arguments)...);
			m_cmp_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		template<class act, class ct, typename ... args>
		cmp<act> new_cmp(args& ... arguments) {
			cmp<act> ref;
			ref.make_ref<ct>(std::forward<args&>(arguments)...);
			m_cmp_reg[ref->get_type()][ref->get_id()].set_ref(ref);
			return ref;
		}
		void del_cmp(v1u t_id, v1u c_id) {
			if (!has_cmp(t_id, c_id)) { return; }
			m_cmp_reg[t_id].erase(c_id);
		}
		template<class ct>
		void del_cmp(v1u c_id) {
			del_cmp(ct::get_type_static(), c_id);
		}
	};
}
#endif	// NW_ECS_COMPONENT_SYSTEM_H