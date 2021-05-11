#ifndef NC_LIB_ENTITY_HPP
#	define NC_LIB_ENTITY_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#		include "../std/nc_lib_array.hpp"
#		include "nc_lib_cmp.hpp"
#		include "nc_lib_cmp_sys.hpp"
// types //
/// entity_type
/// description:
/// --base class for complex objects;
/// --allows to construct an object of different components;
/// --takes responsibility for creation and destruction of all components
class NC_API nc_ent_t : public nc_type_indx_owner_t
{
public:
public:
	// ctor_dtor //
	inline nc_ent_t() : nc_type_indx_owner_t() { }
	virtual inline ~nc_ent_t() { }
};
/// entity_type_template
/// description:
template<class tent, class tref = nc_cmp_t>
class NC_API nc_ent_tt : public nc_type_indx_owner_tt<tent, nc_ent_t>
{
public:
	using cmp_ref_t = mem_ref_t<tref>;    // component reference
	using cmp_ref_tc = const cmp_ref_t; // component constant reference
	using cmp_tab_t = array_t<cmp_ref_t>;// component table
	using cmp_tab_tc = const cmp_tab_t; // component constant table
	template<class tcmp> using nc_cmp_tt = mem_ref_t<tcmp>; // particular component
	template<class tcmp> using cmp_tc = nc_cmp_tt<tcmp>;  // particular constant component
public:
	// ctor_dtor //
	inline nc_ent_tt() : nc_type_indx_owner_tt(), m_cmp_tab(get_cmp_tab_static()) { }
	virtual inline ~nc_ent_tt() { }
	// getters //
	inline cmp_tab_t& get_cmp_tab()        { return m_cmp_tab; }
	inline cmp_tab_tc& get_cmp_tab() const { return m_cmp_tab; }
	static inline cmp_tab_t& get_cmp_tab_static() { static cmp_tab_t s_cmp_tab; return s_cmp_tab; }
	inline size_tc get_cmp_count() const          { return get_cmp_tab().size(); }
	static inline size_tc get_cmp_count_static()  { return get_cmp_tab_static().size(); }
	inline cmp_ref_t& get_cmp_ref(size_t key)        { NC_CHECK(has_cmp(key), "not found!", return cmp_ref_t()); return get_cmp_tab()[key]; }
	inline cmp_ref_tc& get_cmp_ref(size_t key) const { get_cmp_ref(key); }
	static inline cmp_ref_t& get_cmp_ref_static(size_t key)  { NC_CHECK(has_cmp_static(key), "not found!", return cmp_ref_t()); return get_cmp_tab_static()[key]; }
	template<class tcmp> nc_cmp_tt<tcmp> get_cmp(size_t key) const        { nc_cmp_tt<tcmp>(get_cmp_ref(key)); }
	template<class tcmp> nc_cmp_tt<tcmp> get_cmp_static(size_t key) const { nc_cmp_tt<tcmp>(get_cmp_ref_static(key)); }
	// setters //
	inline v1nil_t add_cmp(cmp_ref_t& ref)                 { get_cmp_tab().push_back(ref); }
	template<class tcmp> v1nil_t add_cmp(nc_cmp_tt<tcmp>& cmp) { add_cmp(cmp_ref_t(cmp)); }
	static inline v1nil_t add_cmp_static(cmp_ref_t& ref)                 { get_cmp_tab_static().push_back(ref); }
	template<class tcmp> static v1nil_t add_cmp_static(nc_cmp_tt<tcmp>& cmp) { add_cmp_static(cmp_ref_t(cmp)); }
	inline v1nil_t rmv_cmp(size_t key)               { NC_CHECK(has_cmp(key), "not found!", return); get_cmp_tab().erase(get_cmp_tab().begin() + key); }
	static inline v1nil_t rmv_cmp_static(size_t key) { NC_CHECK(has_cmp_static(key), "not found!", return); get_cmp_tab_static().erase(get_cmp_tab_static().begin() + key); }
	// predicates //
	inline v1bit_t has_cmp(size_t key) const         { key < get_cmp_count(); }
	static inline v1bit_t has_cmp_static(size_t key) { return key < get_cmp_count_static(); }
protected:
	cmp_tab_t m_cmp_tab;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_ECS_ENTITY_HPP //