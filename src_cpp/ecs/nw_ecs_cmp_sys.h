#ifndef NW_ECS_COMPONENT_SYSTEM_H
#define NW_ECS_COMPONENT_SYSTEM_H
#include "nw_lib_core.hpp"
#include "std/nw_std_sing.h"
#include "std/nw_std_cont.h"
#include "mem/nw_mem_ref.h"
#include "nw_ecs_cmp.h"
namespace NW
{
	/// templated component_system static class
	/// description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: t_id-ref;
	template<class tref>
	class NW_API t_cmp_sys
	{
	public:
		using cmp_ref_t = mem_ref<tref>;    // reference to an abstract component
		using cmp_ref_tc = const cmp_ref_t; // constant reference to an abstract component
		using cmp_tab_t = dictionary<v1u, cmp_ref_t>; // table of t_id and component references
		using cmp_tab_tc = const cmp_tab_t;           // constant table of t_id and component references
		using cmp_reg_t = dictionary<v1u, cmp_tab_t>; // table of c_id and component containers
		using cmp_reg_tc = const cmp_reg_t;           // constant table of c_id and component containers
		template<class tcmp> using cmp_t = mem_ref<tcmp>;      // reference to some typed component
		template<class tcmp> using cmp_tc = const cmp_t<tcmp>; // constant reference to some typed component
	protected:
		t_cmp_sys() = default;
	public:
		virtual ~t_cmp_sys() = default;
		// --getters
		inline cmp_reg_t& get_cmp_reg()         { return m_cmp_reg; }
		inline cmp_reg_tc& get_cmp_reg() const  { return m_cmp_reg; }
		inline cmp_tab_t& get_cmp_tab(v1u t_id)        { return get_cmp_reg()[t_id]; }
		inline cmp_tab_tc& get_cmp_tab(v1u t_id) const { return get_cmp_reg().find(t_id)->second; }
		template<class tcmp> cmp_tab_t& get_cmp_tab()        { return get_cmp_tab(tcmp::get_type_static()); }
		template<class tcmp> cmp_tab_tc& get_cmp_tab() const { return get_cmp_tab(tcmp::get_type_static()); }
		inline cmp_ref_t& get_cmp_ref(v1u t_id, v1u c_id) {
			NW_CHECK(has_cmp_ref(t_id, c_id), "not found!", return cmp_ref_t());
			return get_cmp_tab(t_id)[c_id];
		}
		inline cmp_ref_tc& get_cmp_ref(v1u t_id, v1u c_id) const {
			NW_CHECK(has_cmp_ref(t_id, c_id), "not found!", return cmp_ref_t());
			return get_cmp_tab(t_id).find(c_id)->second;
		}
		template<class tcmp> cmp_ref_t& get_cmp_ref(v1u c_id)        { return get_cmp_ref(tcmp::get_type_static(), c_id); }
		template<class tcmp> cmp_ref_tc& get_cmp_ref(v1u c_id) const { return get_cmp_ref(tcmp::get_type_static(), c_id); }
		template<class tcmp> cmp_t<tcmp> get_cmp(v1u c_id) const     { return cmp_t<tcmp>(get_cmp_ref<tcmp>(c_id)); }
		// --predicates
		inline v1bit has_cmp_tab(v1u t_id) const       { return get_cmp_reg().find(t_id) != get_cmp_reg().end(); }
		template<class tcmp> v1bit has_cmp_tab() const { return has_cmp_tab(tcmp::get_type_static()); }
		inline v1bit has_cmp_ref(v1u t_id, v1u c_id) const {
			auto& itab = get_cmp_reg().find(t_id);
			if (itab == get_cmp_reg().end()) { return NW_FALSE; }
			return itab->second.find(c_id) != itab->second.end();
		}
		template<class tcmp> v1bit has_cmp_ref(v1u c_id) const { return has_cmp_ref(tcmp::get_type_static(), c_id); }
	protected:
		cmp_reg_t m_cmp_reg;
	};
	/// component_system singleton class
	class NW_API cmp_sys : public t_cmp_sys<a_cmp>, public singleton_t<cmp_sys>
	{
	public:
		friend class singleton_t<cmp_sys>;
	private:
		cmp_sys();
	public:
		~cmp_sys();
		// --core_methods
		template<class tname, typename ... args>
		cmp_t<tname> new_cmp(args& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, a_cmp, "tname must inherit a_cmp!");
			cmp_t<tname> ref;
			ref.make_ref<tname>(std::forward<args&>(arguments)...);
			get_cmp_reg()[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		template<class tbase, class tname, typename ... args>
		cmp_t<tbase> new_cmp(args& ... arguments) {
			NW_CHECK_TYPE_BASE(tname, a_cmp, "tname must inherit a_cmp!");
			NW_CHECK_TYPE_BASE(tbase, a_cmp, "tbase must inherit a_cmp!");
			cmp_t<tbase> ref;
			ref.make_ref<tname>(std::forward<args&>(arguments)...);
			get_cmp_reg()[ref->get_type()][ref->get_idx()].set_ref(ref);
			return ref;
		}
		v1nil del_cmp(v1u t_id, v1u c_id) { NW_CHECK(has_cmp_ref(t_id, c_id), "not found!", return); get_cmp_tab(t_id).erase(c_id); }
		template<class tname>
		v1nil del_cmp(v1u c_id) { NW_CHECK_TYPE_BASE(tname, a_cmp, "tname must inherit a_cmp!"); del_cmp(tname::get_type_static(), c_id); }
	};
}
#endif	// NW_ECS_COMPONENT_SYSTEM_H