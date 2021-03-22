#ifndef NWL_DATA_PATH_H
#define NWL_DATA_PATH_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include "data_lib.h"
#	define DATA std::experimental::filesystem
namespace NW
{
	class data_path : public DATA::path
	{
		using cpath = const path;
		using dpath = data_path;
		using cdpath = const data_path;
	public:
		data_path();
		data_path(cstr str);
		data_path(cstr16 str);
		data_path(cpath& pth);
		data_path(cdpath& pth);
		~data_path();
		// --getters
		inline dstr get_name() const			{ return path::filename().string(); }
		inline dstr get_stem() const			{ return path::stem(); }
		inline dstr get_extn() const			{ return path::extension(); }
		inline dpath get_root() const			{ return dpath(path::root_path()); }
		inline dpath get_over() const			{ return dpath(path::parent_path()); }
		inline dpath get_relt() const			{ return dpath(path::relative_path()); }
		inline size get_size() const			{ return m_str.size(); }
		inline size get_lnth() const			{ return m_str.length(); }
		inline dstr get_str() const				{ return path::string(); }
		inline dstr16 get_wstr() const			{ return path::wstring(); }
		// --setters
		// --predicates
		inline bit is_file() const				{ return DATA::exists(*this); }
		inline bit is_drct() const				{ return DATA::is_directory(*this); }
		inline bit has_name() const				{ return path::has_filename(); }
		inline bit has_stem() const				{ return path::has_stem(); }
		inline bit has_extn() const				{ return path::has_extension(); }
		inline bit has_root() const				{ return path::has_root_directory(); }
		inline bit has_over() const				{ return path::has_parent_path(); }
		inline bit has_relt() const				{ return path::has_relative_path(); }
		// --operators
		inline operator dstr() const			{ return path::string(); }
		inline operator dstr16() const			{ return path::wstring(); }
		// --core_methods
		bit remake(cstr str);
		bit remake(cdpath& pth);
	protected:
	};
}
#	undef DATA
#endif	//	// NWL_DATA_PATH_H