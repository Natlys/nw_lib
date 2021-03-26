#include <nwl_pch.hpp>
#include "data_path.h"
#include "data_sys.h"
namespace NW
{
	data_path::data_path() :
		path()
	{
	}
	data_path::data_path(csstr source) :
		path(source)
	{
	}
	data_path::data_path(cwstr source) :
		path(source)
	{
	}

	data_path::data_path(cpath& pth) :
		path(pth)
	{
	}
	data_path::data_path(cdpath& pth) :
		path(pth)
	{
	}
	data_path::~data_path() {}
	// --getters
	// --setters
	// --==<core_methods>==--
	bit data_path::remake(cstr str)
	{
		m_str.resize(strlen(str));
		m_str = data_sys::get().get_path(str);
		if (!data_sys::get().is_file_path(str)) { return false; }
		return true;
	}
	bit data_path::remake(cdpath& pth)
	{
		if (!data_sys::get().is_file_path(&pth.get_str()[0])) { return false; }
		m_str.resize(pth.get_lnth());
		m_str = data_sys::get().get_path(&pth.get_str()[0]);
		return true;
	}
	// --==</core_methods>==--
}