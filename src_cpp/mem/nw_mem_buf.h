#ifndef NW_MEM_BUF_H
#define NW_MEM_BUF_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_mem_layt.h"
#	include "nw_mem_elem.h"
namespace NW
{
	/// memory_buffer class
	/// description:
	/// --manages a buffer of bytes;
	/// --allows to read and write bytes due to elements;
	class NW_API mem_buf : public a_mem_cmp
	{
	public:
		using buf_t = mem_buf;
		using buf_tc = const buf_t;
		using elem_t = mem_elem_t;
		using elem_tc = mem_elem_tc;
	public:
		mem_buf(cv1u stride = NW_NULL, cv1u count = NW_NULL, ptr_tc data = NW_NULL);
		mem_buf(buf_tc& copy);
		mem_buf(buf_t&& copy);
		virtual ~mem_buf();
		// --getters
		inline byte_t* get_bytes()        { return &m_bytes[0]; }
		inline byte_tc* get_bytes() const { return &m_bytes[0]; }
		inline byte_t* get_byte(cv1u key = NW_NULL)        { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return &m_bytes[key]; }
		inline byte_tc* get_byte(cv1u key = NW_NULL) const { NW_CHECK(has_space(key), "memory error!", return NW_NULL); return &m_bytes[key]; }
		inline elem_t get_elem(cv1u key = NW_NULL)        { NW_CHECK(has_count(key), "memory error!", return NW_NULL); return elem_t(&m_bytes[key * m_stride], m_stride); }
		inline elem_tc get_elem(cv1u key = NW_NULL) const { NW_CHECK(has_count(key), "memory error!", return NW_NULL); return elem_tc(&m_bytes[key * m_stride], m_stride); }
		inline cv1u get_stride() const { return m_stride; }
		inline cv1u get_count() const  { return m_count; }
		inline cv1u get_space() const  { return m_count * m_stride; }
		// --setters
		virtual v1nil set_data(cv1u count = 1u, ptr_tc data = NW_NULL, cv1u offset = NW_NULL);
		// --predicates
		inline v1bit has_byte(byte_tc* byte) const { return (byte >= &m_bytes[NW_NULL]) && (byte <= &m_bytes[get_space()]); }
		inline v1bit has_elem(elem_tc& elem) const { return (elem.get_data() >= &m_bytes[NW_NULL]) && (elem.get_data() <= &m_bytes[get_space()]); }
		inline v1bit has_count(cv1u count = 1u) const { return get_count() >= count; }
		inline v1bit has_space(cv1u space = 1u) const { return get_space() >= space; }
		// --operators
		v1nil operator=(buf_tc& copy);
		v1nil operator=(buf_t&& copy);
		inline elem_t& operator[](cv1u key)        { return get_elem(key); }
		inline elem_tc& operator[](cv1u key) const { return get_elem(key); }
		// --core_methods
		virtual v1bit remake(cv1u stride, cv1u count = 1u, ptr_tc data = NW_NULL);
	protected:
		byte_t* m_bytes;
		v1u m_stride;
		v1u m_count;
	};
}
namespace NW
{
	/// memory_array class
	class NW_API mem_arr : public mem_buf
	{
	public:
		using arr_t = mem_arr;
		using arr_tc = const arr_t;
		using layt_t = mem_layt;
		using layt_tc = const layt_t;
	public:
		mem_arr(layt_tc& layout = layt_t(), cv1u count = NW_NULL, ptr_tc data = NW_NULL);
		mem_arr(arr_tc& copy);
		mem_arr(arr_t&& copy);
		virtual ~mem_arr();
		// --getters
		inline layt_t& get_layt()         { return m_layt; }
		inline layt_tc& get_layt() const  { return m_layt; }
		inline size_tc get_offset() const { return get_layt().get_offset(); }
		inline cv1u get_space_used() const { return get_offset(); }
		inline cv1u get_space_free() const { return get_space() - get_space_used(); }
		inline cv1u get_count_used() const { return get_space_used() / get_stride(); }
		inline cv1u get_count_free() const { return get_space_free() / get_stride(); }
		// --setters
		v1nil set_layt(layt_tc& layout);
		template<typename tname>
		v1nil set_elem(cv1u key, tname&& buffer) { m_layt[key] = std::forward<tname>(buffer); }
		template<typename tfirst, typename ... trest>
		v1nil set_elem(cv1u key, tfirst&& first, trest&& ... rest) { set_elem(key, std::forward<tfirst>(first)); set_elem(key + 1u, std::forward<trest>(rest)...); }
		template<typename ... args>
		v1nil add_elem(args&& ... arguments) { set_elem(0u, std::forward<args>(arguments)...); m_layt.moveto(1); }
		v1nil rmv_elem() { NW_CHECK(has_count_used(1u), "memory error!", return); memset(get_byte(get_space_used()), NW_NULL, get_stride()); m_layt.moveto(-1); }
		// --predicates
		inline v1bit has_space_used(cv1u space = 1u) const { return get_space_used() >= space; }
		inline v1bit has_space_free(cv1u space = 1u) const { return get_space_free() >= space; }
		inline v1bit has_count_used(cv1u count = 1u) const { return get_count_used() >= count; }
		inline v1bit has_count_free(cv1u count = 1u) const { return get_count_free() >= count; }
		// --operators
		v1nil operator=(arr_tc& copy);
		v1nil operator=(arr_t&& copy);
		// --core_methods
		virtual v1bit remake(cv1u stride, cv1u count, ptr_tc data = NW_NULL) override;
	protected:
		layt_t m_layt;
	};
}
#endif	// NW_API
#endif	// NW_MEM_BUF_H