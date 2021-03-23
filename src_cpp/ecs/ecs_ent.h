#ifndef NWL_ECS_ENTITY_H
#define NWL_ECS_ENTITY_H
#include <nwl_core.hpp>
#include <core/nwl_type.h>
#include <core/nwl_id.h>
#include <core/nwl_cln.h>
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
		inline tab& get_tab()						{ return m_tab; }
		inline ref& get_ref(ui8 idx)				{ return m_tab[idx % m_tab.size()]; }
		template<class ct> cmp<ct> get_cmp(ui8 idx) {
			cmp<ct> cmp_res;
			ref& cmp_ref = m_tab[idx % m_tab.size()];
			if (cmp_ref->check_type(ct::get_type_static())) { cmp_res.set_ref(cmp_ref); }
			return cmp_res;
		}
		// --setters
		inline void add_cmp(ref& reference)					{ m_tab.push_back(reference); }
		template<class ct> void add_cmp(cmp<ct>& reference)	{ add_cmp(ref(reference)); }
		inline void rmv_cmp(ui8 idx)						{ m_tab.erase(m_tab.begin() + idx % m_tab.size()); }
		// --predicates
		inline bit has_cmp(ui32 type_id) {
			for (auto& icmp : m_tab) {
				if (icmp->check_type(type_id)) { return true; }
			}
			return false;
		}
		template<class ct> bit has_cmp()	{ return has_cmp(ct::get_type_static();); }
	protected:
		tab m_tab;
	};
}
#endif	// NWL_ECS_ENTITY_H