#include "nwlib_pch.hpp"
#include "nwlib_std_vlayt.h"
#if (defined NW_API)
namespace NWLIB
{
	velem::velem() :
		name("default"), idx(0u), offset(0u),
		m_type(VTYPE_DEFAULT), m_count(1u)
	{
	}
	velem::velem(cstr name, vtype type, v1u count) :
		name(name), idx(0u), offset(0u),
		m_type(type), m_count(count)
	{
	}
	velem::velem(cstr name, vtype type, v1u count, v1u index) :
		name(name), idx(index), offset(0u),
		m_type(type), m_count(count)
	{
	}
	velem::velem(cstr name, vtype type, v1u count, v1u index, size offset_size) :
		name(name), idx(index), offset(offset_size),
		m_type(type), m_count(count)
	{
	}
}
namespace NWLIB
{
	vlayout::vlayout() :
		m_elems(elems())
	{
	}
	vlayout::vlayout(elems&& elements) :
		m_elems(elements)
	{
	}
	// setters
	void vlayout::set_elems(celems& elements) { m_elems = std::move(elements); }
	void vlayout::set_elems(elems&& elements) { m_elems = std::move(elements); }
	void vlayout::add_elem(elem&& element) {
		m_elems.push_back(element);
	}
	void vlayout::add_elem(celem& element, v1u nof_elements) {
		while (nof_elements-- != 0) {
			m_elems.push_back(element);
		}
	}
	void vlayout::rmv_elem(v1u idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}
#endif	// NW_API