#include "nw_lib_pch.hpp"
#include "nw_mem_elem.h"
#if (defined NW_API)
#include "nw_mem_sys.h"
namespace NW
{
	mem_elem::mem_elem(ctype tid, ptr buffer, size offset) :
		m_type(tid),
		m_size(type_info::get(tid).size),
		m_data(static_cast<data>(buffer)),
		m_offset(offset)
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
	mem_elem::~mem_elem()
	{
	}
	// --setters
	void mem_elem::set_data(ctype tid, cptr buffer) {
		NW_CHECK(check_type(tid), "incompatible type!", return);
		NW_CHECK(m_data != NW_NULL, "there is no data!", return);

		memcpy(m_data + m_offset, buffer, m_size);
	}
	// void mem_elem::set_count(csize nof_elems) { m_size = get_type_size() * nof_elems; }
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
	stm_out& mem_elem::operator<<(stm_out& stm) const {
		
		stm << "mem_elem" << "{" << NW_STR_EOL;
		stm << "type:" << m_type << ";" << NW_STR_EOL;
		stm << "size:" << m_size << ";" << NW_STR_EOL;
		stm << "offset:" << m_offset << ";" << NW_STR_EOL;
		stm << "data:"; stm.write(reinterpret_cast<char*>(get_data()), m_size); stm << ";";
		stm << "};" << NW_STR_EOL;
		return stm;
	}
	stm_in& mem_elem::operator>>(stm_in& stm) {
		sbyte temp[256];
		stm >> temp
			>> m_type >> temp
			>> m_size >> temp
			>> m_offset >> temp;
		return stm;
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
	mem_array::mem_array(ctype tid, cv1u nof_elems, ptr buffer, csize offset) :
		mem_elem(tid, buffer, offset)
	{
		m_size = 0u;
		set_elems(tid, nof_elems);
	}
	mem_array::mem_array(carr& copy) :
		mem_elem(copy),
		m_elems(copy.m_elems)
	{
	}
	mem_array::mem_array(arr&& copy) :
		mem_elem(copy),
		m_elems(copy.m_elems)
	{
	}
	mem_array::~mem_array()
	{
	}
	// --setters
	void mem_array::set_type(ctype tid) {
		m_type = tid;
		// essentially recreate all elements;
		// old elements have old type and it is possible
		// to change type from an array to some value but
		// our refs can stay arrays;
		if (get_count() >= 1u) {
			set_count(get_count());
		}
	}
	void mem_array::set_count(cv1u nof_elems) {
		if (nof_elems == 0u) { m_elems.clear(); return; }
		m_elems.resize(nof_elems);
		m_size = 0u;
		if (m_type == type_info::get_id<arr>()) {
			for (v1u ie = 0u; ie < get_count(); ie++) {
				mem_ref<elem> ielem;
				ielem.make_ref<arr>(m_type, 0u, m_data, m_size + m_offset);
				m_size += ielem->get_size();
				m_elems[ie] = ielem;
			}
		}
		else if (m_type == type_info::get_id<tab>()) {
			for (v1u ie = 0u; ie < get_count(); ie++) {
				mem_ref<elem> ielem;
				ielem.make_ref<tab>(m_data, m_size + m_offset);
				m_size += ielem->get_size();
				m_elems[ie] = ielem;
			}
		}
		else {
			for (v1u ie = 0u; ie < get_count(); ie++) {
				mem_ref<elem> ielem;
				ielem.make_ref<elem>(m_type, m_data, m_size + m_offset);
				m_size += ielem->get_size();
				m_elems[ie] = ielem;
			}
		}
	}
	void mem_array::set_elems(ctype tid, cv1u nof_elems) {
		set_type(tid);
		set_count(nof_elems);
	}
	// --operators
	void mem_array::operator=(carr& copy) {
		mem_elem::operator=(copy);

		m_elems = copy.m_elems;
	}
	void mem_array::operator=(arr&& copy) {
		mem_elem::operator=(copy);

		m_elems = copy.m_elems;
	}
	stm_out& mem_array::operator<<(stm_out& stm) const {
		stm << "mem_array" << "{";
		for (v1u ie = 0u; ie < get_count(); ie++) {
			stm << "[" << ie << "]";
			stm << *m_elems[ie];
		}
		stm << "};";
		return stm;
	}
	stm_in& mem_array::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b mem_array::remake(ptr buffer, csize offset)
	{
		m_size = m_size == 0u ? 1u : m_size;
		NW_CHECK(mem_elem::remake(buffer, offset), "failed to remake", return NW_FALSE);
		NW_CHECK(get_count() >= 1u, "no elements", return NW_FALSE);
		
		m_size = 0u;
		for (v1u ie = 0u; ie < get_count(); ie++) {
			auto& ielem = get_elem(ie);
			NW_CHECK(ielem.remake(m_data, m_size + m_offset), "failed to remake!", return NW_FALSE);
			m_size += ielem.get_size();
		}

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_table::mem_table(ptr buffer, size offset) :
		mem_elem(type_info::get_id<mem_table>(), buffer, offset)
	{
		m_size = 0u;
	}
	mem_table::mem_table(ctab& copy) : 
		mem_elem(copy),
		m_elems(copy.m_elems)
	{
	}
	mem_table::mem_table(tab&& copy) :
		mem_elem(copy),
		m_elems(copy.m_elems)
	{
	}
	mem_table::~mem_table()
	{
	}
	// --setters
	mem_table::elem& mem_table::add_elem(cstr key, ctype tid) {
		NW_CHECK(!has_elem(key), "this name is already used!", return *this);
		
		m_elems.push_back(std::make_pair(key, mem_ref<elem>() ));
		m_elems.back().second.make_ref<elem>(tid, m_data, m_size + m_offset);
		m_size += m_elems.back().second->get_size();
		return m_elems.back().second;
	}
	void mem_table::rmv_elem(cstr key) {
		NW_CHECK(!has_elem(key), "not found!", return);

		for (elem_iter ie = begin(); ie != end(); ie++) {
			if (ie->first == key) {
				m_elems.erase(ie);
				return;
			}
		}
	}
	mem_table::arr& mem_table::add_arr(cstr key, ctype tid, cv1u nof_elems) {
		NW_CHECK(!has_elem(key), "this name is already used", return *this);

		m_elems.push_back({ key, mem_ref<elem>() });
		m_elems.back().second.make_ref<arr>(tid, nof_elems, m_data, m_size + m_offset);
		m_size += m_elems.back().second->get_size();
		return *m_elems.back().second.get_ref<arr>();
	}
	mem_table::tab& mem_table::add_tab(cstr key) {
		NW_CHECK(!has_elem(key), "this name is already used", return *this);

		m_elems.push_back({ key, mem_ref<elem>() });
		m_elems.back().second.make_ref<tab>(m_data, m_size + m_offset);
		m_size += m_elems.back().second->get_size();
		return *m_elems.back().second.get_ref<tab>();
	}
	// --operators
	void mem_table::operator=(ctab& copy) {
		mem_elem::operator=(copy);

		m_elems = copy.m_elems;
	}
	void mem_table::operator=(tab&& copy) {
		mem_elem::operator=(copy);
		
		m_elems = copy.m_elems;
	}
	stm_out& mem_table::operator<<(stm_out& stm) const {
		stm << "mem_table" << "{";
		for (v1u ie = 0u; ie < get_count(); ie++) {
			stm << "[" << m_elems[ie].first << "]";
			stm << *m_elems[ie].second;
		}
		stm << "};";
		return stm;
	}
	stm_in& mem_table::operator>>(stm_in& stm) {
		return stm;
	}
	// --==<core_methods>==--
	v1b mem_table::remake(ptr buffer, size offset) {
		m_size = m_size == 0u ? 1u : m_size;
		NW_CHECK(mem_elem::remake(buffer, offset), "failed to remake!", return NW_FALSE);
		NW_CHECK(get_count() >= 1u, "no elements!", return NW_FALSE);
		
		m_size = 0u;
		for (v1u ie = 0u; ie < get_count(); ie++) {
			auto& ielem = get_elem(ie);
			NW_CHECK(ielem.remake(m_data, m_size + m_offset), "failed to remake!", return NW_FALSE);
			m_size += ielem.get_size();
		}

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API