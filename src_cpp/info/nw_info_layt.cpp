#include "nw_lib_pch.hpp"
#include "nw_info_layt.h"
#if (defined NW_API)
namespace NW
{
	info_elem::info_elem() :
		name("default"), idx(0u), offset(0u),
		m_type(VTYPE_DEFAULT), m_count(1u)
	{
	}
	info_elem::info_elem(cstr name, vtype type, v1u count) :
		name(name), idx(0u), offset(0u),
		m_type(type), m_count(count)
	{
	}
	info_elem::info_elem(cstr name, vtype type, v1u count, v1u index) :
		name(name), idx(index), offset(0u),
		m_type(type), m_count(count)
	{
	}
	info_elem::info_elem(cstr name, vtype type, v1u count, v1u index, size offset_size) :
		name(name), idx(index), offset(offset_size),
		m_type(type), m_count(count)
	{
	}
}
namespace NW
{
	info_layt::info_layt() :
		m_elems(elems())
	{
	}
	info_layt::info_layt(elems&& elements) :
		m_elems(elements)
	{
	}
	// setters
	void info_layt::set_elems(celems& elements) { m_elems = std::move(elements); }
	void info_layt::set_elems(elems&& elements) { m_elems = std::move(elements); }
	void info_layt::add_elem(elem&& element) {
		m_elems.push_back(element);
	}
	void info_layt::add_elem(celem& element, v1u nof_elements) {
		while (nof_elements-- != 0) {
			m_elems.push_back(element);
		}
	}
	void info_layt::rmv_elem(v1u idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
#endif	// NW_API