#ifndef NC_LIB_SYSTEM_REFERENCE_HPP
#	define NC_LIB_SYSTEM_REFERENCE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
#		include "../../nc_mem/src_cpp/core/nc_mem_ref.hpp"
#		include "../std/nc_lib_table.hpp"
#		include "nc_lib_system.hpp"
/// reference_system_type
template<class tsys, class tref>
class ref_sys_tt : public nc_system_tt<tsys>
{
public:
	using sys_t = tsys;
	using sys_tc = const sys_t;
	using ref_t = mem_ref_t<tref>; // reference to an abstract type;
	using ref_tc = const ref_t;  // constant reference to an abstract type;
	using tab_t = table_t<v1u_t, ref_t>; // table of t_id and abstract type references;
	using tab_tc = const tab_t;        // constant table of type_idx and abstract type references;
	using reg_t = table_t<v1u_t, tab_t>; // table of ent_idx and abstract type tables;
	using reg_tc = const reg_t;        // constant registry for cmp_id and abstract type containers;
public:
	constexpr inline ref_sys_t() : m_reg(reg_t()) { }
	virtual inline ~ref_sys_t() { NC_CHECK(!has_reg(), "there is excess of refs!", return); }
	// getters //
	inline reg_t& get_reg() { return m_reg; }
	inline reg_tc& get_reg() const { return m_reg; }
	inline tab_t& get_tab(v1u_tc type) { NC_CHECK(has_tab(type), "not found!", return tab_t()); return get_reg()[type]; }
	inline tab_tc& get_tab(v1u_tc type) const { NC_CHECK(has_tab(type), "not found!", return tab_tc()); return get_reg().find(type)->second; }
	template<class tname> tab_t& get_tab() { return get_tab(tname::get_type_static()); }
	template<class tname> tab_tc& get_tab() const { return get_tab(tname::get_type_static()); }
	inline ref_t& get_ref(v1u_tc type, v1u_tc idx) { NC_CHECK(has_ref(type, idx), "not found!", return get_tab(type)[0u]); return get_tab(type)[idx]; }
	inline ref_tc& get_ref(v1u_tc type, v1u_tc idx) const { NC_CHECK(has_ref(type, idx), "not found!", return get_tab(type).find(0u)->second); return get_tab(type).find(idx)->second; }
	template<class tname> mem_ref_t<tname> get_ref(v1u_tc idx) { return get_ref(tname::get_type_static(), idx); }
	template<class tname> mem_ref_t<tname> get_ref(v1u_tc idx) const { return get_ref(tname::get_type_static(), idx); }
	// predicates //
	inline v1bit_t has_reg() const { return !m_reg.empty(); }
	inline v1bit_t has_tab(v1u_tc type) const { return m_reg.find(type) != m_reg.end(); }
	template<class tname> v1bit_t has_tab() const { return has_tab(tname::get_type_static()); }
	inline v1bit_t has_ref(v1u_tc type, v1u_tc idx) const {
		auto& type_tab = m_reg.find(type);
		if (type_tab == m_reg.end()) { return NC_FALSE; }
		auto& tab = type_tab->second;
		return get_tab(type).find(idx) != tab.end();
	}
	template<class tname> v1bit_t has_ref(v1u_tc idx) const { return has_ref(tname::get_type_static(), idx); }
	// commands //
	inline v1bit_t init() {
		NC_CHECK(!has_reg(), "init is already done!", return NC_FALSE);
		m_reg[NC_NULL][NC_NULL] = ref_t();
		return NC_TRUTH;
	}
	inline v1bit_t quit() {
		NC_CHECK(has_reg(), "quit is already done!", return NC_FALSE);
		while (!m_reg.empty()) {
			auto& itab = m_reg.begin()->second;
			while (!itab.empty()) {
				itab.erase(itab.begin());
			}
			m_reg.erase(m_reg.begin());
		}
		return NC_TRUTH;
	}
	inline v1bit_t work() { return NC_TRUTH; }
	template<class tname, typename ... args>
	mem_ref_t<tname> new_ref(args&& ... arguments) {
		NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
		mem_ref_t<tname> ref;
		ref.make_ref<tname>(std::forward<args>(arguments)...);
		m_reg[ref->get_type()][ref->get_idx()].set_ref(ref);
		return ref;
	}
	template<class tbase, class tname, typename ... args>
	mem_ref_t<tbase> new_ref(args&& ... arguments) {
		NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!");
		NC_CHECK_TYPE_BASE(tbase, tref, "tbase must inherit ref_type!");
		mem_ref_t<tbase> ref;
		ref.make_ref<tname>(std::forward<args>(arguments)...);
		m_reg[ref->get_type()][ref->get_idx()].set_ref(ref);
		return ref;
	}
	inline v1nil_t del_ref(v1u_tc type, v1u_tc idx) { NC_CHECK(has_ref(type, idx), "not found!", return); get_tab(type).erase(idx); }
	template<class tname> v1nil_t del_ref(v1u_tc idx) { NC_CHECK_TYPE_BASE(tname, tref, "tname must inherit ref_type!"); del_ref(tname::get_type_static(), idx); }
protected:
	reg_t m_reg;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_SYSTEM_REFERENCE_HPP //