#ifndef NW_MEM_BUF_H
#define NW_MEM_BUF_H
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
	public:
		mem_buf();
		mem_buf(layt_tc& layout, cv1u count, ptr_tc data = NW_NULL);
		mem_buf(buf_tc& copy);
		mem_buf(buf_t&& copy);
		virtual ~mem_buf();
		// --getters
		inline layt_t& get_layt()        { return m_layt; }
		inline layt_tc& get_layt() const { return m_layt; }
		inline cv1u get_stride() const { return m_layt.get_space(); }
		inline cv1u get_space() const      { return get_count() * get_stride(); }
		inline cv1u get_count() const      { return m_count; }
		inline byte_t* get_data()        { return &m_data[0]; }
		inline byte_tc* get_data() const { return &m_data[0]; }
		inline byte_t* get_data(cv1u key)        { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return get_data() + key; }
		inline byte_tc* get_data(cv1u key) const { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return get_data() + key; }
		inline byte_t* get_data(cstr_t key)        { return get_data(get_layt()[key].get_offset()); }
		inline byte_tc* get_data(cstr_t key) const { return get_data(get_layt()[key].get_offset()); }
		inline elem_t get_elem(cv1u key)        { NW_CHECK(has_count(key), "memory error!", return elem_t(NW_NULL, get_layt())); return elem_t(get_data(get_stride() * key), get_layt()); }
		inline elem_tc get_elem(cv1u key) const { NW_CHECK(has_count(key), "memory error!", return elem_tc(NW_NULL, get_layt())); return elem_tc(get_data(get_stride() * key), get_layt()); }
		inline elem_t get_elem(cstr_t key)        { return elem_t(get_data(get_layt()[key].get_offset()), get_layt()[key]); }
		inline elem_tc get_elem(cstr_t key) const { return elem_tc(get_data(get_layt()[key].get_offset()), get_layt()[key]); }
		// --setters
		buf_t& set_layt(layt_tc& layout);
		buf_t& set_count(cv1u count);
		virtual buf_t& set_data(cv1u key, ptr_tc data, cv1u count);
		inline buf_t& set_data(ptr_tc data, cv1u count) { return set_data(NW_NULL, data, count); }
		inline buf_t& set_data(cv1u key, ptr_tc data)   { return set_data(key, data, get_count()); }
		inline buf_t& set_data(ptr_tc data)             { return set_data(NW_NULL, data, get_count()); }
		inline buf_t& set_data()                        { return set_data(NW_NULL, get_data(), get_count()); }
		template<typename tname>
		buf_t& set_elem(cv1u key, const tname& data)   { get_elem(key) = data; return *this; }
		template<typename tname>
		buf_t& set_elem(cstr_t key, const tname& data) { get_elem(key) = data; return *this; }
		// --predicates
		inline v1bit has_data() const              { return get_data() != NW_NULL; }
		inline v1bit has_data(byte_tc* data) const { return data >= get_data() && data <= get_data(get_space()); }
		inline v1bit has_elem(elem_tc& elem) const { return elem.get_data() >= get_data() && elem.get_data() <= get_data(get_space()); }
		inline v1bit has_count(cv1u count = 1u) const { return get_count() >= count; }
		inline v1bit has_space(cv1u space = 1u) const { return get_space() >= space; }
		// --operators
		inline buf_t& operator=(buf_tc& copy) {
			NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this);
			return *this;
		}
		inline buf_t& operator=(buf_t&& copy) {
			NW_CHECK(remake(copy.get_layt(), copy.get_count(), copy.get_data()), "remake error!", return *this);
			return *this;
		}
		inline operator elem_t ()        { return get_elem(0u); }
		inline operator elem_tc () const { return get_elem(0u); }
		inline elem_t operator[](cv1u key)        { return get_elem(key); }
		inline elem_tc operator[](cv1u key) const { return get_elem(key); }
		inline elem_t operator[](cstr_t key)        { return get_elem(key); }
		inline elem_tc operator[](cstr_t key) const { return get_elem(key); }
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
		// --core_methods
		virtual v1bit remake();
		inline v1bit remake(layt_tc& layt) { set_layt(layt); return remake(); }
		inline v1bit remake(cv1u count) { set_count(count); return remake(); }
		inline v1bit remake(ptr_tc data) { set_data(NW_NULL, data, get_count()); return remake(); }
		inline v1bit remake(cv1u count, ptr_tc data) { set_count(count); return remake(data); }
		inline v1bit remake(layt_tc& layt, cv1u count) { set_layt(layt); return remake(count); }
		inline v1bit remake(layt_tc& layt, cv1u count, ptr_tc data) {
			NW_CHECK(remake(layt, count), "remake error!", return NW_FALSE); set_data(data); return NW_TRUE;
		}
	protected:
		layt_t m_layt;
		v1u m_count;
		byte_t* m_data;
	};
}
#endif	// NW_API
#endif	// NW_MEM_BUF_H