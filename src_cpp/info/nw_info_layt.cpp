#include "nw_lib_pch.hpp"
#include "nw_info_layt.h"
#if (defined NW_API)
namespace NW
{
	info_elem::info_elem() :
		m_enum(NW_DEFAULT_VAL),
		name("default"), idx(0u), offset(0u)
	{
	}
	info_elem::info_elem(cstr name, cenum_id tenum) :
		m_enum(tenum),
		name(name), idx(0u), offset(0u)
	{
	}
	info_elem::info_elem(cstr name, cenum_id tenum, v1u index) :
		m_enum(tenum),
		name(name), idx(index), offset(0u)
	{
	}
	info_elem::info_elem(cstr name, cenum_id tenum, v1u index, size offset_size) :
		m_enum(tenum),
		name(name), idx(index), offset(offset_size)
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