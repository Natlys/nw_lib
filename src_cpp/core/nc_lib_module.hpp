#ifndef NC_LIB_MODULE_HPP
#	define NC_LIB_MODULE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_WAPI)
/* includes */
/* defines */
// types //
/// module_type_template
/// description:
template<cstr_t name>
class nc_module_tt
{
public:
	using module_t = nc_module_tt;
	using module_tc = const module_t;
	using handle_t = nc_wapi_module_t;
	using handle_tc = const handle_t;
public:
	inline nc_module_tt() : m_handle(::LoadLibrary(name)) { NC_CHECK(has_handle(), "load error!", return); }
	inline ~nc_module_tt() { if (has_handle()) { ::FreeLibrary(m_handle); m_handle = NC_ZERO; } }
	/* getters */
	static constexpr inline cstr_t get_name() { return name; }
	inline handle_t& get_handle()           { return m_handle; }
	inline handle_tc& get_handle() const    { return m_handle; }
	inline ptr_t get_proc(cstr_t proc_name) { return ::GetProcAddress(m_handle, proc_name); }
	/* setters */
	/* predicates */
	inline v1bit_t has_handle() const               { return m_handle != NC_ZERO; }
	inline v1bit_t has_proc(cstr_t proc_name) const { return ::GetProcAddress(m_handle, proc_name) != NC_NULL; }
	/* commands */
	/* operators */
protected:
	handle_t m_handle;
};
#endif	/* NC_WAPI */
/* end_of_file */
#endif	// NC_LIB_MODULE_HPP //