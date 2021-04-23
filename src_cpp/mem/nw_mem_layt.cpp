#include "nw_lib_pch.hpp"
#include "nw_mem_layt.h"
#if (defined NW_API)
#	include "../iop/nw_iop_stm.h"
#	include "nw_mem_sys.h"
namespace NW
{
	mem_layt::mem_layt(cstr_t key) :
		t_tree_cmp(key), a_mem_cmp(), a_iop_cmp(),
		m_space(type_info::get<tree_t>().size),
		m_offset(NW_NULL)
	{
	}
	mem_layt::mem_layt(cstr_t key, elems_tc& elements) :
		t_tree_cmp(key, elements), a_mem_cmp(), a_iop_cmp(),
		m_space(type_info::get<tree_t>().size),
		m_offset(NW_NULL)
	{
	}
	mem_layt::mem_layt(elems_tc& elements) :
		mem_layt(NW_DEFAULT_STR, elements)
	{
	}
	mem_layt::mem_layt(cstr_t key, vtype_tc type, size_tc offset) :
		t_tree_cmp(key, type), a_mem_cmp(), a_iop_cmp(),
		m_space(type_info::get(type).size),
		m_offset(offset)
	{
	}
	mem_layt::mem_layt(vtype_tc type, size_tc offset) :
	mem_layt(NW_DEFAULT_STR, type, offset)
	{
	}
	mem_layt::mem_layt(elem_tc& copy) :
		t_tree_cmp(copy), a_mem_cmp(copy), a_iop_cmp(copy),
		m_space(copy.m_space),
		m_offset(copy.m_offset)
	{
	}
	mem_layt::mem_layt(elem_t&& copy) :
		t_tree_cmp(copy), a_mem_cmp(copy), a_iop_cmp(copy),
		m_space(copy.m_space),
		m_offset(copy.m_offset)
	{
	}
	mem_layt::~mem_layt()
	{
	}
	// --setters
	v1nil mem_layt::set_offset(size_tc offset) {
		m_offset = offset;
	}
	// --operators
	op_stream_t& mem_layt::operator<<(op_stream_t& stm) const {
		stm << "{";
		stm << "name:" << get_name() << ";";
		stm << "vtype:" << get_vtype_info() << ";" << NW_STR_EOL;
		stm << "space:" << get_space() << ";" << NW_STR_EOL;
		stm << "offset:" << get_offset() << ";" << NW_STR_EOL;
		stm << "elements:" << "{";
		stm << "count:" << get_count() << ";";
		for (auto& inode : get_nodes()) { stm << inode; }
		stm << "\t" << "}" << ":elements" << NW_STR_EOL;
		stm << "}" << ":[" << get_name() << "]" << ";" << NW_STR_EOL;

		return stm;
	}
	ip_stream_t& mem_layt::operator>>(ip_stream_t& stm) {
		byte_t buf[256]{ NW_NULL };
		m_nodes.clear();
		stm.getline(buf, sizeof(buf), ':'); // name:
		stm >> m_name;
		stm.getline(buf, sizeof(buf), ':'); // type:
		stm.getline(buf, sizeof(buf), ':'); // {id:...
		stm >> m_vtype;
		stm.getline(buf, sizeof(buf), '}'); // ...}
		stm.getline(buf, sizeof(buf), ':'); // space:
		stm >> m_space;
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
	v1bit mem_layt::remake()
	{
		if (is_leaf()) { m_space = get_vtype_size(); }
		else if (is_tree()) {
			NW_CHECK(has_node(), "no leafs", return NW_FALSE);
			m_space = NW_NULL;
			for (v1u ie = 0u; ie < get_count(); ie++) {
				auto& ielem = get_node(ie);
				NW_CHECK(ielem.remake(m_space + m_offset), "failed to remake", return NW_FALSE);
				m_space += ielem.get_space();
			}
		}
		else { NW_ERROR("type error!", return NW_FALSE); }

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
#endif	// NW_API