#include <nwl_pch.hpp>
#include "data_ent.h"
#include "data_sys.h"
namespace NW
{
	data_ent::data_ent(cstr name) :
		m_path(data_sys::get_path()),
		m_name(name)
	{
		ui32 attribs = ::GetFileAttributesA(data_sys::get_path(name));
	}
	data_ent::data_ent(cstr path, cstr name) :
		m_path(data_sys::get_path(path)),
		m_name(name)
	{
		ui32 attribs = ::GetFileAttributesA(data_sys::get_path(name));
	}
	data_ent::~data_ent()
	{
	}
	// --setters
	// --operators
	// --==<core_methods>==--
	bit data_ent::save_file(cstr file_path)
	{
		return false;
	}
	bit data_ent::load_file(cstr file_path) {
		return false;
	}
	// --==</core_methods>==--
}