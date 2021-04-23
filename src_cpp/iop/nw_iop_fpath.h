#ifndef NW_IOP_FILE_PATH_H
#define NW_IOP_FILE_PATH_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_iop_flib.h"
namespace NW
{
	class NW_API iop_fpath_t : public flib::path
	{
	public:
		using fpath_t = iop_fpath_t;
		using fpath_tc = const fpath_t;
		using path_t = flib::path;
		using path_tc = const path_t;
	public:
		iop_fpath_t();
		iop_fpath_t(cstr_t str);
		iop_fpath_t(path_tc& copy);
		iop_fpath_t(path_t&& copy);
		iop_fpath_t(fpath_tc& copy);
		iop_fpath_t(fpath_t&& copy);
		~iop_fpath_t();
		// --getters
		inline dstr_t get_full() const { return path::string(); }
		inline dstr_t get_name() const { return path::filename().string(); }
		inline dstr_t get_stem() const { return path::stem(); }
		inline dstr_t get_extn() const { return path::extension(); }
		inline fpath_tc get_root() const { return fpath_tc(path::root_path()); }
		inline fpath_tc get_over() const { return fpath_tc(path::parent_path()); }
		inline fpath_tc get_relt() const { return fpath_tc(path::relative_path()); }
		inline size_t get_fsize() const  { return flib::file_size(*this); }
		inline fspace get_fspace() const { return flib::space(*this); }
		inline size_t get_ssize() const { return m_str.size(); }
		inline size_t get_slen() const  { return m_str.length(); }
		// --setters
		v1nil set_full(cstr_t str);
		inline v1nil set_full(dstr_tc& str) { set_full(&str[0]); }
		inline v1nil set_full(path_tc& pth) { set_full(pth.string()); }
		inline v1nil set_full(fpath_tc& pth) { set_full(pth.get_full()); }
		// --predicates
		inline v1bit is_file() const { return flib::exists(*this); }
		inline v1bit is_fdir() const { return flib::is_directory(*this); }
		inline v1bit has_full() const { return get_full() != NW_DEFAULT_STR; }
		inline v1bit has_full(cstr_t str) const    { return get_full() != str; }
		inline v1bit has_full(path_tc& pth) const  { return has_full(&pth.string()[0]); }
		inline v1bit has_full(fpath_tc& pth) const { return has_full(pth.get_full()); }
		inline v1bit has_name() const { return path::has_filename(); }
		inline v1bit has_stem() const { return path::has_stem(); }
		inline v1bit has_extn() const { return path::has_extension(); }
		inline v1bit has_root() const { return path::has_root_directory(); }
		inline v1bit has_over() const { return path::has_parent_path(); }
		inline v1bit has_relt() const { return path::has_relative_path(); }
		// --operators
		inline v1nil operator=(cstr_t str)    { set_full(str); }
		inline v1nil operator=(path_tc& pth)  { set_full(pth); }
		inline v1nil operator=(path_t&& pth)  { set_full(pth); }
		inline v1nil operator=(fpath_tc& pth) { set_full(pth); }
		inline v1nil operator=(fpath_t&& pth) { set_full(pth); }
		inline v1bit operator==(cstr_t str) const    { return has_full(str); }
		inline v1bit operator==(path_tc& pth) const  { return has_full(pth); }
		inline v1bit operator==(fpath_tc& pth) const { return has_full(pth); }
		inline operator dstr_t() const  { return path::string(); }
		inline operator dwstr_t() const { return path::wstring(); }
		// --core_methods
		v1bit remake();
		inline v1bit remake(path_tc& pth) { set_full(&pth.string()[0]); return remake(); }
	protected:
	};
}
#endif	// NW_API
#endif	//	// NW_IOP_FILE_PATH_H
