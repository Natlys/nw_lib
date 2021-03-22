#include <nwl_pch.hpp>
#include "data_layt.h"

namespace NW
{
	data_elem::data_elem(cstr name, data_types type, ui32 count, ui32 index, size offset_size) :
		name(name), type(type), count(count), idx(index), offset(offset_size)
	{
	}
}
namespace NW
{
	data_layt::data_layt() :
		m_elems(elems()) 
	{
	}
	// setters
	void data_layt::add_elem(celem& element, ui8 nof_elements) {
		while (nof_elements-- != 0) {
			m_elems.push_back(element);
		}
	}
	void data_layt::rmv_elem(ui8 idx) {
		m_elems.erase(m_elems.begin() + idx % m_elems.size());
	}
	// --==<core_methods>==--
	// --==</core_methods>==--
}