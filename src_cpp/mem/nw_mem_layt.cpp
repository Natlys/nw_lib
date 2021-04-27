#include "nw_lib_pch.hpp"
#include "nw_mem_layt.h"
#if (defined NW_API)
#	include "../iop/nw_iop_stm.h"
#	include "nw_mem_sys.h"
namespace NW
{
	mem_layt::mem_layt() : t_tree_cmp(), a_mem_user(), a_iop_cmp(), m_space(type_info::get<tree_t>().size), m_offset(NW_NULL) { }
	mem_layt::mem_layt(cstr_t key) : mem_layt() { set_name(key); }
	mem_layt::mem_layt(cstr_t key, elems_tc& elems) : mem_layt() { set_name(key); set_nodes(elems); }
	mem_layt::mem_layt(elems_tc& elems) : mem_layt() { set_nodes(elems); }
	mem_layt::mem_layt(cstr_t key, init_list_tc<elem_t>& elems) : mem_layt() { set_name(key); set_nodes(elems); }
	mem_layt::mem_layt(init_list_tc<elem_t>& elems) : mem_layt() { set_nodes(elems); }
	mem_layt::mem_layt(cstr_t key, type_tc type, size_tc offset) : mem_layt() { set_name(key); set_type(type); set_offset(offset); }
	mem_layt::mem_layt(type_tc type, size_tc offset) : mem_layt() { set_type(type); set_offset(offset); }
	mem_layt::mem_layt(elem_tc& copy) : mem_layt() { operator=(copy); }
	mem_layt::mem_layt(elem_t&& copy) : mem_layt() { operator=(copy); }
	mem_layt::~mem_layt() { }
	// --setters
	v1nil mem_layt::set_offset(size_tc offset) {
		m_offset = offset;
	}
	// --operators
	op_stream_t& mem_layt::operator<<(op_stream_t& stm) const {
		stm << "{";
		stm << "name:" << get_name() << ";";
		stm << "type:" << get_type() << ";";
		stm << "space:" << get_space() << ";";
		stm << "offset:" << get_offset() << ";";
		stm << "count:" << get_count() << ";";
		size_t itr = 0u; for (auto& inode : get_nodes()) { stm << "elem[" << itr++ << "]:" << inode; }
		stm << "}" << ";";
		return stm;
	}
	ip_stream_t& mem_layt::operator>>(ip_stream_t& stm) {
		byte_t buf[256]{ NW_NULL };
		m_nodes.clear();
		stm.getline(buf, sizeof(buf), ':'); // name:
		stm >> m_name;
		stm.getline(buf, sizeof(buf), ':'); // type:
		stm.getline(buf, sizeof(buf), ':'); // {id:...
		stm >> m_type;
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
		if (is_leaf()) { m_space = get_type_size(); }
		else if (is_tree()) {
			//NW_CHECK(has_node(), "no leafs", return NW_FALSE);
			m_space = NW_NULL;
			for (auto& ielem : m_nodes) {
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