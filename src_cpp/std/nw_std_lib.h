#ifndef NW_STD_LIBRARY_H
#define NW_STD_LIBRARY_H
#include "nw_lib_core.hpp"
#if (defined NW_WAPI)
#	include "nw_std_name.h"
namespace NW
{
	/// library_loader class
	class NW_API lib_loader : public a_name_owner
	{
	public:
		using handle_t = library_handle;
		using handle_tc = const handle_t;
	public:
		lib_loader() : a_name_owner(NW_DEFAULT_STR), m_handle(NW_NULL) { }
		lib_loader(cstr_t name) : a_name_owner(name), m_handle(NW_NULL) { NW_CHECK(remake(name), "remake error!", return); }
		virtual ~lib_loader() { if (has_handle()) { ::FreeLibrary(m_handle); m_handle = NW_NULL; } }
		// --getters
		inline handle_t& get_handle()        { return m_handle; }
		inline handle_tc& get_handle() const { return m_handle; }
		inline ptr_t get_proc(cstr_t name) { return ::GetProcAddress(m_handle, name); }
		// --setters
		// --predicates
		inline v1bit has_handle() const { return m_handle != NW_NULL; }
		inline v1bit has_proc(cstr_t name) const { return ::GetProcAddress(m_handle, name) != NW_NULL; }
		// --core_methods
		inline v1bit remake() {
			if (has_handle()) { ::FreeLibrary(m_handle); m_handle = NW_NULL; }
			m_handle = ::LoadLibrary(get_name());
			NW_CHECK(m_handle != NW_NULL, "failed load!", return NW_FALSE);
			return NW_TRUE;
		}
		inline v1bit remake(cstr_t name) { set_name(name); return remake(); }
	protected:
		handle_t m_handle;
	};
}
#endif	// NW_WAPI
#endif	// NW_STD_LIBRARY_H