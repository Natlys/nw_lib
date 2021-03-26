#include <nwl_pch.hpp>
#include "data_layt.h"

namespace NW
{
	data_elem::data_elem() :
		name("default"), type(NTP_DEFAULT), count(1u), idx(0u), offset(0u)
	{
	}
	data_elem::data_elem(cstr name, native_types type, v1ui count) :
		name(name), type(type), count(count), idx(0u), offset(0u)
	{
	}
	data_elem::data_elem(cstr name, native_types type, v1ui count, v1ui index) :
		name(name), type(type), count(count), idx(index), offset(0u)
	{
	}
	data_elem::data_elem(cstr name, native_types type, v1ui count, v1ui index, size offset_size) :
		name(name), type(type), count(count), idx(index), offset(offset_size)
	{
	}
}
namespace NW
{
	data_layt::data_layt() :
		m_elems(elems()), m_stride(0u)
	{
	}
	data_layt::data_layt(elems&& elements) :
		m_elems(elements), m_stride(0u)
	{
	}
	// setters
	void data_layt::set_elems(celems& elements) { m_elems = std::move(elements); }
	void data_layt::set_elems(elems&& elements) { m_elems = std::move(elements); }
	void data_layt::add_elem(elem&& element) {
		m_elems.push_back(element);
	}
	void data_layt::add_elem(celem& element, v1ui8 nof_elements) {
		while (nof_elements-- != 0) {
			m_elems.push_back(element);
		}
	}
	void data_layt::rmv_elem(v1ui8 idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}