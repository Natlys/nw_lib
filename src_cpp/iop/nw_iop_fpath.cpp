#include "nw_lib_pch.hpp"
#include "nw_iop_fpath.h"
#if (defined NW_API)
#	include "nw_iop_sys.h"
namespace NW
{
	iop_fpath_t::iop_fpath_t() :
		path()
	{
	}
	iop_fpath_t::iop_fpath_t(cstr_t source) :
		path(source)
	{
	}
	iop_fpath_t::iop_fpath_t(path_tc& copy) :
		path(copy)
	{
	}
	iop_fpath_t::iop_fpath_t(path_t&& copy) :
		path(copy)
	{
	}
	iop_fpath_t::iop_fpath_t(fpath_tc& copy) :
		path(copy)
	{
	}
	iop_fpath_t::iop_fpath_t(fpath_t&& copy) :
		path(copy)
	{
	}
	iop_fpath_t::~iop_fpath_t()
	{
	}
	// --setters
	v1nil iop_fpath_t::set_full(cstr_t str) {
		m_str.resize(strlen(str) + 1);
		OemToCharW(str, &m_str[0]);
	}
	// --==<core_methods>==--
	v1bit iop_fpath_t::remake()
	{
		NW_CHECK(is_file() || is_fdir(), "not valid path!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API