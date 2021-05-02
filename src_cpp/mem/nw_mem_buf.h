#ifndef NW_MEM_BUFFER_H
#define NW_MEM_BUFFER_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../iop/nw_iop_cmp.h"
#	include "nw_mem_layt.h"
#	include "nw_mem_elem.h"
namespace NW
{
	/// memory_buffer class
	/// description:
	/// --manages a buffer of bytes;
	/// --allows to read and write bytes due to elements;
	class NW_API mem_buf : public a_mem_user, public a_iop_cmp
	{
	public:
		using buf_t = mem_buf;
		using buf_tc = const buf_t;
		using elem_t = mem_elem_t;
		using elem_tc = mem_elem_tc;
		using layt_t = mem_layt;
		using layt_tc = const layt_t;
		using size_t = v1u;
		using size_tc = cv1u;
	public:
		// --constructors_destructor
		mem_buf();
		mem_buf(layt_tc& layout, size_t count);
		mem_buf(layt_tc& layout, size_t count, ptr_tc data);
		mem_buf(buf_tc& copy);
		mem_buf(buf_t&& copy);
		virtual ~mem_buf();
		// --getters
		// // --layout
		inline layt_t& get_layt()        { return m_layt; }
		inline layt_tc& get_layt() const { return m_layt; }
		// // --size
		inline size_t get_stride() const { return m_layt.get_space(); }
		inline size_t get_space() const { return m_count * m_layt.get_space(); }
		inline size_t get_count() const { return m_count; }
		// // --data
		inline byte_t* get_data()        { return &m_data[0]; }
		inline byte_tc* get_data() const { return &m_data[0]; }
		inline byte_t* get_data(size_t key)        { NW_CHECK(has_space(key), "key error!", return NW_NULL); return get_data() + key; }
		inline byte_tc* get_data(size_t key) const { NW_CHECK(has_space(key), "key error!", return NW_NULL); return get_data() + key; }
		inline byte_t* get_data(cstr_t key)        { return get_data(m_layt[key].get_offset()); }
		inline byte_tc* get_data(cstr_t key) const { return get_data(m_layt[key].get_offset()); }
		// // --elems
		inline elem_t get_elem(size_t key)        { NW_CHECK(has_count(key), "key error!", return elem_t(NW_NULL, m_layt)); return elem_t(get_data(get_stride() * key), m_layt); }
		inline elem_tc get_elem(size_t key) const { NW_CHECK(has_count(key), "key error!", return elem_tc(NW_NULL, m_layt)); return elem_tc(get_data(get_stride() * key), m_layt); }
		inline elem_t get_elem(cstr_t key)        { return elem_t(get_data(m_layt[key].get_offset()), m_layt[key]); }
		inline elem_tc get_elem(cstr_t key) const { return elem_tc(get_data(m_layt[key].get_offset()), m_layt[key]); }
		// --setters
		// // --layout
		buf_t& set_layt(layt_tc& layout);
		inline buf_t& set_layt() { return set_layt(layt_t()); }
		// // --space
		buf_t& set_count(size_t count);
		buf_t& set_space(size_t space);
		// // --data
		virtual buf_t& set_data(size_t key, ptr_tc data, size_t count);
		inline buf_t& set_data(size_t key, ptr_tc data)   { return set_data(key, data, get_count() - key); }
		inline buf_t& set_data(ptr_tc data, size_t count) { return set_data(0u, data, count); }
		inline buf_t& set_data(ptr_tc data)               { return set_data(0u, data, get_count()); }
		inline buf_t& set_data()                          { return set_data(0u, get_data(), get_count()); }
		template<typename tname> buf_t& set_elem(size_t key, const tname& data) { get_elem(key) = data; return *this; }
		template<typename tname> buf_t& set_elem(cstr_t key, const tname& data) { get_elem(key) = data; return *this; }
		// --predicates
		inline v1bit has_stride(size_t stride = 1u) const { return get_stride() >= stride; }
		inline v1bit has_space(size_t space = 1u) const { return get_space() >= space; }
		inline v1bit has_count(size_t count = 1u) const { return get_count() >= count; }
		inline v1bit has_data() const              { return get_data() != NW_NULL; }
		inline v1bit has_data(byte_tc* data) const { return data >= get_data() && data <= get_data(get_space()); }
		inline v1bit has_elem(elem_tc& elem) const { return elem.get_data() >= get_data() && elem.get_data() <= get_data(get_space()); }
		inline v1bit has_elem(size_t key) const    { return get_space() >= key / get_stride(); }
		inline v1bit has_elem(cstr_t key) const    { return get_layt().has_node(key); }
		// --operators
		// // --assignment
		inline buf_t& operator=(buf_tc& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		inline buf_t& operator=(buf_t&& copy) { NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this); return *this; }
		// // --convertion
		inline operator elem_t ()        { return elem_t(get_data(), get_layt()); }
		inline operator elem_tc () const { return elem_tc(get_data(), get_layt()); }
		// // --accessors
		inline elem_t operator[](size_t key)        { return get_elem(key); }
		inline elem_tc operator[](size_t key) const { return get_elem(key); }
		inline elem_t operator[](cstr_t key)        { return get_elem(key); }
		inline elem_tc operator[](cstr_t key) const { return get_elem(key); }
		// // --input_output
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		virtual v1bit remake();
		inline v1bit remake(layt_tc& layt, size_t count) { set_layt(layt).set_count(count); return remake(); }
		inline v1bit remake(layt_tc& layt, size_t count, ptr_tc data) { NW_CHECK(remake(layt, count), "remake error!", return NW_FALSE); set_data(data); return NW_TRUE; }
	protected:
		layt_t m_layt;
		size_t m_count;
		byte_t* m_data;
	};
}
#endif	// NW_API
#endif	// NW_MEM_BUFFER_H