#ifndef NWLIB_IO_SYSTEM_H
#define NWLIB_IO_SYSTEM_H
#include "nwlib_core.hpp"
#if (defined NW_WAPI)
#include "../std/nwlib_std_os.h"
#include "../std/nwlib_std_sing.h"
#include "../std/nwlib_std_str.h"
#include "../std/nwlib_std_sing.h"
#include "../ecs/nwlib_ecs_ent_sys.h"
#include "../ecs/nwlib_ecs_cmp_sys.h"
#include "nwlib_io_flib.h"
#include "nwlib_io_fpath.h"
#include "nwlib_io_stm.h"
#include "nwlib_io_cmp.h"
#include "nwlib_io_const.h"
namespace NWLIB
{
	/// input_output_system static class
	class NW_API io_sys : public t_singleton<io_sys>
	{
	public:
		friend class t_singleton<io_sys>;
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
#endif // NWLIB_IO_SYSTEM_H