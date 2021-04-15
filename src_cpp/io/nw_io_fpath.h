#ifndef NW_IO_FILE_PATH_H
#define NW_IO_FILE_PATH_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "nw_io_flib.h"
namespace NW
{
	class fpath : public flib::path
	{
	public:
		using cpath = const flib::path;
		using cfpath = const fpath;
	public:
		fpath();
		fpath(cstr str);
		fpath(cpath& pth);
		fpath(cfpath& pth);
		~fpath();
		// --getters
		inline dstr get_full() const { return path::string(); }
		inline dstr get_name() const { return path::filename().string(); }
		inline dstr get_stem() const { return path::stem(); }
		inline dstr get_extn() const { return path::extension(); }
		inline fpath get_root() const { return fpath(path::root_path()); }
		inline fpath get_over() const { return fpath(path::parent_path()); }
		inline fpath get_relt() const { return fpath(path::relative_path()); }
		inline size_t get_fsize() const  { return flib::file_size(*this); }
		inline fspace get_fspace() const { return flib::space(*this); }
		inline size_t get_ssize() const { return m_str.size(); }
		inline size_t get_slen() const  { return m_str.length(); }
		// --setters
		// --predicates
		inline v1bit is_file() const { return flib::exists(*this); }
		inline v1bit is_fdir() const { return flib::is_directory(*this); }
		inline v1bit has_name() const { return path::has_filename(); }
		inline v1bit has_stem() const { return path::has_stem(); }
		inline v1bit has_extn() const { return path::has_extension(); }
		inline v1bit has_root() const { return path::has_root_directory(); }
		inline v1bit has_over() const { return path::has_parent_path(); }
		inline v1bit has_relt() const { return path::has_relative_path(); }
		// --operators
		inline operator dstr() const   { return path::string(); }
		inline operator dstr16() const { return path::wstring(); }
		// --core_methods
		v1bit remake(cstr str);
		v1bit remake(cfpath& pth);
	protected:
	};
}
#endif	// NW_API
#endif	//	// NW_IO_FILE_PATH_H
