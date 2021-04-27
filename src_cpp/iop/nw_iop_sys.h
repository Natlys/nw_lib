#ifndef NW_IOP_SYSTEM_H
#define NW_IOP_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_WAPI)
#	include "../std/nw_std_sing.h"
#	include "../ecs/nw_ecs_ent_sys.h"
#	include "../ecs/nw_ecs_cmp_sys.h"
#	include "nw_iop_flib.h"
#	include "nw_iop_fpath.h"
#	include "nw_iop_stm.h"
#	include "nw_iop_cmp.h"
namespace NW
{
	/// input_output_system static class
	class NW_API iop_sys : public t_singleton<iop_sys>
	{
	public:
		using iput_t = std::stringstream;
		using iput_tc = const iput_t;
		using oput_t = op_stream_t;
		using oput_tc = const oput_t;
		using path_t = iop_fpath_t;
		using path_tc = const path_t;
		using space_t = fspace;
		using space_tc = const space_t;
		friend class t_singleton<iop_sys>;
	public:
		iop_sys();
		~iop_sys();
		// --getters
		inline iput_t& get_iput()        { return *m_iput; }
		inline iput_tc& get_iput() const { return *m_iput; }
		inline oput_t& get_oput()        { return *m_oput; }
		inline oput_tc& get_oput() const { return *m_oput; }
		inline path_t& get_path()        { return m_path; }
		inline path_tc& get_path() const { return m_path; }
		inline path_t get_path(cstr_t fpath) const               { return get_path() / fpath; }
		inline path_t get_path(cstr_t fpath, cstr_t fname) const { return get_path() / fpath / fname; }
		inline size_tc get_fsize(cstr_t fpath) const   { return flib::file_size(fpath); }
		inline space_tc get_fspace(cstr_t fpath) const { return flib::space(fpath); }
		// --setters
		v1nil set_input(iput_t* in);
		v1nil set_output(oput_t* out);
		v1nil set_path(path_tc& path);
		// --predicates
		inline v1bit has_iput() const  { return m_iput != NW_NULL; }
		inline v1bit has_oput() const { return m_oput != NW_NULL; }
		inline v1bit has_path() const { return m_path.get_full() != NW_DEFAULT_STR; }
		inline v1bit has_path(cstr_t path) const { return m_path.get_full() != path; }
		inline v1bit is_fdir(cstr_t fpath) const { if (strlen(fpath) > NW_MAX_PATH) { return NW_FALSE; } return flib::is_directory(fpath); }
		inline v1bit is_file(cstr_t fpath) const { if (strlen(fpath) > NW_MAX_PATH) { return NW_FALSE; } return flib::exists(fpath); }
		// --core_methods
		v1bit init();
		inline v1bit init(cstr_t path) { set_path(path); return init(); }
		v1bit quit();
		v1nil update();
		// --directories
		v1nil new_fdir(cstr_t fpath);
		v1nil del_fdir(cstr_t fpath);
		// -- files
		v1nil new_file(cstr_t fpath);
		v1nil del_file(cstr_t fpath);
		cstr_t load_dialog(cstr_t filter, window_handle wnd = NW_NULL);
		v1bit load_file(cstr_t fpath, ptr_t data, size_t size);
		v1bit load_file(cstr_t fpath, dstr_t& data);
		v1bit load_file(cstr_t fpath, a_ip_cmp& data);
		cstr_t save_dialog(cstr_t filter, window_handle wnd = NW_NULL);
		v1bit save_file(cstr_t fpath, ptr_tc data, size_t size);
		v1bit save_file(cstr_t fpath, dstr_tc& data);
		v1bit save_file(cstr_t fpath, a_op_cmp& data);
		// -- logging
		v1nil write_info(cstr_t format, ...);
		v1nil write_warn(cstr_t format, ...);
		v1nil write_error(cv1u err_code, cstr_t format, ...);
	private:
		iput_t* m_iput;
		oput_t* m_oput;
		path_t m_path;
	};
}
#endif	// NW_WAPI
#endif // NW_IOP_SYSTEM_H
