#ifndef NW_MEM_LAYOUT_H
#define NW_MEM_LAYOUT_H
#include "nw_lib_core.hpp"
	#if (defined NW_API)
#	include "../std/nw_std_tree.h"
#	include "../info/nw_info_type.h"
#	include "../io/nw_io_cmp.h"
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
	class NW_API mem_layt : public t_tree_cmp<mem_layt>, public a_io_cmp, public a_mem_cmp
	{
	public:
		using elem_t = mem_layt;
		using elem_tc = const elem_t;
		using elems_t = darray<mem_layt>;
		using elems_tc = const elems_t;
	public:
		mem_layt(cstr key = "root");
		mem_layt(cstr key, elems_tc& elements);
		mem_layt(cstr key, vtype_tc type, ptr_t buffer = NW_NULL, size_t offset = NW_NULL);
		mem_layt(elem_tc& copy);
		mem_layt(elem_t&& copy);
		~mem_layt();
		// --getters
		inline byte_t* get_data()        { return m_data + m_offset; }
		inline byte_tc* get_data() const { return m_data + m_offset; }
		inline byte_t* get_data(vtype_tc type)        { NW_CHECK(has_vtype(type), "type error!", return NW_NULL); return get_data(); }
		inline byte_tc* get_data(vtype_tc type) const { NW_CHECK(has_vtype(type), "type error!", return NW_NULL); return get_data(); }
		template<typename tname> tname& get()             { return *get_data<tname>(); }
		template<typename tname> const tname& get() const { return *get_data<tname>(); }
		template<typename tname> tname* get_data()             { return reinterpret_cast<tname*>(get_data(type_info::get_type<tname>())); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(get_data(type_info::get_type<tname>())); }
		inline size_tc get_offset() const { return m_offset; }
		inline size_tc get_size() const   { return m_size; }
		// --setters
		v1nil set_data(ptr_tc buffer, vtype_tc type);
		template<typename tname> v1nil set_data(const tname* buffer) { set_data(buffer, type_info::get_type<tname>()); }
		template<typename tname> v1nil set(const tname& buffer) { set_data<tname>(&buffer); }
		// --operators
		template<typename tname> operator tname*()              { return get_data<tname>(); }
		template<typename tname> operator const tname*() const  { return get_data<tname>(); }
		template<typename tname> operator tname&()              { return get<tname>(); }
		template<typename tname> operator const tname& () const { return get<tname>(); }
		inline v1nil operator=(elem_tc& copy) { t_tree_cmp::operator=(copy); m_data = copy.m_data; m_size = copy.m_size; m_offset = copy.m_offset; }
		inline v1nil operator=(elem_t&& copy) { t_tree_cmp::operator=(copy); m_data = copy.m_data; m_size = copy.m_size; m_offset = copy.m_offset; }
		template<typename tname> v1nil operator=(const tname* buffer) { set_data<tname>(buffer); }
		template<typename tname> v1nil operator=(const tname& buffer) { set<tname>(buffer); }
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		v1bit remake(ptr_t buffer = NW_NULL, size_t offset = NW_NULL);
		v1bit moveto(cv1s steps);
	protected:
		byte_t* m_data;
		size_t m_offset;
		size_t m_size;
	};
}
#	endif	// NW_API
#endif	// NW_MEM_LAYOUT_H