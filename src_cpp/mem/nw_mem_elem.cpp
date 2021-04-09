#include "nw_lib_pch.hpp"
#include "nw_mem_elem.h"
#if (defined NW_API)
#include "nw_mem_sys.h"
namespace NW
{
	mem_elem::mem_elem(cstr name) :
		m_name(NW_DEFAULT_STR),
		m_type(type_info::get<mem_elem>().id),
		m_size(type_info::get<mem_elem>().size),
		m_data(NW_NULL),
		m_offset(NW_NULL),
		m_elems(elems())
	{
		strcpy_s(m_name, NW_MAX_NAME, name);
	}
	mem_elem::mem_elem(cstr name, celems& elements) :
		m_name(NW_DEFAULT_STR),
		m_type(type_info::get<mem_elem>().id),
		m_size(type_info::get<mem_elem>().size),
		m_data(NW_NULL),
		m_offset(NW_NULL),
		m_elems(elems())
	{
		strcpy_s(m_name, NW_MAX_NAME, name);
		for (auto& ielem : elements) {
			if (ielem.is_table()) {
				add_elem(ielem.get_name(), ielem.get_elems());
			}
			else {
				add_elem(ielem.get_name(), ielem.get_type());
			}
		}
	}
	mem_elem::mem_elem(cstr name, ctype tid, ptr buffer, size offset) :
		m_name(NW_DEFAULT_STR),
		m_type(tid),
		m_size(type_info::get(tid).size),
		m_data(static_cast<data>(buffer)),
		m_offset(offset),
		m_elems(elems())
	{
		strcpy_s(m_name, NW_MAX_NAME, name);
	}
	mem_elem::mem_elem(celem& copy) :
		m_name(NW_DEFAULT_STR),
		m_type(copy.m_type),
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size),
		m_elems(copy.m_elems)
	{
		strcpy_s(m_name, NW_MAX_NAME, copy.get_name());
	}
	mem_elem::mem_elem(elem&& copy) :
		m_name(NW_DEFAULT_STR),
		m_type(copy.m_type),
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size),
		m_elems(copy.m_elems)
	{
		strcpy_s(m_name, NW_MAX_NAME, copy.get_name());
	}
	mem_elem::~mem_elem()
	{
	}
	// --setters
	void mem_elem::set_data(ctype tid, cptr buffer) {
		NW_CHECK(is_type(tid), "incompatible type!", return);
		NW_CHECK(m_data != NW_NULL, "there is no data!", return);
		NW_CHECK(m_size >= 1u, "there is no data!", return);

		memcpy(get_data(), buffer, m_size);
	}
	mem_elem::elem& mem_elem::add_elem(cstr key, celems& elements) {
		auto& element = add_elem(key, type_info::get_id<mem_elem>());
		for (auto& ielem : elements) {
			if (ielem.is_table()) {
				element.add_elem(ielem.get_name(), ielem.get_elems());
			}
			else {
				element.add_elem(ielem.get_name(), ielem.get_type());
			}
		}
		return element;
	}
	mem_elem::elem& mem_elem::add_elem(cstr key, ctype tid) {
		NW_CHECK(is_table(), "incompatible type!", return *this);
		
		sbyte temp[NW_MAX_NAME] { NW_NULL };
		if (key == NW_NULL) { sprintf_s(temp, "%d", get_count()); }
		else { strcpy_s(temp, key); }
		if (type_info::get_id<mem_elem>() == tid) { m_elems.push_back(elem(temp, elems())); }
		else { m_elems.push_back(elem(temp, tid, m_data, m_size + m_offset)); }
		
		return m_elems.back();
	}
	void mem_elem::rmv_elem(cv1u key) {
		NW_CHECK(is_table(), "incompatible type", return);
		NW_CHECK(has_elem(key), "out of range!", return);

		m_elems.erase(m_elems.begin() + key);
	}
	void mem_elem::rmv_elem(cstr key) {
		NW_CHECK(is_table(), "incompatible type", return);
		NW_CHECK(has_elem(key), "not found!", return);

		for (elem_iter& ie = m_elems.begin(); ie != m_elems.end(); ie++) {
			if (ie->is_name(key)) { m_elems.erase(ie); }
		}
	}
	// --operators
	// // data
	void mem_elem::operator=(celem& copy) {
		NW_CHECK(is_type(copy.m_type), "incompatible type!", return);
		
		strcpy_s(&m_name[0], NW_MAX_NAME, copy.get_name());
		m_data = copy.m_data;
		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_elems = copy.m_elems;
	}
	void mem_elem::operator=(elem&& copy) {
		NW_CHECK(is_type(copy.m_type), "incompatible type!", return);
		
		strcpy_s(&m_name[0], NW_MAX_NAME, copy.get_name());
		m_data = copy.m_data;
		m_size = copy.m_size;
		m_offset = copy.m_offset;
		m_elems = copy.m_elems;
	}
	// // other
	stm_out& mem_elem::operator<<(stm_out& stm) const {
		if (is_table()) {
			stm << "{";
			stm << "name:" << get_name() << ";";
			stm << "type:" << get_type_info() << ";";
			stm << "size:" << get_size() << ";";
			stm << "offset:" << get_offset() << ";";
			stm << "elements:{" << NW_STR_EOL << "\t";
			stm << "count:" << get_count() << ";" << NW_STR_EOL << "\t";
			for (v1u ie = 0u; ie < get_count(); ie++) {
				stm << "[" << ie << "]:" << get_elem(ie) << ";" << NW_STR_EOL << "\t";
			}
			stm << "}" << NW_STR_EOL;
		}
		else {
			stm << "{";
			stm << "name:" << get_name() << ";";
			stm << "type:" << get_type_info() << ";";
			stm << "size:" << get_size() << ";";
			stm << "offset:" << get_offset() << ";";
			stm << "data:"; get_data(); stm << ";";
			stm << "}";
		}
		return stm;
	}
	stm_in& mem_elem::operator>>(stm_in& stm) {
		sbyte temp[256];
		if (is_table()) {
		}
		else {
			stm >> temp
				>> m_name >> temp
				>> m_type >> temp
				>> m_size >> temp
				>> m_offset >> temp;
		}
		return stm;
	}
	// --==<core_methods>==--
	v1b mem_elem::remake(ptr buffer, size offset) {
		m_data = static_cast<data>(buffer);
		m_offset = offset;
		NW_CHECK(m_data != NW_NULL, "no data!", return NW_FALSE);

		if (is_elem()) {
			NW_CHECK(m_size != NW_NULL, "no size!", return NW_FALSE);
		}
		else if (is_table()) {
			NW_CHECK(get_count() >= 1u, "no elems", return NW_FALSE);
			
			m_size = 0u;
			for (v1u ie = 0u; ie < get_count(); ie++) {
				auto& ielem = get_elem(ie);
				NW_CHECK(ielem.remake(m_data, m_offset + m_size), "failed to remake", return NW_FALSE);
				m_size += ielem.get_size();
			}
		}
		else {
			NW_ERROR("undefined type", return NW_FALSE);
		}

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API