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
	class NW_API mem_buf : public a_mem_cmp, public a_iop_cmp
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
		inline cv1u get_space_used() const { return m_count_used; }
		inline cv1u get_space_free() const { return get_space() - get_space_used(); }
		inline cv1u get_count() const      { return m_count; }
		inline cv1u get_count_used() const { return get_space_used() / get_stride(); }
		inline cv1u get_count_free() const { return get_space_free() / get_stride(); }
		inline byte_t* get_data()        { return &m_data[0]; }
		inline byte_tc* get_data() const { return &m_data[0]; }
		inline byte_t* get_data(cv1u key)        { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return get_data() + key; }
		inline byte_tc* get_data(cv1u key) const { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return get_data() + key; }
		inline byte_t* get_data(cstr_t key)        { return get_data(get_layt()[key].get_offset()); }
		inline byte_tc* get_data(cstr_t key) const { return get_data(get_layt()[key].get_offset()); }
		inline byte_t* get_data_last()        { return get_data(get_space_used()); }
		inline byte_tc* get_data_last() const { return get_data(get_space_used()); }
		inline elem_t get_elem(cv1u key)        { NW_CHECK(has_count(key), "memory error!", return elem_t(NW_NULL, get_layt())); return elem_t(get_data(get_stride() * key), get_layt()); }
		inline elem_tc get_elem(cv1u key) const { NW_CHECK(has_count(key), "memory error!", return elem_tc(NW_NULL, get_layt())); return elem_tc(get_data(get_stride() * key), get_layt()); }
		inline elem_t get_elem(cstr_t key)        { return elem_t(get_data(get_layt()[key].get_offset()), get_layt()[key]); }
		inline elem_tc get_elem(cstr_t key) const { return elem_tc(get_data(get_layt()[key].get_offset()), get_layt()[key]); }
		inline elem_t get_elem_last()        { return get_elem(get_count_used()); }
		inline elem_tc get_elem_last() const { return get_elem(get_count_used()); }
		// --setters
		v1nil set_layt(layt_tc& layout);
		v1nil set_count(cv1u count);
		virtual v1nil set_data(cv1u key, ptr_tc data, cv1u count);
		inline v1nil set_data(ptr_tc data, cv1u count) { set_data(NW_NULL, data, count); }
		inline v1nil set_data(cv1u key, ptr_tc data)   { set_data(key, data, get_count()); }
		inline v1nil set_data(ptr_tc data)             { set_data(NW_NULL, data, get_count()); }
		inline v1nil set_data()                        { set_data(NW_NULL, NW_NULL, get_count()); }
		template<typename tname>
		v1nil set_elem(cv1u key, const tname& data) { get_elem(key) = data; }
		template<typename tname>
		v1nil set_elem(cstr_t key, const tname& data) { get_elem(key) = data; }
		// --predicates
		inline v1bit has_data() const              { return get_data() != NW_NULL; }
		inline v1bit has_data(byte_tc* data) const { return data >= get_data() && data <= get_data(get_space()); }
		inline v1bit has_elem(elem_tc& elem) const { return elem.get_data() >= get_data() && elem.get_data() <= get_data(get_space()); }
		inline v1bit has_count(cv1u count = 1u) const { return get_count() >= count; }
		inline v1bit has_count_used(cv1u count = 1u) const { return get_count_used() >= count; }
		inline v1bit has_count_free(cv1u count = 1u) const { return get_count_free() >= count; }
		inline v1bit has_space(cv1u space = 1u) const { return get_space() >= space; }
		inline v1bit has_space_used(cv1u space = 1u) const { return get_space_used() >= space; }
		inline v1bit has_space_free(cv1u space = 1u) const { return get_space_free() >= space; }
		// --operators
		v1nil operator=(buf_tc& copy);
		v1nil operator=(buf_t&& copy);
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
		inline v1bit remake(layt_tc& layt, cv1u count, ptr_tc data) { NW_CHECK(remake(layt, count), "failed remake!", return NW_FALSE); set_data(data); return NW_TRUE; }
		inline v1bit moveto(cv1s steps) {
			cv1u diff = static_cast<cv1u>(NW_MATH_ABS(steps));
			if (steps < 0) { // move backward
				NW_CHECK(has_count_used(diff), "memory error!", return NW_FALSE);
				m_count_used -= diff;
			}
			else if (steps > 0) { // move forward
				NW_CHECK(has_count_free(diff), "memory error!", return NW_FALSE);
				m_count_used += diff;
			}
			else { NW_ERROR("no difference!", NW_NULL); return NW_FALSE; }
			return NW_TRUE;
		}
	protected:
		layt_t m_layt;
		v1u m_count;
		v1u m_count_used;
		byte_t* m_data;
	};
}
#endif	// NW_API
#endif	// NW_MEM_BUF_H