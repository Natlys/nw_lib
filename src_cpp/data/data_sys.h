#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H
#include <nwl_core.hpp>
#if (defined NW_OS)
#include <core/nwl_cln.h>
#include "data_rsc.h"
#include "data_loc.h"
namespace NW
{
	/// data_system static class
	class NW_API data_sys
	{
		using paths = darray<dstr>;
	public:
		// --getters
		static cstr get_path();
		static cstr get_path(cstr file_path);
		static paths get_directory_paths();
		// --setters
		static void set_dir_root(cstr root_directory);
		// --core_methods
		static void on_init();
		static void on_quit();
		// --loading
		static cstr dialog_load(cstr filter, window_handle wnd);
		static bit load_file(cstr file_path, ptr data, size nof_bytes);
		static bit load_file(cstr file_path, dstr& data);
		static bit load_file(cstr file_path, a_data_rsc& data);
		// --saving
		static cstr dialog_save(cstr filter, window_handle wnd);
		static bit save_file(cstr file_path, ptr data, size nof_bytes);
		static bit save_file(cstr file_path, dstr& data);
		static bit save_file(cstr file_path, a_data_rsc& data);
	private:
		static dstr s_root_path;
		static dstr s_temp_path;
	};
}
#endif	// NW_OS
#endif	// NWL_DATA_SYSTEM_H