#ifndef NW_MEM_ELEMENT_H
#define NW_MEM_ELEMENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../std/nw_std_type.h"
#	include "nw_mem_layt.h"
namespace NW
{
	/// memory_element class
	class NW_API mem_elem_t : public a_mem_user
	{
	public:
		using layt_t = mem_layt;
		using layt_tc = const layt_t;
		using elem_t = mem_elem_t;
		using elem_tc = const elem_t;
		using type_t = layt_t::type_t;
		using type_tc = layt_t::type_tc;
	public:
		mem_elem_t(byte_t* data, layt_t& layt) : m_data(data), m_layt(layt) { }
		// --getters
		inline byte_t* get_data()         { return m_data; }
		inline byte_tc* get_data() const  { return m_data; }
		inline layt_t& get_layt()         { return m_layt; }
		inline layt_tc& get_layt() const  { return m_layt; }
		inline size_tc get_space() const  { return get_layt().get_space(); }
		inline size_tc get_count() const  { return get_layt().get_count(); }
		inline size_tc get_offset() const { return get_layt().get_offset(); }
		inline elem_t get_elem(cv1u key)        { return elem_t(m_data + m_layt[key].get_offset(), m_layt[key]); }
		inline elem_tc get_elem(cv1u key) const { return elem_t(m_data + m_layt[key].get_offset(), m_layt[key]); }
		inline elem_t get_elem(cstr_t key)        { return elem_t(m_data + m_layt[key].get_offset(), m_layt[key]); }
		inline elem_tc get_elem(cstr_t key) const { return elem_t(m_data + m_layt[key].get_offset(), m_layt[key]); }
		inline byte_t* get_data(type_tc type)        { NW_CHECK(get_layt().has_type(type), "type error!", return NW_NULL); return get_data(); }
		inline byte_tc* get_data(type_tc type) const { NW_CHECK(get_layt().has_type(type), "type error!", return NW_NULL); return get_data(); }
		template<typename tname> tname* get_data()             { return reinterpret_cast<tname*>(get_data(type_info::get_type<tname>())); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(get_data(type_info::get_type<tname>())); }
		template<typename tname> tname& get()             { return *reinterpret_cast<tname*>(get_data(type_info::get_type<tname>())); }
		template<typename tname> const tname& get() const { return *reinterpret_cast<const tname*>(get_data(type_info::get_type<tname>())); }
		// --setters
		inline v1nil set_data(ptr_tc buffer)               { memcpy(get_data(), buffer, get_space()); }
		inline v1nil set_data(ptr_tc buffer, type_tc type) { memcpy(get_data(type), buffer, get_space()); }
		template<typename tname> v1nil set_data(const tname* buffer) { set_data(buffer, type_info::get_type<tname>()); }
		template<typename tname> v1nil set(const tname& buffer)      { set_data(&buffer, type_info::get_type<tname>()); }
		template<typename tname>
		v1nil set_elem(cv1u key, tname&& buffer) { get_elem(key).set<tname>(std::forward<tname>(buffer)); }
		template<typename tfirst, typename ... trest>
		v1nil set_elem(cv1u key, tfirst&& first, trest&& ... rest) {
			set_elem(key, std::forward<tfirst>(first));
			set_elem(key + 1u, std::forward<trest>(rest)...);
		}
		// --operators
		template<typename tname> operator tname* ()             { return get_data<tname>(); }
		template<typename tname> operator const tname* () const { return get_data<tname>(); }
		template<typename tname> operator tname& ()             { return get<tname>(); }
		template<typename tname> operator const tname& () const { return get<tname>(); }
		template<typename tname> inline v1nil operator=(const tname* buffer) { set_data<tname>(buffer); }
		template<typename tname> inline v1nil operator=(const tname& buffer) { set<tname>(buffer); }
		inline elem_t operator[](cv1u key)        { return get_elem(key); }
		inline elem_tc operator[](cv1u key) const { return get_elem(key); }
		inline elem_t operator[](cstr_t key)        { return get_elem(key); }
		inline elem_tc operator[](cstr_t key) const { return get_elem(key); }
	private:
		byte_t* m_data;
		layt_t& m_layt;
	};
	/// memory_element constant class
	class NW_API mem_elem_tc
	{
	public:
		using layt_t = mem_layt;
		using layt_tc = const layt_t;
		using elem_t = mem_elem_tc;
		using elem_tc = const elem_t;
		using vtype_t = layt_t::type_t;
		using vtype_tc = layt_t::type_tc;
	public:
		mem_elem_tc(byte_tc* data, layt_tc& layt) : m_data(data), m_layt(layt) { }
		// --getters
		inline byte_tc* get_data() const { return m_data; }
		inline layt_tc& get_layt() const { return m_layt; }
		inline size_tc get_space() const { return get_layt().get_space(); }
		inline size_tc get_count() const { return get_layt().get_count(); }
		inline size_tc get_offset() const { return get_layt().get_offset(); }
		inline elem_tc get_elem(cv1u key) const { return elem_t(m_data + get_layt()[key].get_offset(), m_layt); }
		inline elem_tc get_elem(cstr_t key) const { return elem_t(m_data + get_layt()[key].get_offset(), m_layt); }
		inline byte_tc* get_data(vtype_tc type) const { NW_CHECK(get_layt().has_type(type), "type error!", return NW_NULL); return get_data(); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(get_data(type_info::get_type<tname>())); }
		template<typename tname> const tname& get() const { return *reinterpret_cast<const tname*>(get_data(type_info::get_type<tname>())); }
		// --operators
		template<typename tname> operator const tname* () const { return get_data<tname>(); }
		template<typename tname> operator const tname& () const { return get<tname>(); }
		inline elem_tc operator[](cv1u key) const { return get_elem(key); }
		inline elem_tc operator[](cstr_t key) const { return get_elem(key); }
	private:
		byte_tc* m_data;
		layt_tc& m_layt;
	};
}
#endif	// NW_API
#endif	// NW_MEM_ELEMENT_H