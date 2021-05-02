#ifndef NW_ECS_SYSTEM_H
#define NW_ECS_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "std/nw_std_type.h"
#	include "std/nw_std_sing.h"
#	include "std/nw_std_table.h"
#	include "mem/nw_mem_ref.h"
namespace NW
{
	template<class tsys, class tref>
	class t_ecs_sys : public t_singleton<tsys>
	{
	public:
		using sys_t = tsys;
		using sys_tc = const sys_t;
		using ref_t = mem_ref<tref>; // reference to an abstract type;
		using ref_tc = const ref_t;  // constant reference to an abstract type;
		using tab_t = t_table<v1u, ref_t>; // table of t_id and abstract type references;
		using tab_tc = const tab_t;        // constant table of type_idx and abstract type references;
		using reg_t = t_table<v1u, tab_t>; // table of ent_idx and abstract type tables;
		using reg_tc = const reg_t;        // constant registry for cmp_id and abstract type containers;
		friend class t_singleton<tsys>;
	public:
		t_ecs_sys() : m_reg(reg_t()) {}
		virtual ~t_ecs_sys() { NW_CHECK(!has_reg(), "there is excess of refs!", return); }
		// --getters
		inline reg_t& get_reg()        { return m_reg; }
		inline reg_tc& get_reg() const { return m_reg; }
		inline tab_t& get_tab(cv1u type)        { NW_CHECK(has_tab(type), "not found!", return tab_t()); return get_reg()[type]; }
		inline tab_tc& get_tab(cv1u type) const { NW_CHECK(has_tab(type), "not found!", return tab_tc()); return get_reg().find(type)->second; }
		template<class tname> tab_t& get_tab() { return get_tab(tname::get_type_static()); }
		template<class tname> tab_tc& get_tab() const { return get_tab(tname::get_type_static()); }
		inline ref_t& get_ref(cv1u type, cv1u idx)        { NW_CHECK(has_ref(type, idx), "not found!", return get_tab(type)[0u]); return get_tab(type)[idx]; }
		inline ref_tc& get_ref(cv1u type, cv1u idx) const { NW_CHECK(has_ref(type, idx), "not found!", return get_tab(type).find(0u)->second); return get_tab(type).find(idx)->second; }
		template<class tname> mem_ref<tname> get_ref(cv1u idx)       { return get_ref(tname::get_type_static(), idx); }
		template<class tname> mem_ref<tname> get_ref(cv1u idx) const { return get_ref(tname::get_type_static(), idx); }
		// --predicates
		inline v1bit has_reg() const { return !m_reg.empty(); }
		inline v1bit has_tab(cv1u type) const        { return m_reg.find(type) != m_reg.end(); }
		template<class tname> v1bit has_tab() const { return has_tab(tname::get_type_static()); }
		inline v1bit has_ref(cv1u type, cv1u idx) const {
			auto& type_tab = m_reg.find(type);
			if (type_tab == m_reg.end()) { return NW_FALSE; }
			auto& tab = type_tab->second;
			return get_tab(type).find(idx) != tab.end();
		}
		template<class tname> v1bit has_ref(cv1u idx) const { return has_ref(tname::get_type_static(), idx); }
		// --core_methods
		v1bit init() {
			NW_CHECK(!has_reg(), "init is already done!", return NW_FALSE);
			m_reg[NW_NULL][NW_NULL] = ref_t();
			return NW_TRUE;
		}
		v1bit quit() {
			NW_CHECK(has_reg(), "quit is already done!", return NW_FALSE);
			while (!m_reg.empty()) {
				auto& itab = m_reg.begin()->second;
				while (!itab.empty()) {
					itab.erase(itab.begin());
				}
				m_reg.erase(m_reg.begin());
			}
			return NW_TRUE;
		}
		template<class tname, typename ... args>
		mem_ref<tname> new_ref(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
			mem_ref<tname> ref;
			ref.make_ref<tname>(std::forward<args>(arguments)...);
			m_reg[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		template<class tbase, class tname, typename ... args>
		mem_ref<tbase> new_ref(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
			NW_CHECK_TYPE_BASE(tbase, tref, "tbase must inherit ref_type!");
			mem_ref<tbase> ref;
			ref.make_ref<tname>(std::forward<args>(arguments)...);
			m_reg[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		inline v1nil del_ref(cv1u type, cv1u idx)     { NW_CHECK(has_ref(type, idx), "not found!", return); get_tab(type).erase(idx); }
		template<class tname> v1nil del_ref(cv1u idx) { NW_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!"); del_ref(tname::get_type_static(), idx); }
	protected:
		reg_t m_reg;
	};
}
#endif	// NW_API
#endif	// NW_ECS_SYS_H