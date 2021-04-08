#include "nw_lib_pch.hpp"
#include "nw_mem_elem.h"
#if (defined NW_API)
#include "nw_mem_sys.h"
namespace NW
{
	mem_elem::mem_elem(type tenum, ptr buffer, size offset) :
		m_data(static_cast<data>(buffer)),
		m_offset(offset),
		m_size(info_type::get(tenum).elem_size),
		m_type(tenum)
	{
	}
	mem_elem::mem_elem(celem& copy) :
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size),
		m_type(copy.m_type)
	{
	}
	mem_elem::mem_elem(elem&& copy) :
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size),
		m_type(copy.m_type)
	{
	}
	// --setters
	void mem_elem::set_data(type tenum, cptr buffer) {
		NW_CHECK(check_type(tenum), "incompatible type!", return);
		NW_CHECK(m_data != NW_NULL, "there is no data!", return);

		memcpy(m_data + m_offset, buffer, m_size);
	}
	void mem_elem::set_count(size nof_elements) {
		m_size = get_type_size() * nof_elements;
		for (v1u ie = 0u; ie < nof_elements; ie++) {
			*get_elem(ie) = elem(m_type, m_data, m_offset + ie * get_type_size());
		}
	}
	// --operators
	void mem_elem::operator=(celem& copy) {
		NW_CHECK(check_type(copy.m_type), "incompatible type!", return);
		
		m_data = copy.m_data;
		m_size = copy.m_size;
		m_offset = copy.m_offset;
	}
	void mem_elem::operator=(elem&& copy) {
		NW_CHECK(check_type(copy.m_type), "incompatible type!", return);
		
		m_data = copy.m_data;
		m_size = copy.m_size;
		m_offset = copy.m_offset;
	}
	// --==<core_methods>==--
	v1b mem_elem::remake(ptr buffer, size offset) {
		NW_CHECK(buffer != NW_NULL, "there is no data!", return NW_FALSE);
		NW_CHECK(m_size != NW_NULL, "there is no size!", return NW_FALSE);
		
		m_data = static_cast<data>(buffer);
		m_offset = offset;
		
		return NW_TRUE;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_table::mem_table(ptr buffer, size offset) :
		mem_elem(NW_TYPE_DEFAULT, buffer, offset)
	{
		m_data = reinterpret_cast<data>(mem_sys::get().new_one<elems>());
	}
	mem_table::mem_table(ctab& copy)
	{
		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_data = copy.m_data;
		// m_data = reinterpret_cast<data>(mem_sys::get().new_one<elems>());
		// get_elems() = copy.get_elems();
	}
	mem_table::mem_table(tab&& copy)
	{
		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_data = copy.m_data;
		// m_data = reinterpret_cast<data>(mem_sys::get().new_one<elems>());
		// get_elems() = copy.get_elems();
	}
	mem_table::~mem_table()
	{
		// mem_sys::get().del_one<elems>(reinterpret_cast<elems*>(m_data));
	}
	// --setters
	mem_table::elem& mem_table::add_elem(cstr key, ctype tenum) {
		NW_CHECK(!has_elem(key), "the name is already used!", return *this);
		
		auto& m_elems = get_elems();
		m_elems.push_back(std::make_pair(key, mem_elem(tenum)));
		m_size -= sizeof(elem);
		return m_elems.back().second;
	}
	void mem_table::rmv_elem(cstr key) {
		NW_CHECK(!has_elem(key), "not found!", return);

		for (elem_iter ie = begin(); ie != end(); ie++) {
			if (ie->first == key) {
				get_elems().erase(ie);
				m_size -= sizeof(elem);
				return;
			}
		}
	}
	// --operators
	void mem_table::operator=(ctab& copy) {
		NW_CHECK(check_type(copy.m_type), "incompatible type!", return);

		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_data = copy.m_data;
		// mem_sys::get().del_one<elems>(reinterpret_cast<elems*>(m_data));
		// m_data = reinterpret_cast<data>(mem_sys::get().new_one<elems>());
		// get_elems() = copy.get_elems();
	}
	void mem_table::operator=(tab&& copy) {
		NW_CHECK(check_type(copy.m_type), "incompatible type!", return);

		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_data = copy.m_data;
		// mem_sys::get().del_one<elems>(reinterpret_cast<elems*>(m_data));
		// m_data = reinterpret_cast<data>(mem_sys::get().new_one<elems>());
		// get_elems() = copy.get_elems();
	}
	// --==<core_methods>==--
	v1b mem_table::remake(ptr buffer, size offset) {
		NW_CHECK(mem_elem::remake(m_data, offset), "failed to remake!", return NW_FALSE);
		NW_CHECK(get_count() >= 1u, "no elements!", return NW_FALSE);
		
		m_size = 0u;
		for (v1u ie = 0u; ie < get_count(); ie++) {
			auto& ielem = get_elems()[ie].second;
			//data ibuf = m_data + m_size;
			NW_CHECK(ielem.remake(buffer, m_size + offset), "failed to remake!", return NW_FALSE);
			m_size += ielem.get_size();
		}

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API