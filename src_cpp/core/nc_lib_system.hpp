#ifndef NC_LIB_SYSTEM_HPP
#	define NC_LIB_SYSTEM_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "../std/nc_lib_table.hpp"
#		include "../mem/nc_mem_ref.hpp"
#		include "nc_lib_single.hpp"
/// standard_system_type
template<class tsys>
class nc_system_tt : public nc_single_tt<tsys>
{
public:
	using sys_t = tsys;
	using sys_tc = const sys_t;
public:
	// ctor_dtor //
	inline nc_system_tt() = default;
	inline ~nc_system_tt() = default;
	// getters //
	// setters //
	// predicates //
	// commands //
	inline v1bit_t init() { return NC_TRUTH; }
	inline v1bit_t quit() { return NC_TRUTH; }
	inline v1bit_t work() { return NC_TRUTH; }
	// operators //
protected:
};
/// system_type_template_reference
template<class tsys, class tref>
class nc_system_ttr : public nc_system_tt<tsys>
{
public:
	// system //
	using sys_t = tsys;
	using sys_tc = const sys_t;
	// values //
	using type_t = v1u_t;
	using type_tc = const type_t;
	using indx_t = v1u_t;
	using indx_tc = const indx_t;
	// references //
	using ref_t = nc_ref_tt<tref>; // reference to an abstract type;
	using ref_tc = const ref_t;    // constant reference to an abstract type;
	using tab_t = nc_table_tt<type_t, ref_t>; // table of t_id and abstract type references;
	using tab_tc = const tab_t;               // constant table of type_indx and abstract type references;
	using reg_t = nc_table_tt<indx_t, tab_t>; // table of ent_indx and abstract type tables;
	using reg_tc = const reg_t;               // constant registry for cmp_id and abstract type containers;
public:
	constexpr inline nc_system_ttr() : m_reg(reg_t()) { }
	virtual inline ~nc_system_ttr() { NC_CHECK(!has_reg(), "there is excess of refs!", return); }
	// getters //
	inline reg_t& get_reg()        { return m_reg; }
	inline reg_tc& get_reg() const { return m_reg; }
	inline tab_t& get_tab(type_tc type)        { NC_CHECK(has_tab(type), "not found!", return tab_t()); return get_reg()[type]; }
	inline tab_tc& get_tab(type_tc type) const { NC_CHECK(has_tab(type), "not found!", return tab_tc()); return get_reg().find(type)->second; }
	template<class tname> tab_t& get_tab()        { return get_tab(tname::get_type_static()); }
	template<class tname> tab_tc& get_tab() const { return get_tab(tname::get_type_static()); }
	inline ref_t& get_ref(type_tc type, indx_tc indx)        { NC_CHECK(has_ref(type, indx), "not found!", return get_tab(type)[0u]); return get_tab(type)[indx]; }
	inline ref_tc& get_ref(type_tc type, indx_tc indx) const { NC_CHECK(has_ref(type, indx), "not found!", return get_tab(type).find(0u)->second); return get_tab(type).find(indx)->second; }
	template<class tname> nc_ref_tt<tname> get_ref(indx_tc indx)       { return get_ref(tname::get_type_static(), indx); }
	template<class tname> nc_ref_tt<tname> get_ref(indx_tc indx) const { return get_ref(tname::get_type_static(), indx); }
	// predicates //
	inline v1bit_t has_reg() const { return !m_reg.empty(); }
	inline v1bit_t has_tab(v1u_tc type) const     { return m_reg.find(type) != m_reg.end(); }
	template<class tname> v1bit_t has_tab() const { return has_tab(tname::get_type_static()); }
	inline v1bit_t has_ref(type_tc type, indx_tc indx) const  {
		auto& type_tab = m_reg.find(type);
		if (type_tab == m_reg.end()) { return NC_FALSE; }
		auto& tab = type_tab->second;
		return get_tab(type).find(indx) != tab.end();
	}
	template<class tname> v1bit_t has_ref(indx_tc indx) const { return has_ref(tname::get_type_static(), indx); }
	// commands //
	inline v1bit_t init() {
		// checking //
		NC_PCALL({
			NC_CHECK(!has_reg(), "init is already done!", return NC_FALSE);
		}, "init error!", return NC_FALSE);
		// action //
		NC_PCALL({
			m_reg[NC_ZERO][NC_ZERO] = ref_t();
		}, "init error!", return NC_FALSE);
		// result //
		return NC_TRUTH;
	}
	inline v1bit_t quit() {
		// checking //
		NC_PCALL({
			NC_CHECK(has_reg(), "quit is already done!", return NC_FALSE);
		}, "quit error!", return NC_FALSE);
		// action //
		NC_PCALL({
			while (!m_reg.empty()) {
				auto& itab = m_reg.begin()->second;
				while (!itab.empty()) {
					itab.erase(itab.begin());
				}
				m_reg.erase(m_reg.begin());
			}
		}, "quit error!", return NC_FALSE);
		// result //
		return NC_TRUTH;
	}
	inline v1bit_t work() {
		// checking //
		NC_PCALL({
			//
		}, "work error!", return NC_FALSE);
		// action //
		NC_PCALL({
			//
		}, "work error!", return NC_FALSE);
		// result //
		return NC_TRUTH;
	}
	template<class tname, typename ... targs> nc_ref_tt<tname> new_ref(targs&& ... args) {
		NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
		nc_ref_tt<tname> ref;
		ref.make_ref<tname>(std::forward<targs>(args)...);
		m_reg[ref->get_type()][ref->get_indx()].set_ref(ref);
		return ref;
	}
	template<class tbase, class tname, typename ... targs> nc_ref_tt<tbase> new_ref(targs&& ... args) {
		NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
		NC_CHECK_TYPE_BASE(tbase, tref, "tbase must inherit ref_type!");
		nc_ref_tt<tbase> ref;
		ref.make_ref<tname>(std::forward<targs>(args)...);
		m_reg[ref->get_type()][ref->get_indx()].set_ref(ref);
		return ref;
	}
	inline sys_t& del_ref(type_tc type, indx_tc indx) {
		NC_CHECK(has_ref(type, indx), "not found!", return *this;);
		get_tab(type).erase(indx);
		return *this;
	}
	template<class tname> sys_t& del_ref(indx_tc indx) {
		NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
		return del_ref(tname::get_type_static(), indx);
	}
protected:
	reg_t m_reg;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_SYSTEM_HPP //