#include "nw_lib_pch.hpp"
#include "nw_mem_layt.h"
#if (defined NW_API)
#	include "../io/nw_io_stm.h"
#	include "nw_mem_sys.h"
namespace NW
{
	mem_layt::mem_layt(cstr key) :
		t_tree_cmp(key), a_io_cmp(), a_mem_cmp(),
		m_size(type_info::get<tree_t>().size),
		m_data(NW_NULL),
		m_offset(NW_NULL)
	{
	}
	mem_layt::mem_layt(cstr key, elems_tc& elements) :
		t_tree_cmp(key, elements), a_io_cmp(), a_mem_cmp(),
		m_size(type_info::get<tree_t>().size),
		m_data(NW_NULL),
		m_offset(NW_NULL)
	{
	}
	mem_layt::mem_layt(cstr key, vtype_tc type, ptr_t buffer, size_t offset) :
		t_tree_cmp(key, type), a_io_cmp(), a_mem_cmp(),
		m_size(type_info::get(type).size),
		m_data(static_cast<byte_t*>(buffer)),
		m_offset(offset)
	{
	}
	mem_layt::mem_layt(elem_tc& copy) :
		t_tree_cmp(copy), a_io_cmp(copy), a_mem_cmp(copy),
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size)
	{
	}
	mem_layt::mem_layt(elem_t&& copy) :
		t_tree_cmp(copy), a_io_cmp(copy), a_mem_cmp(copy),
		m_data(copy.m_data),
		m_offset(copy.m_offset),
		m_size(copy.m_size)
	{
	}
	mem_layt::~mem_layt()
	{
	}
	// --setters
	v1nil mem_layt::set_data(ptr_tc buffer, vtype_tc type) {
		NW_CHECK(has_vtype(type), "type error!", return);
		NW_CHECK(m_data != NW_NULL, "data error!", return);
		NW_CHECK(m_size >= 1u, "size error!", return);

		memcpy(get_data(), buffer, m_size);
	}
	// --operators
	stm_out& mem_layt::operator<<(stm_out& stm) const {
		stm << "{";
		stm << "name:" << get_key() << ";";
		stm << "vtype:" << get_vtype_info() << ";" << NW_STR_EOL;
		stm << "size:" << get_size() << ";" << NW_STR_EOL;
		stm << "offset:" << get_offset() << ";" << NW_STR_EOL;
		stm << "elements:" << "{";
		stm << "count:" << get_count() << ";";
		for (auto& inode : get_nodes()) { stm << inode; }
		stm << "\t" << "}" << ":elements" << NW_STR_EOL;
		stm << "}" << ":[" << get_key() << "]" << ";" << NW_STR_EOL;

		return stm;
	}
	stm_in& mem_layt::operator>>(stm_in& stm) {
		sbyte_t buf[256]{ NW_NULL };
		m_nodes.clear();
		stm.getline(buf, sizeof(buf), ':'); // name:
		stm >> m_key;
		stm.getline(buf, sizeof(buf), ':'); // type:
		stm.getline(buf, sizeof(buf), ':'); // {id:...
		stm >> m_vtype;
		stm.getline(buf, sizeof(buf), '}'); // ...}
		stm.getline(buf, sizeof(buf), ':'); // size:
		stm >> m_size;
		stm.getline(buf, sizeof(buf), ':'); // offset:
		stm >> m_offset;
		stm.getline(buf, sizeof(buf), ':'); // elements:
		stm.getline(buf, sizeof(buf), ':'); // count:
		v1s count;
		stm >> count;
		if (count != 0) {
			for (v1s ei = 0u; ei < count; ei++) {
				m_nodes.push_back(mem_layt());
				stm >> m_nodes.back();
			}
		}
		return stm;
	}
	// --==<core_methods>==--
	v1bit mem_layt::remake(ptr_t buffer, size_t offset)
	{
		m_data = static_cast<byte_t*>(buffer);
		m_offset = offset;
		// NW_CHECK(m_data != NW_NULL, "no data!", return NW_FALSE);

		if (is_leaf()) { NW_CHECK(m_size != NW_NULL, "no size!", return NW_FALSE); }
		else if (is_tree()) {
			NW_CHECK(get_count() >= 1u, "no leafs", return NW_FALSE);
			m_size = 0u;
			for (v1u ie = 0u; ie < get_count(); ie++) {
				auto& ielem = get_node(ie);
				NW_CHECK(ielem.remake(m_data, m_offset + m_size), "failed to remake", return NW_FALSE);
				m_size += ielem.get_size();
			}
		}
		else { NW_ERROR("type error!", return NW_FALSE); }

		return NW_TRUE;
	}
	v1bit mem_layt::moveto(cv1s steps) {
		NW_CHECK(steps != NW_NULL, "no difference!", return NW_FALSE);
		NW_CHECK(m_data != NW_NULL, "no data!", return NW_FALSE);
		return remake(m_data, m_offset + steps * get_size());
	}
	// --==</core_methods>==--
}
#endif	// NW_API