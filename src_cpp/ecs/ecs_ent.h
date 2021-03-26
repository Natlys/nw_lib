#ifndef NWL_ECS_ENTITY_H
#define NWL_ECS_ENTITY_H
#include <nwl_core.hpp>
#include <core/nwl_type.h>
#include <core/nwl_id.h>
#include <core/nwl_cont.h>
#include "ecs_cmp.h"
#include "ecs_cmp_sys.h"
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
#		define NW_FOREACH_BRANCH(cont, oper, code_true, code_false) for(auto& itr : cont) { if (itr oper) { code_true } else { code_false } }
		using cmp_type = act;
		using ref = mem_ref<act>;	// component reference
		using tab = darray<ref>;	// component table
		template<class ct>
		using cmp = mem_ref<ct>;	// particular component
	protected:
		t_ent() : t_type_id_owner() { }
	public:
		virtual ~t_ent() = default;
		// --getters
		inline tab& get_tab()                         { return m_tab; }
		inline ref& get_ref(v1ui idx)                 { return m_tab[idx % m_tab.size()]; }
		template<class ct> cmp<ct> get_cmp(v1ui idx)  {
			cmp<ct> cmp_res;
			ref& cmp_ref = m_tab[idx % m_tab.size()];
			if (cmp_ref->check_type(ct::get_type_static())) { cmp_res.set_ref(cmp_ref); }
			return cmp_res;
		}
		// --setters
		inline void add_cmp(ref& ref)                 { m_tab.push_back(ref); }
		template<class ct> void add_cmp(cmp<ct>& cmp) { add_cmp(ref(cmp)); }
		inline void rmv_cmp(v1ui idx)                 { m_tab.erase(m_tab.begin() + idx % m_tab.size()); }
		// --predicates
		inline bit has_cmp(v1ui type_id) const        { NW_FOREACH_BRANCH(m_tab, ->check_type(), return true, NW_EMPTY); return false; }
		template<class ct> bit has_cmp() const        { return has_cmp(ct::get_type_static();); }
	protected:
		tab m_tab;
#		undef NW_FOREACH_BRANCH
	};
}
#endif	// NWL_ECS_ENTITY_H