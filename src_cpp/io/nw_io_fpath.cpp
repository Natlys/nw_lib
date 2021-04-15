#include "nw_lib_pch.hpp"
#include "nw_io_fpath.h"
#if (defined NW_API)
#include "nw_io_sys.h"
namespace NW
{
	fpath::fpath() :
		path()
	{
	}
	fpath::fpath(cstr source) :
		path(source)
	{
	}
	fpath::fpath(cpath& pth) :
		path(pth)
	{
	}
	fpath::fpath(cfpath& pth) :
		path(pth)
	{
	}
	fpath::~fpath() {}
	// --getters
	// --setters
	// --==<core_methods>==--
	v1bit fpath::remake(cstr str)
	{
		m_str.resize(strlen(str));
		m_str = io_sys::get().get_fpath(str);
		if (!io_sys::get().is_file_path(str)) { return false; }
		return true;
	}
	v1bit fpath::remake(cfpath& pth)
	{
		if (!io_sys::get().is_file_path(&pth.get_full()[0])) { return false; }
		m_str.resize(pth.get_slen());
		m_str = io_sys::get().get_fpath(&pth.get_full()[0]);
		return true;
	}
	// --==</core_methods>==--
}
#endif	// NW_API