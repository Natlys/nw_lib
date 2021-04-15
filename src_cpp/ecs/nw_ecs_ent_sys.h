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
	template<class tref>
	class NW_API t_ent_sys
	{
	public:
		using ent_ref_t = mem_ref<tref>;    // reference to an abstract entity
		using ent_ref_tc = const ent_ref_t; // constant reference to an abstract entity
		using ent_tab_t = dictionary<v1u, ent_ref_t>; // table of t_id and entity references
		using ent_tab_tc = const ent_tab_t;           // constant table of t_id and entity references
		using ent_reg_t = dictionary<v1u, ent_tab_t>; // table of cmp_id and entity containers
		using ent_reg_tc = const ent_reg_t;           // constant registry for cmp_id and entity containers
		template<class tent> using ent_t = mem_ref<tent>;      // reference to some typed entity
		template<class tent> using ent_tc = const ent_t<tent>; // constant reference to some typed entity
	protected:
		t_ent_sys() = default;
	public:
		virtual ~t_ent_sys() = default;
		// --getters
		inline ent_reg_t& get_ent_reg()        { return m_ent_reg; }
		inline ent_reg_tc& get_ent_reg() const { return m_ent_reg; }
		inline ent_tab_t& get_ent_tab(v1u t_id)        { return get_ent_reg()[t_id]; }
		inline ent_tab_tc& get_ent_tab(v1u t_id) const { return get_ent_reg().find(t_id)->second; }
		template<class tent> ent_tab_t& get_ent_tab()        { return get_ent_tab(tent::get_type_static()); }
		template<class tent> ent_tab_tc& get_ent_tab() const { return get_ent_tab(tent::get_type_static()); }
		inline ent_ref_t& get_ent_ref(v1u t_id, v1u e_id) {
			NW_CHECK(has_ent_ref(t_id, e_id), "not found!", return ent_ref_t());
			return get_ent_tab(t_id)[e_id];
		}
		inline ent_ref_tc& get_ent_ref(v1u t_id, v1u e_id) const {
			NW_CHECK(has_ent_ref(t_id, e_id), "not found!", return ent_ref_t());
			return get_ent_tab(t_id).find(e_id)->second;
		}
		template<class tent> ent_ref_t& get_ent_ref(v1u e_id)       { return get_ent_ref(tent::get_type_static(), e_id); }
		template<class tent> ent_ref_t& get_ent_ref(v1u e_id) const { return get_ent_ref(tent::get_type_static(), e_id); }
		template<class tent> ent_t<tent> get_ent(v1u e_id) const    { return ent_t<tent>(get_ent_ref<tent>(e_id)); }
		// --predicates
		inline v1bit has_ent_tab(v1u t_id) const       { return get_ent_reg().find(t_id) != get_ent_reg().end(); }
		template<class tent> v1bit has_ent_tab() const { return has_ent_tab(tent::get_type_static()); }
		inline v1bit has_ent_ref(v1u t_id, v1u e_id) const {
			auto& itab = get_ent_reg().find(t_id);
			if (itab == get_ent_reg().end()) { return NW_FALSE; }
			return itab->second.find(e_id) != itab->second.end();
		}
		template<class tent> v1bit has_ent_ref(v1u e_id) { return has_ent_ref(tent::get_type_static(), e_id); }
	protected:
		ent_reg_t m_ent_reg;
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
		template<class tname, typename ... args>
		ent_t<tname> new_ent(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, a_ent, "tname must inherit a_ent!");
			ent_t<tname> ref;
			ref.make_ref<tname>(std::forward<args>(arguments)...);
			get_ent_reg()[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		template<class tbase, class tname, typename ... args>
		ent_t<tbase> new_ent(args&& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, a_ent, "tname must inherit a_ent!");
			NW_CHECK_TYPE_BASE(tbase, a_ent, "tname must inherit a_ent!");
			mem_ref<tbase> ref;
			ref.make_ref<tname>(std::forward<args>(arguments)...);
			get_ent_reg()[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		v1nil del_ent(v1u t_id, v1u e_id) { NW_CHECK(has_ent_ref(t_id, e_id), "not found!", return); get_ent_tab(t_id).erase(t_id); }
		template<class tname>
		void del_ent(v1u e_id) { NW_CHECK_TYPE_BASE(tname, a_ent, "tname must inherit a_ent!"); del_ent(tname::get_type_static(), e_id); }
	};
}
#endif	// NW_API
#endif // NW_ECS_ENTITY_SYSTEM_H
