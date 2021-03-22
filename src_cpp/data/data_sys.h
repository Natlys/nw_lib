#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H
#include <nwl_core.hpp>
#if (defined NW_WAPI)
#include <core/nwl_cln.h>
#include <mem/mem_ref.h>
#include "data_rsc.h"
#include "data_ent.h"
namespace NW
{
	/// data_system static class
	class NW_API data_sys
	{
	public:
		using rsc = mem_ref<a_data_rsc>;
		using rscs = darray<rsc>;
		using path = data_path;
	public:
		// --getters
		static path get_path();
		static path get_path(cstr path);
		static path get_path(cstr file_path, cstr file_name);
		static cstr get_path_str();
		static cstr get_path_str(cstr path);
		static cstr get_path_str(cstr file_path, cstr file_name);
		// --setters
		static void set_path_root(path root_path);
		// --core_methods
		static void on_init();
		static void on_quit();
		// --loading
		static cstr dialog_load(cstr filter, window_handle wnd);
		static bit load_file(cstr file_path, ptr buffer, size nof_bytes);
		static bit load_file(cstr file_path, dstr& buffer);
		static bit load_file(cstr file_path, a_data_rsc& resource);
		// --saving
		static cstr dialog_save(cstr filter, window_handle wnd);
		static bit save_file(cstr file_path, ptr buffer, size nof_bytes);
		static bit save_file(cstr file_path, dstr& buffer);
		static bit save_file(cstr file_path, a_data_rsc& data);
	};
}
#endif	// NW_WAPI
#endif	// NWL_DATA_SYSTEM_H