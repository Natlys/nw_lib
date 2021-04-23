#ifndef NW_MEM_LAYOUT_H
#define NW_MEM_LAYOUT_H
#include "nw_lib_core.hpp"
	#if (defined NW_API)
#	include "../std/nw_std_tree.h"
#	include "../info/nw_info_type.h"
#	include "../iop/nw_iop_cmp.h"
#	include "nw_mem_cmp.h"
#	include "nw_mem_ref.h"
namespace NW
{
	/// memory_element class
	/// description:
	/// --this is a data structure which allows to:
	/// construct tables out of elements;
	/// describe any format i like;
	/// set bytes of a given buffer;
	class NW_API mem_layt : public t_tree_cmp<mem_layt>, public a_mem_cmp, public a_iop_cmp
	{
	public:
		using tree_t = t_tree_cmp<mem_layt>;
		using tree_tc = const tree_t;
		using elem_t = mem_layt;
		using elem_tc = const elem_t;
		using elems_t = tree_t::nodes_t;
		using elems_tc = tree_t::nodes_tc;
	public:
		mem_layt(cstr_t key = "root");
		mem_layt(cstr_t key, elems_tc& elements);
		mem_layt(elems_tc& elements);
		mem_layt(cstr_t key, vtype_tc type, size_tc offset = NW_NULL);
		mem_layt(vtype_tc type, size_tc offset = NW_NULL);
		mem_layt(elem_tc& copy);
		mem_layt(elem_t&& copy);
		~mem_layt();
		// --getters
		inline size_tc get_space() const  { return m_space; }
		inline size_tc get_offset() const { return m_offset; }
		// --setters
		v1nil set_offset(size_tc offset);
		// --predicates
		// --operators
		inline v1nil operator=(elem_tc& copy) { t_tree_cmp::operator=(copy); NW_CHECK(remake(copy.m_offset), "failed remake!", return); }
		inline v1nil operator=(elem_t&& copy) { t_tree_cmp::operator=(copy); NW_CHECK(remake(copy.m_offset), "failed remake!", return); }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		virtual v1bit remake();
		inline v1bit remake(size_tc offset) { set_offset(offset); return remake(); }
	protected:
		size_t m_space;
		size_t m_offset;
	};
	template<typename tname>
	class NW_API t_mem_layt : public mem_layt
	{
	public:
		t_mem_layt(cstr_t key = NW_DEFAULT_STR, size_tc offset = NW_NULL) :
			mem_layt(key, type_info::get_type<tname>(), offset) { }
	};
}
#	endif	// NW_API
#endif	// NW_MEM_LAYOUT_H