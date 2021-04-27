#ifndef NW_ECS_ENTITY_H
#define NW_ECS_ENTITY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../std/nw_std_array.h"
#	include "nw_ecs_cmp.h"
#	include "nw_ecs_cmp_sys.h"
namespace NW
{
	/// abstract entity class
	/// --base class for complex objects;
	/// --allows to construct an object of different components;
	/// --takes responsibility for creation and destruction of all components
	class NW_API a_ent : public a_type_idx_owner
	{
	protected:
		a_ent() : a_type_idx_owner() { }
	public:
		virtual ~a_ent() = default;
	};
	/// templated entity class
	template<class tent, class tref = a_cmp>
	class NW_API t_ent: public t_type_idx_owner<tent, a_ent>
	{
	public:
		using cmp_ref_t = mem_ref<tref>;    // component reference
		using cmp_ref_tc = const cmp_ref_t; // component constant reference
		using cmp_tab_t = darray_t<cmp_ref_t>;// component table
		using cmp_tab_tc = const cmp_tab_t; // component constant table
		template<class tcmp> using cmp_t = mem_ref<tcmp>; // particular component
		template<class tcmp> using cmp_tc = cmp_t<tcmp>;  // particular constant component
	protected:
		t_ent() : t_type_idx_owner(), m_cmp_tab(get_cmp_tab_static()) { }
	public:
		virtual ~t_ent() = default;
		// --getters
		inline cmp_tab_t& get_cmp_tab()        { return m_cmp_tab; }
		inline cmp_tab_tc& get_cmp_tab() const { return m_cmp_tab; }
		static inline cmp_tab_t& get_cmp_tab_static()  { static cmp_tab_t s_cmp_tab; return s_cmp_tab; }
		inline size_tc get_cmp_count() const         { return get_cmp_tab().size(); }
		static inline size_tc get_cmp_count_static() { return get_cmp_tab_static().size(); }
		inline cmp_ref_t& get_cmp_ref(size_t key)        { NW_CHECK(has_cmp(key), "not found!", return cmp_ref_t()); return get_cmp_tab()[key]; }
		inline cmp_ref_tc& get_cmp_ref(size_t key) const { get_cmp_ref(key); }
		static inline cmp_ref_t& get_cmp_ref_static(size_t key)  { NW_CHECK(has_cmp_static(key), "not found!", return cmp_ref_t()); return get_cmp_tab_static()[key]; }
		template<class tcmp> cmp_t<tcmp> get_cmp(size_t key) const        { cmp_t<tcmp>(get_cmp_ref(key)); }
		template<class tcmp> cmp_t<tcmp> get_cmp_static(size_t key) const { cmp_t<tcmp>(get_cmp_ref_static(key)); }
		// --setters
		inline v1nil add_cmp(cmp_ref_t& ref)                 { get_cmp_tab().push_back(ref); }
		template<class tcmp> v1nil add_cmp(cmp_t<tcmp>& cmp) { add_cmp(cmp_ref_t(cmp)); }
		static inline v1nil add_cmp_static(cmp_ref_t& ref)                 { get_cmp_tab_static().push_back(ref); }
		template<class tcmp> static v1nil add_cmp_static(cmp_t<tcmp>& cmp) { add_cmp_static(cmp_ref_t(cmp)); }
		inline v1nil rmv_cmp(size_t key)               { NW_CHECK(has_cmp(key), "not found!", return); get_cmp_tab().erase(get_cmp_tab().begin() + key); }
		static inline v1nil rmv_cmp_static(size_t key) { NW_CHECK(has_cmp_static(key), "not found!", return); get_cmp_tab_static().erase(get_cmp_tab_static().begin() + key); }
		// --predicates
		inline v1bit has_cmp(size_t key) const         { key < get_cmp_count(); }
		static inline v1bit has_cmp_static(size_t key) { return key < get_cmp_count_static(); }
	protected:
		cmp_tab_t m_cmp_tab;
	};
}
#endif	// NW_API
#endif	// NW_ECS_ENTITY_H