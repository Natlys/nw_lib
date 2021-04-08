#ifndef NW_MEM_ELEMENT_H
#define NW_MEM_ELEMENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_cont.h"
namespace NW
{
	class NW_API mem_elem;
	class NW_API mem_table;
	/// memory_element class
	class NW_API mem_elem
	{
	public:
		using data = byte*;
		using cdata = const data;
		using type = value_types;
		using ctype = const type;
		using info = info_type;
		using cinfo = const info;
		using elem = mem_elem;
		using celem = const elem;
		using tab = mem_table;
		using ctab = const tab;
	public:
		mem_elem(type tenum = NW_TYPE_DEFAULT, ptr buffer = NW_NULL, size offset = NW_NULL);
		mem_elem(celem& copy);
		mem_elem(elem&& copy);
		~mem_elem() = default;
		// --getters
		inline ctype get_type() const       { return m_type; }
		inline cinfo& get_type_info() const { return info_type::get(m_type); }
		inline cstr get_type_name() const   { return get_type_info().type_name; }
		inline ctype get_type_enum() const  { return get_type_info().type_enum; }
		inline csize get_type_size() const  { return get_type_info().elem_size; }
		inline csize get_type_count() const { return get_type_info().elem_count; }
		inline data get_data()          { return m_data + m_offset; }
		inline cdata get_data() const   { return m_data + m_offset; }
		inline data get_data(ctype tenum)        { NW_CHECK(check_type(tenum), "incompatible type", return NW_NULL); return get_data(); }
		inline cdata get_data(ctype tenum) const { NW_CHECK(check_type(tenum), "incompatible type", return NW_NULL); return get_data(); }
		inline elem* get_elem(cv1u key)        { NW_CHECK(key < get_count(), "", return this); return reinterpret_cast<elem*>(m_data + m_offset) + key; }
		inline celem* get_elem(cv1u key) const { NW_CHECK(key < get_count(), "", return this); return reinterpret_cast<elem*>(m_data + m_offset) + key; }
		inline csize get_offset() const { return m_offset; }
		inline csize get_size() const   { return m_size; }
		inline csize get_count() const  { return m_size / get_type_size(); }
		template<typename tname>
		inline tname& get()             { return *get_data<tname>(); }
		template<typename tname>
		inline const tname& get() const { return *get_data<tname>(); }
		template<typename tname>
		inline tname* get_data()        { return reinterpret_cast<tname*>(get_data(info_type::get<tname>().type_enum)); }
		template<typename tname>
		const tname* get_data() const   { return reinterpret_cast<const tname*>(get_data(info_type::get<tname>().type_enum)); }
		// --setters
		void set_data(type type, cptr buffer);
		template<typename tname>
		void set_data(const tname* buffer) { set_data(info_type::get<tname>().type_enum, buffer); }
		void set_count(size nof_elements);
		// --predicates
		inline v1b check_type(ctype tenum) const        { return get_type_info().type_enum == tenum; }
		template<typename tname> v1b check_type() const { return check_type(info_type::get<tname>().type_enum); }
		template<ctype tenum> v1b check_type() const    { return check_type(tenum); }
		// --operators
		void operator=(celem& copy);
		void operator=(elem&& copy);
		template<typename tname>
		void operator=(const tname& buffer) { set_data<tname>(&buffer); }
		template<typename tname>
		operator tname&()              { return get<tname>(); }
		template<typename tname>
		operator const tname& () const { return get<tname>(); }
		template<typename tname>
		operator tname*()              { return get_data<tname>(); }
		template<typename tname>
		operator const tname*() const  { return get_data<tname>(); }
		inline elem& operator[](cv1u key)        { return *get_elem(key); }
		inline celem& operator[](cv1u key) const { return *get_elem(key); }
		// --core_methods
		virtual v1b remake(ptr buffer, size offset = NW_NULL);
	protected:
		type m_type;
		data m_data;
		size m_offset;
		size m_size;
	};
}
namespace NW
{
	/// memory_table class
	class NW_API mem_table : public mem_elem
	{
	public:
		using elems = darray<std::pair<dstr, elem>>;
		using celems = const elems;
		using elem_iter = elems::iterator;
	public:
		mem_table(ptr buffer = NW_NULL, size offset = NW_NULL);
		mem_table(ctab& copy);
		mem_table(tab&& copy);
		~mem_table();
		// --getters
		inline elems& get_elems()        { return *reinterpret_cast<elems*>(m_data); }
		inline celems& get_elems() const { return *reinterpret_cast<celems*>(m_data); }
		inline elem_iter begin()         { return get_elems().begin(); }
		inline elem_iter end()           { return get_elems().end(); }
		inline csize get_count() const   { return get_elems().size(); }
		elem& get_elem(cstr key)         { for (auto& ie : get_elems()) { if (ie.first == key) return ie.second; } NW_ERROR("not found!", return *this); }
		celem& get_elem(cstr key) const  { for (auto& ie : get_elems()) { if (ie.first == key) return ie.second; } NW_ERROR("not found!", return *this); }
		template<typename tname>
		tname& get_elem(cstr key)             { static_cast<tname&>(get_elem(key)); }
		template<typename tname>
		const tname& get_elem(cstr key) const { static_cast<const tname&>(get_elem(key)); }
		// --setters
		elem& add_elem(cstr key, type tenum);
		template<typename tname>
		tname& add_elem(cstr key) {
			return add_elem(key, info_type::get<tname>().type_enum);
		}
		template<>
		tab& add_elem<tab>(cstr key) {
			NW_CHECK(!has_elem(key), "name is already used!", return *this);
			
			auto& m_elems = get_elems();
			m_elems.push_back({ key, tab() });
			m_size += sizeof(elem);
			return m_elems.back().second;
		}
		void rmv_elem(cstr key);
		// --predicates
		inline v1b has_elem(cstr key) const { for (auto& ie : get_elems()) { if (ie.first == key) return NW_TRUE; } return NW_FALSE; }
		// --operators
		void operator=(ctab& copy);
		void operator=(tab&& copy);
		inline elem& operator[](cstr key)        { return get_elem(key); }
		inline celem& operator[](cstr key) const { return get_elem(key); }
		// --core_methods
		virtual v1b remake(ptr buffer, size offset = NW_NULL);
	};
	template<> inline mem_table& mem_elem::get<mem_table>()             { return *static_cast<tab*>(this); }
	template<> inline const mem_table& mem_elem::get<mem_table>() const { return *static_cast<ctab*>(this); }
}
#endif	// NW_API
#endif	// NW_MEM_ELEMENT_H