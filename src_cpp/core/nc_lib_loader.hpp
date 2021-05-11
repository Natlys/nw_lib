#ifndef NC_LIB_LOADER_H
#	define NC_LIB_LOADER_H
#	include "../nc_lib_core.hpp"
#	if (defined NC_WAPI)
#		include "nc_lib_name.h"
/// library_loader_type
class NC_API nc_loader_t : public nc_name_owner_t
{
public:
	using handle_t = library_handle;
	using handle_tc = const handle_t;
public:
	inline nc_library_t() : nc_name_owner_t(NC_DEFAULT_STR), m_handle(NC_NULL) { }
	inline nc_library_t(cstr_t name) : nc_name_owner_t(name), m_handle(NC_NULL) { NC_CHECK(remake(name), "remake error!", return); }
	virtual inline ~nc_library_t() { if (has_handle()) { ::FreeLibrary(m_handle); m_handle = NC_NULL; } }
	// getters //
	inline handle_t& get_handle()        { return m_handle; }
	inline handle_tc& get_handle() const { return m_handle; }
	inline ptr_t get_proc(cstr_t name) { return ::GetProcAddress(m_handle, name); }
	// setters //
	// predicates //
	inline v1bit_t has_handle() const { return m_handle != NC_NULL; }
	inline v1bit_t has_proc(cstr_t name) const { return ::GetProcAddress(m_handle, name) != NC_NULL; }
	// commands //
	inline v1bit_t remake() {
		if (has_handle()) { ::FreeLibrary(m_handle); m_handle = NC_NULL; }
		m_handle = ::LoadLibrary(get_name());
		NC_CHECK(m_handle != NC_NULL, "failed load!", return NC_FALSE);
		return NC_TRUTH;
	}
	inline v1bit_t remake(cstr_t name) { set_name(name); return remake(); }
protected:
	handle_t m_handle;
};
#endif	// NC_WAPI //
// end_of_file //
#endif	// NC_LIB_LOADER_HPP //