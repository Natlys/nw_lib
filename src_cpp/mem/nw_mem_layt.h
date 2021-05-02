#ifndef NW_MEM_LAYOUT_H
#define NW_MEM_LAYOUT_H
#include "nw_lib_core.hpp"
	#if (defined NW_API)
#	include "../std/nw_std_tree.h"
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
	class NW_API mem_layt : public t_tree_cmp<mem_layt>, public a_mem_user, public a_iop_cmp
	{
	public:
		using layt_t = mem_layt;
		using layt_tc = const layt_t;
		using tree_t = t_tree_cmp<mem_layt>;
		using tree_tc = const tree_t;
		using elem_t = mem_layt;
		using elem_tc = const elem_t;
		using elems_t = tree_t::nodes_t;
		using elems_tc = tree_t::nodes_tc;
		using elem_list_t = tree_t::node_list_t;
		using elem_list_tc = tree_t::node_list_tc;
	public:
		mem_layt();
		mem_layt(cstr_t key);
		mem_layt(cstr_t key, elems_tc& elems);
		mem_layt(elems_tc& elems);
		mem_layt(cstr_t key, elem_list_tc& elems);
		mem_layt(elem_list_tc& elems);
		mem_layt(cstr_t key, type_tc type, size_tc offset = NW_NULL);
		mem_layt(type_tc type, size_tc offset = NW_NULL);
		mem_layt(elem_tc& copy);
		mem_layt(elem_t&& copy);
		~mem_layt();
		// --getters
		inline size_tc get_space() const  { return m_space; }
		inline size_tc get_offset() const { return m_offset; }
		// --setters
		layt_t& set_offset(size_tc offset);
		// --predicates
		inline v1bit has_offset(size_t offset = 1u) const { return m_offset >= offset; };
		inline v1bit has_space(size_t space = 1u) const { return m_space >= space; };
		// --operators
		inline v1nil operator=(elem_tc& copy) { t_tree_cmp::operator=(copy); NW_CHECK(remake(copy.m_offset), "remake error!", return); }
		inline v1nil operator=(elem_t&& copy) { t_tree_cmp::operator=(copy); NW_CHECK(remake(copy.m_offset), "remake error!", return); }
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