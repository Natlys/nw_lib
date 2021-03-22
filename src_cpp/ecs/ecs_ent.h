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
	class NW_API a_ent : public a_type_owner, public a_id_owner
	{
	protected:
		a_ent();
		a_ent(const a_ent& copy) = delete;
	public:
		virtual ~a_ent();
		// --getters
		virtual inline ui32 get_type() const = 0;
		virtual inline ui32 get_id() const = 0;
		// --setters
		void set_enabled(bit enable);
		// --predicates
		inline bit is_enabled()	{ return m_is_enabled; }
		// --operators
		inline void operator=(const a_ent& copy) = delete;
	protected:
		bit m_is_enabled;
	};
}
namespace NW
{
	/// templated entity class
	template<class et, class aet = a_ent, class act = a_cmp>
	class NW_API t_ent: public t_type_owner<et, aet>, public t_id_owner<et>
	{
		using ref = mem_ref<act>;	// component reference
		using tab = darray<ref>;	// component table
		template<class ct>
		using cmp = mem_ref<ct>;	// particular component
	protected:
		template<typename ... args> t_ent(args ... arguments) :
			t_type_owner(std::forward<args>(agruments)...)
		{
		}
	public:
		virtual ~t_ent() = default;
		// --getters
		inline tab& get_tab()					{ return m_tab; }
		inline ref& get_ref(ui8 idx)			{ return m_tab[idx % m_tab.size()]; }
		template<class ct> cmp<ct> get_cmp(ui8 idx) {
			cmp<ct> cmp_res;
			ref& cmp_ref = m_tab[idx % m_tab.size()];
			if (cmp_ref->check_type(ct::get_type_static())) { cmp_res.set_ref(cmp_ref); }
			return cmp_res;
		}
		// --setters
		inline void add_cmp(ref& reference)		{ m_tab.push_back(reference); }
		inline void rmv_cmp(ui8 idx)			{ m_tab.erase(m_tab.begin() + idx % m_tab.size()); }
		// --predicates
		inline bit has_cmp(ui32 type_id) {
			for (auto& icmp : m_tab) {
				if (icmp->check_type(type_id)) { return true; }
			}
			return false;
		}
		template<class ct> bit has_cmp()	{ return has_cmp(ct::get_type_static();); }
	private:
		tab m_tab;
	};
}
#endif	// NWL_ECS_ENTITY_H