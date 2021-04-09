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
	class NW_API mem_elem;
	class NW_API mem_array;
	class NW_API mem_table;
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
		using tab = mem_table;
		using ctab = const tab;
		using arr = mem_array;
		using carr = const arr;
	public:
		mem_elem(ctype tid = NW_NULL, ptr buffer = NW_NULL, size offset = NW_NULL);
		mem_elem(celem& copy);
		mem_elem(elem&& copy);
		~mem_elem();
		// --getters
		// // type
		inline ctype get_type() const       { return m_type; }
		inline cinfo& get_type_info() const { return type_info::get(get_type()); }
		inline cv1u get_type_id()   const   { return get_type_info().id; }
		inline cstr get_type_name() const   { return &get_type_info().name[0]; }
		inline csize get_type_size() const  { return get_type_info().size; }
		// // data
		inline data get_data()        { return m_data + m_offset; }
		inline cdata get_data() const { return m_data + m_offset; }
		inline data get_data(ctype tid)        { NW_CHECK(check_type(tid), "", return NW_NULL); return get_data(); }
		inline cdata get_data(ctype tid) const { NW_CHECK(check_type(tid), "", return NW_NULL); return get_data(); }
		template<typename tname> tname& get()             { return *get_data<tname>(); }
		template<typename tname> const tname& get() const { return *get_data<tname>(); }
		template<typename tname> tname* get_data()             { return reinterpret_cast<tname*>(get_data(type_info::get_id<tname>())); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(get_data(type_info::get_id<tname>())); }
		virtual inline cv1u get_count() const { return m_size / get_type_size(); }
		virtual inline elem& get_elem(cv1u key)        { NW_ERROR("this is not indexable type!", return *this); }
		virtual inline celem& get_elem(cv1u key) const { NW_ERROR("this is not indexable type!", return *this); }
		virtual inline elem& get_elem(cstr key)        { NW_ERROR("this is not indexable type!", return *this); }
		virtual inline celem& get_elem(cstr key) const { NW_ERROR("this is not indexable type!", return *this); }
		// // info
		inline csize get_offset() const { return m_offset; }
		inline csize get_size() const   { return m_size; }
		// --setters
		void set_data(ctype tid, cptr buffer);
		template<typename tname>
		void set_data(const tname* buffer) { set_data(type_info::get_id<tname>(), buffer); }
		// void set_count(csize nof_elems);
		// --predicates
		inline v1b check_type(ctype tid) const          { return get_type_id() == tid; }
		template<typename tname> v1b check_type() const { return check_type(type_info::get_id<tname>()); }
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
	/// memory_array class
	class NW_API mem_array : public mem_elem
	{
	public:
		using elems = darray<mem_ref<elem>>;
		using celems = const elems;
		using elem_iter = elems::iterator;
	public:
		mem_array(ctype tid = NW_NULL, cv1u nof_elems = NW_NULL, ptr buffer = NW_NULL, csize offset = NW_NULL);
		mem_array(carr& copy);
		mem_array(arr&& copy);
		~mem_array();
		// --getters
		inline elems& get_elems()        { return m_elems; }
		inline celems& get_elems() const { return m_elems; }
		inline elem_iter begin()         { return m_elems.begin(); }
		inline elem_iter end()           { return m_elems.end(); }
		virtual inline cv1u get_count() const override { return m_elems.size(); }
		virtual inline elem& get_elem(cv1u key) override        { NW_CHECK(has_elem(key), "out of range!", return *this); return m_elems[key]; }
		virtual inline celem& get_elem(cv1u key) const override { NW_CHECK(has_elem(key), "out of range!", return *this); return m_elems[key]; }
		// --setters
		void set_type(ctype tid);
		template<typename tname> void set_type() { set_type(type_info::get_id<tname>()); }
		void set_count(cv1u nof_elems);
		void set_elems(ctype tid, cv1u nof_elems);
		template<typename tname> void set_elems(cv1u nof_elems) { set_elems(type_info::get_id<tname>(), nof_elems); }
		// --predicates
		inline v1b has_elem(cv1u key) const { return key < get_count(); }
		// --operators
		void operator=(carr& copy);
		void operator=(arr&& copy);
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		virtual v1b remake(ptr buffer, csize offset = NW_NULL) override;
	protected:
		elems m_elems;
	};
}
namespace NW
{
	/// memory_table class
	class NW_API mem_table : public mem_elem
	{
	public:
		using elems = darray<std::pair<dstr, mem_ref<elem>>>;
		using celems = const elems;
		using elem_iter = elems::iterator;
	public:
		mem_table(ptr buffer = NW_NULL, size offset = NW_NULL);
		mem_table(ctab& copy);
		mem_table(tab&& copy);
		~mem_table();
		// --getters
		inline elems& get_elems()        { return m_elems; }
		inline celems& get_elems() const { return m_elems; }
		inline elem_iter begin()         { return m_elems.begin(); }
		inline elem_iter end()           { return m_elems.end(); }
		virtual inline elem& get_elem(cv1u key)        override { NW_CHECK(has_elem(key), "out of range", return *this); return m_elems[key].second; }
		virtual inline celem& get_elem(cv1u key) const override { NW_CHECK(has_elem(key), "out of range", return *this); return m_elems[key].second; }
		virtual inline elem& get_elem(cstr key)        override { for (auto& ie : m_elems) { if (ie.first == key) return ie.second; } NW_ERROR("not found!", return *this); }
		virtual inline celem& get_elem(cstr key) const override { for (auto& ie : m_elems) { if (ie.first == key) return ie.second; } NW_ERROR("not found!", return *this); }
		template<typename tname>
		tname& get_elem(cstr key)             { static_cast<tname&>(get_elem(key)); }
		template<typename tname>
		const tname& get_elem(cstr key) const { static_cast<const tname&>(get_elem(key)); }
		virtual inline cv1u get_count() const override { return m_elems.size(); }
		// --setters
		elem& add_elem(cstr key, ctype tid);
		inline elem& add_elem(cstr key) { return add_elem(key, m_type); }
		template<typename tname>
		elem& add_elem(cstr key) { return add_elem(key, type_info::get_id<tname>()); }
		template<>
		elem& add_elem<arr>(cstr key) {
			NW_CHECK(!has_elem(key), "this name is already used", return *this);

			m_elems.push_back({ key, mem_ref<elem>() });
			m_elems.back().second.make_ref<arr>(m_type, 0u, m_data, m_size + m_offset);
			m_size += m_elems.back().second->get_size();
			return *m_elems.back().second.get_ref<arr>();
		}
		template<>
		elem& add_elem<tab>(cstr key) {
			NW_CHECK(!has_elem(key), "this name is already used", return *this);

			m_elems.push_back({ key, mem_ref<elem>() });
			m_elems.back().second.make_ref<tab>(m_data, m_size + m_offset);
			m_size += m_elems.back().second->get_size();
			return *m_elems.back().second.get_ref<tab>();
		}
		void rmv_elem(cstr key);
		arr& add_arr(cstr key, ctype tid, cv1u nof_elems = 0u);
		template<typename tname>
		arr& add_arr(cstr key, cv1u nof_elems = 0u) { return add_arr(key, type_info::get_id<tname>()); }
		tab& add_tab(cstr key);
		// --predicates
		inline v1b has_elem(cv1u key) const { return key < get_count(); }
		inline v1b has_elem(cstr key) const { for (auto& ie : m_elems) { if (ie.first == key) return NW_TRUE; } return NW_FALSE; }
		// --operators
		void operator=(ctab& copy);
		void operator=(tab&& copy);
		virtual stm_out& operator<<(stm_out& stm) const override;
		virtual stm_in& operator>>(stm_in& stm) override;
		// --core_methods
		virtual v1b remake(ptr buffer, size offset = NW_NULL) override;
	protected:
		elems m_elems;
	};
	template<> inline mem_table& mem_elem::get<mem_table>()             { return *static_cast<tab*>(this); }
	template<> inline const mem_table& mem_elem::get<mem_table>() const { return *static_cast<ctab*>(this); }
	template<> inline mem_array& mem_elem::get<mem_array>()             { return *static_cast<arr*>(this); }
	template<> inline const mem_array& mem_elem::get<mem_array>() const { return *static_cast<carr*>(this); }
}
#endif	// NW_API
#endif	// NW_MEM_ELEMENT_H