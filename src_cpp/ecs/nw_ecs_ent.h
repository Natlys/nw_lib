#ifndef NW_ECS_ENTITY_H
#define NW_ECS_ENTITY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_cont.h"
#include "nw_ecs_cmp.h"
#include "nw_ecs_cmp_sys.h"
namespace NW
{
	/// abstract entity class
	/// --base class for complex objects;
	/// --allows to construct an object of different components;
	/// --takes responsibility for creation and destruction of all components
	class NW_API a_ent : public a_type_id_owner, public a_mem_user
	{
	protected:
		a_ent() : a_type_id_owner() { }
	public:
		virtual ~a_ent() = default;
	};
	/// templated entity class
	template<class et, class act = a_cmp>
	class NW_API t_ent: public t_type_id_owner<et, a_ent>
	{
	public:
		using cmp_type = act;
		using ref = mem_ref<act>;	// component reference
		using tab = darray<ref>;	// component table
		template<class ct>
		using cmp = mem_ref<ct>;	// particular component
	protected:
		t_ent() : t_type_id_owner(), m_tab(get_tab_static()) { }
	public:
		virtual ~t_ent() = default;
		// --getters
		inline tab& get_tab()                       { return m_tab; }
		inline ref& get_ref(v1u idx)                { return m_tab[idx % m_tab.size()]; }
		template<class ct> cmp<ct> get_cmp(v1u idx) {
			ref& cmp_ref = m_tab[idx % m_tab.size()];
			cmp<ct> cmp_res;
			if (cmp_ref->check_type(ct::get_type_static())) { cmp_res.set_ref(cmp_ref); }
			return cmp_res;
		}
		// --getters_static
		static inline tab& get_tab_static()        { static tab s_tab; return s_tab; }
		static inline ref& get_ref_static(v1u idx) { return get_tab_static()[idx % m_tab.size()]; }
		template<class ct>
		static cmp<ct> get_cmp_static(v1u idx)     {
			ref& cmp_ref = get_tab_static()[idx % m_tab.size()];
			cmp<ct> cmp_res;
			if (cmp_ref->check_type(ct::get_type_static())) { cmp_res.set_ref(cmp_ref); }
			return cmp_res;
		}
		// --setters
		inline void add_cmp(ref& ref) { m_tab.push_back(ref); }
		template<class ct>
		void add_cmp(cmp<ct>& cmp)    { add_cmp(ref(cmp)); }
		inline void rmv_cmp(v1u idx)  { m_tab.erase(m_tab.begin() + idx % m_tab.size()); }
		// --setters_static
		static inline void add_cmp_static(ref& ref)  { get_tab_static().push_back(ref); }
		template<class ct>
		static void add_cmp_static(cmp<ct>& cmp)     { add_cmp_static(ref(cmp)); }
		static inline void rmv_cmp_static(v1u idx)   { get_tab_static().erase(m_tab.begin() + idx % m_tab.size()); }
		// --predicates
		inline v1b has_cmp(v1u type_id) const  { for (auto& cmp : m_tab) { if (itr->check_type()) { return true; } return false; } }
		template<class ct> v1b has_cmp() const { return has_cmp(ct::get_type_static();); }
		// --predicates_static
		static inline v1b has_cmp_static(v1u type_id)  { for (auto& cmp : get_tab_static()) { if (itr->check_type()) { return true; } return false; } }
		template<class ct> static v1b has_cmp_static() { return has_cmp_static(ct::get_type_static();); }
	protected:
		tab m_tab;
	};
}
#endif	// NW_API
#endif	// NW_ECS_ENTITY_H