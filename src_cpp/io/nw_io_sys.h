#ifndef NW_IO_SYSTEM_H
#define NW_IO_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_WAPI)
#include "../std/nw_std_sing.h"
#include "../ecs/nw_ecs_ent_sys.h"
#include "../ecs/nw_ecs_cmp_sys.h"
#include "nw_io_flib.h"
#include "nw_io_fpath.h"
#include "nw_io_err.h"
#include "nw_io_stm.h"
#include "nw_io_cmp.h"
namespace NW
{
	/// input_output_system static class
	class NW_API io_sys : public singleton_t<io_sys>
	{
	public:
		friend class singleton_t<io_sys>;
		using input = stm_io_str;
		using output = stm_out;
		using cfpath = const fpath;
		using fspace = fspace;
		using cfspace = const fspace;
		using cmp = a_io_cmp;
		using ccmp = const cmp;
	private:
		io_sys();
	public:
		~io_sys();
		// --getters
		inline input& get_input()		{ return *m_input; }
		inline output& get_output()		{ return *m_output; }
		inline fpath get_fpath() const                       { return flib::current_path(); }
		inline fpath get_fpath(cstr fpath) const             { return get_fpath() / fpath; }
		inline fpath get_fpath(cstr fpath, cstr fname) const { return get_fpath() / fpath / fname; }
		inline size get_fsize(cstr fpath) const              { return flib::file_size(fpath); }
		inline fspace get_fspace(cstr fpath) const           { return flib::space(fpath); }
		// --setters
		void set_output(stm_out& out);
		void set_path_curr(cstr cpath);
		// --predicates
		inline v1b is_drct_path(cstr fpath) { return flib::is_directory(fpath); }
		inline v1b is_file_path(cstr fpath) { return flib::exists(fpath); }
		// --core_methods
		void update();
		// --directories
		void new_drct(cstr dir_path);
		void del_drct(cstr dir_path);
		// --file_loading
		cstr load_dlg(cstr filter, window_handle wnd);
		bool load_file(cstr file_path, ptr destination, size nof_bytes);
		bool load_file(cstr file_path, dstr& destination);
		bool load_file(cstr file_path, cmp& destination);
		// --file_saving
		cstr save_dlg(cstr filter, window_handle wnd);
		bool save_file(cstr file_path, cptr destination, size nof_bytes);
		bool save_file(cstr file_path, cdstr& destination);
		bool save_file(cstr file_path, ccmp& destination);
		// --logging
		void write_info(cstr format, ...);
		void write_warn(cstr format, ...);
		void write_error(error_codes err_code, cstr format, ...);
	private:
		input* m_input;
		output* m_output;
		fpath m_path_curr;
		fpath m_path_temp;
	};
}
#endif	// NW_WAPI
#endif // NW_IO_SYSTEM_H
