#ifndef NWL_DATA_SYSTEM_H
#define NWL_DATA_SYSTEM_H
#include <nwl_core.hpp>
#if (defined NW_WAPI)
#include <core/nwl_sing.h>
#include <core/nwl_cln.h>
#include <mem/mem_ref.h>
#include "data_ent.h"
#include "data_cmp.h"
#include "data_lib.h"
#	define DATA std::experimental::filesystem
namespace NW
{
	/// data_system static class
	class NW_API data_sys : public t_singleton<data_sys>
	{
	public:
		friend class t_singleton<data_sys>;
		using cmp = mem_ref<a_data_cmp>;
		using tab = darray<cmp>;
		using path = data_path;
		using cpath = const data_path;
		using space_info = data_space_info;
		using cspace_info = const data_space_info;
	private:
		data_sys();
	public:
		~data_sys();
		// --getters
		inline path get_path()							{ m_path_curr = DATA::current_path(); return m_path_curr; }
		inline path get_path(cstr fpath)				{ return get_path() / fpath; }
		inline path get_path(cstr fpath, cstr fname)	{ return get_path() / fpath / fname; }
		inline size get_size(cstr fpath)				{ return DATA::file_size(fpath); }
		inline space_info get_space_info(cstr fpath)	{ return DATA::space(fpath); }
		// --setters
		void set_path_curr(cstr cpath);
		// --predicates
		inline bit is_drct_path(cstr fpath)			{ return DATA::is_directory(fpath); }
		inline bit is_file_path(cstr fpath)			{ return DATA::exists(fpath); }
		// --core_methods
		void new_drct(cstr dir_path);
		void del_drct(cstr dir_path);
		// --loading
		cstr dialog_load(cstr filter, window_handle wnd);
		bit load_file(cstr file_path, ptr data, size nof_bytes);
		bit load_file(cstr file_path, dstr& data);
		bit load_file(cstr file_path, a_data_cmp& data);
		// --saving
		cstr dialog_save(cstr filter, window_handle wnd);
		bit save_file(cstr file_path, ptr data, size nof_bytes);
		bit save_file(cstr file_path, dstr& data);
		bit save_file(cstr file_path, a_data_cmp& data);
	private:
		path m_path_curr;
		path m_path_temp;
	};
}
#	undef DATA
#endif	// NW_WAPI
#endif	// NWL_DATA_SYSTEM_H