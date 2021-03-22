#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_cln.h>
#include <core/nwl_type.h>
#include <mem/mem_ref.h>
#include "ecs_ent.h"
#include "ecs_cmp.h"
#include "ecs_cmp_sys.h"
namespace NW
{
	/// entity_system static class
	class NW_API ent_sys
	{
	public:
		using ref = mem_ref<a_ent>;			// base reference to an abstract entity
		using tab = dictionary<ui32, ref>;	// table of type_id and entity references
		using reg = dictionary<ui32, tab>;	// table of cmp_id and entity containers
		template<class et>
		using ent = mem_ref<et>;			// reference to some typed entity
		using cmp = mem_ref<a_cmp>;
		using cmps = darray<darray<cmp>>;
	public:
		// --getters
		static inline reg& get_reg()							{ return s_reg; }
		static inline tab& get_tab(ui32 type_id)				{ return s_reg[type_id]; }
		template<class et> static tab& get_tab()				{ return get_tab(et::get_type_static()); }
		static inline ref& get_ref(ui32 ent_id, ui32 type_id)	{ return s_reg[type_id][ent_id]; }
		template<class et> static ref& get_ref(ui32 ent_id)		{ return get_ref(et::get_type_static(), ent_id); }
		template<class et> static ent<et> get_ent(ui32 ent_id)	{ return ent<et>(get_ref<et>(ent_id)); }
		// --predicates
		static inline bit has_ent(ui32 ent_id, ui32 type_id)	{ return s_reg[type_id].find(ent_id) != s_reg[type_id].end(); }
		template<class et> static bit has_ent(ui32 ent_id)		{ return has_ent(et::get_type_static(), ent_id); }
		// --core_methods
		static void on_init();
		static void on_quit();
		template<class et, typename ... args>
		static mem_ref<et> new_ent(args&& ... arguments);
		template<class aet, class et, typename ... args>
		static mem_ref<aet> new_ent(args&& ... arguments);
		static void del_ent(ui32 type_id, ui32 ent_id);
		template<class et> static void del_ent(ui32 ent_id)		{ del_ent(et::get_type_static(), ent_id); }
	private:
		static reg s_reg;
	};
	// --setters
	template<class et, typename ... args>
	mem_ref<et> ent_sys::new_ent(args&& ... arguments) {
		mem_ref<et> ref;
		ref.make_ref<et>(std::forward<args>(arguments)...);
		s_reg[ref->get_type()][ref->get_id()].set_ref<et>(ref);
	}
	template<class aet, class et, typename ... args>
	mem_ref<aet> ent_sys::new_ent(args&& ... arguments) {
		mem_ref<aet> ref;
		ref.make_ref<et>(std::forward<args>(arguments)...);
		s_reg[ref->get_type()][ref->get_id()].set_ref<aet>(ref);
	}
}
#endif // NWL_ECS_ENTITY_SYSTEM_H