#ifndef NW_MEM_ELEMENT_H
#define NW_MEM_ELEMENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "../std/nw_std_cont.h"
#include "../info/nw_info_type.h"
#include "../io/nw_io_cmp.h"
#include "nw_mem_cmp.h"
#include "nw_mem_ref.h"
namespace NW
{
	/// memory_element class
	/// description:
	/// --it's a wrapper for bytes to write data of some type;
	/// --it's like a variable int/float which describes how to
	/// treat bytes which it has;
	class NW_API mem_elem : public a_mem_cmp, public a_io_cmp
	{
	public:
		using data = byte*;
		using cdata = const data;
		using type = v1u;
		using ctype = const type;
		using info = type_info;
		using cinfo = const info;
		using elem = mem_elem;
		using celem = const elem;
		using elems = darray<elem>;
		using celems = const elems;
		using elem_iter = elems::iterator;
	public:
		mem_elem(cstr name = "root");
		mem_elem(cstr name, celems& elements);
		mem_elem(cstr name, ctype tid, ptr buffer, size offset = NW_NULL);
		mem_elem(celem& copy);
		mem_elem(elem&& copy);
		~mem_elem();
		// --getters
		// // type
		inline cstr get_name() const        { return m_name; }
		inline ctype get_type() const       { return m_type; }
		inline cinfo& get_type_info() const { return type_info::get(get_type()); }
		inline cv1u get_type_id()   const   { return get_type_info().id; }
		inline cstr get_type_name() const   { return &get_type_info().name[0]; }
		inline csize get_type_size() const  { return get_type_info().size; }
		inline data get_data()        { return m_data + m_offset; }
		inline cdata get_data() const { return m_data + m_offset; }
		inline data get_data(ctype tid)        { NW_CHECK(is_type(tid), "", return NW_NULL); return get_data(); }
		inline cdata get_data(ctype tid) const { NW_CHECK(is_type(tid), "", return NW_NULL); return get_data(); }
		template<typename tname> tname& get()             { return *get_data<tname>(); }
		template<typename tname> const tname& get() const { return *get_data<tname>(); }
		template<typename tname> tname* get_data()             { return reinterpret_cast<tname*>(get_data(type_info::get_id<tname>())); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(get_data(type_info::get_id<tname>())); }
		inline elems& get_elems()        { return m_elems; }
		inline celems& get_elems() const { return m_elems; }
		inline elem_iter begin()         { return m_elems.begin(); }
		inline elem_iter end()           { return m_elems.end(); }
		inline cv1u get_count() const    { return m_elems.size(); }
		inline elem& get_elem(cv1u key)        { NW_CHECK(has_elem(key), "out of range", return *this); return m_elems[key]; }
		inline celem& get_elem(cv1u key) const { NW_CHECK(has_elem(key), "out of range", return *this); return m_elems[key]; }
		inline elem& get_elem(cstr key)        { for (auto& ie : m_elems) { if (ie.is_name(key)) return ie; } NW_ERROR("not found!", return *this); }
		inline celem& get_elem(cstr key) const { for (auto& ie : m_elems) { if (ie.is_name(key)) return ie; } NW_ERROR("not found!", return *this); }
		template<typename tname>
		tname& get_elem(cstr key)             { static_cast<tname&>(get_elem(key)); }
		template<typename tname>
		const tname& get_elem(cstr key) const { static_cast<const tname&>(get_elem(key)); }
		// // info
		inline csize get_offset() const { return m_offset; }
		inline csize get_size() const   { return m_size; }
		// --setters
		// // data
		void set_data(ctype tid, cptr buffer);
		template<typename tname>
		void set_data(const tname* buffer) { set_data(type_info::get_id<tname>(), buffer); }
		// // elem
		elem& add_elem(cstr key, celems& elements);
		elem& add_elem(cstr key, ctype tid);
		template<typename tname>
		elem& add_elem(cstr key) { return add_elem(key, type_info::get_id<tname>()); }
		void rmv_elem(cv1u key);
		void rmv_elem(cstr key);
		// --predicates
		inline v1b is_name(cstr name) const { return NW_STR_EQUAL(m_name, name); }
		inline v1b is_type(ctype tid) const { return get_type_id() == tid; }
		template<typename tname>
		v1b is_type() const                 { return is_type(type_info::get_id<tname>()); }
		inline v1b is_elem() const          { return is_type<mem_elem>() == NW_FALSE; }
		inline v1b is_table() const         { return is_type<mem_elem>() == NW_TRUE; }
		inline v1b has_elem(cv1u key) const { return key < get_count(); }
		inline v1b has_elem(cstr key) const { for (auto& ie : m_elems) { if (ie.is_name(key)) return NW_TRUE; } return NW_FALSE; }
		// --operators
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
		void operator=(celem& copy);
		void operator=(elem&& copy);
		inline elem& operator[](cv1u key)        { return get_elem(key); }
		inline celem& operator[](cv1u key) const { return get_elem(key); }
		inline elem& operator[](cstr key)        { return get_elem(key); }
		inline celem& operator[](cstr key) const { return get_elem(key); }
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		v1b remake(ptr buffer, size offset = NW_NULL);
	protected:
		schar m_name[NW_MAX_NAME];
		type m_type;
		data m_data;
		size m_offset;
		size m_size;
		elems m_elems;
	};
}
#endif	// NW_API
#endif	// NW_MEM_ELEMENT_H