#ifndef NW_ECS_COMPONENT_SYSTEM_H
#define NW_ECS_COMPONENT_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_cln.h>
#include <core/nwl_type.h>
#include <ecs/ecs_cmp.h>
namespace NW
{
	/// component_system static class
	/// description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: type_id-ref;
	class NW_API cmp_sys
	{
		using ref = mem_ref<a_cmp>;			// base reference to an abstract component
		using tab = dictionary<ui32, ref>;	// table of type_id and component references
		using reg = dictionary<ui32, tab>;	// table of cmp_id and component containers
		template<class ct>
		using cmp = mem_ref<ct>;			// reference to some typed component
	public:
		// --getters
		static inline reg& get_reg()							{ return s_reg; }
		static inline tab& get_tab(ui32 type_id)				{ return s_reg[type_id]; }
		template<class ct> static tab& get_tab()				{ return get_tab(NW_TYPE_ID(ct)); }
		static inline ref& get_ref(ui32 type_id, ui32 cmp_id)	{ return s_reg[type_id][cmp_id]; }
		template<class ct> static ref& get_ref(ui32 cmp_id)		{ return get_ref(NW_TYPE_ID(ct), cmp_id); }
		template<class ct> static cmp<ct> get_cmp(ui32 cmp_id)	{ cmp<ct> cmp_ref(get_cmp<ct>(cmp_id)); }
		// --predicates
		static inline bit has_cmp(ui32 type_id, ui32 cmp_id)	{ return s_reg[type_id].find(cmp_id) != s_reg[type_id].end(); }
		template<class ct> static bit has_cmp(ui32 cmp_id)		{ return has_cmp(NW_TYPE_ID(ct), cmp_id); }
		// --core_methods
		static void on_init();
		static void on_quit();
		template<class ct, typename ... args>
		static cmp<ct> new_cmp(args& ... arguments);
		template<class act, class ct, typename ... args>
		static cmp<act> new_cmp(args& ... arguments);
		static void del_cmp(ui32 type_id, ui32 cmp_id);
		template<class ct> static void del_cmp(ui32 cmp_id)	{ del_cmp(NW_TYPE_ID(ct), cmp_id); }
	private:
		static reg s_reg;
	};
	// --setters
	template<class ct, typename ... args>
	static cmp_sys::cmp<ct> cmp_sys::new_cmp(args& ... arguments) {
		cmp<ct> ref;
		ref.make_ref<ct>(std::forward<args&>(arguments)...);
		s_reg[ref->get_type()][ref->get_id()].set_ref<ct>(ref);
	}
	template<class act, class ct, typename ... args>
	static cmp_sys::cmp<act> cmp_sys::new_cmp(args& ... arguments) {
		cmp<act> ref;
		ref.make_ref<ct>(std::forward<args&>(arguments)...);
		s_reg[ref->get_type()][ref->get_id()].set_ref<act>(ref);
	}
}

#endif	// NW_ECS_COMPONENT_SYSTEM_H