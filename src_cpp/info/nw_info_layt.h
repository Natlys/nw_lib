#ifndef NW_INFO_LAYOUT_H
#define NW_INFO_LAYOUT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_cont.h"
#include "nw_info_type.h"
namespace NW
{
	/// info_element class
	class NW_API info_elem
	{
	public:
		info_elem();
		info_elem(cstr name, cenum_id type);
		info_elem(cstr name, cenum_id type, v1u index);
		info_elem(cstr name, cenum_id type, v1u index, size offset_size);
		//info_elem(const info_elem& copy) = default;
		//info_elem(info_elem&& copy) = default;
		~info_elem() = default;
		// --getters
		inline cstr get_name() const     { return NW_GET_TYPE_NAME_D(m_enum); }
		inline size get_size() const     { return NW_GET_TYPE_SIZE_D(m_enum); }
		inline size get_count() const    { return NW_GET_TYPE_COUNT_D(m_enum); }
		inline cenum_id get_enum() const { return NW_GET_TYPE_ENUM_D(m_enum); }
		inline cenum_id get_gapi() const { return NW_GET_TYPE_GAPI_D(m_enum); }
		// --setters
		// --predicates
		inline cv1b check_enum(cenum_id type) const   { return get_enum() == type; }
		template<typename vt> cv1b check_enum() const { return get_enum() == NW_GET_TYPE_ENUM_S(vt); }
		// --operators
		// --core_methods
		cstr name;
		v1u idx;
		size offset;
	private:
		enum_id m_enum;
	};
}
namespace NW
{
	/// information_layout class
	class NW_API info_layt
	{
	public:
		using elem = info_elem;
		using celem = const elem;
		using elems = darray<elem>;
		using celems = const darray<elem>;
		using elem_iter = elems::iterator;
	public:
		info_layt();
		info_layt(elems&& elements);
		// --getters
		inline elems* get_elems()                { return &m_elems; }
		inline celem* get_elem(v1u idx) const    { return &m_elems[idx % m_elems.size()]; }
		inline celem* get_elem(cstr name) const  { for (auto& ielem : m_elems) { if (strcmp(name, ielem.name) == 0) { return &ielem; } } return nullptr; }
		inline elem_iter begin()                 { return m_elems.begin(); }
		inline elem_iter end()                   { return m_elems.end(); }
		// --setters
		void set_elems(celems& elements);
		void set_elems(elems&& elements);
		void add_elem(elem&& element);
		void add_elem(celem& element, v1u nof_elements = 1);
		template<typename type>
		void add_elem(cstr name, v1u count, v1u idx) { add_elem({ name, NW_GET_TYPE_ENUM_S(type), count, idx }); }
		template<typename type>
		void add_elem(cstr name, v1u count, v1u idx, size offset) { add_elem({ name, NW_GET_TYPE_ENUM_S(type), count, idx, offset }); }
		void rmv_elem(v1u idx);
		// --predicates
		inline v1b has_elem(v1u) {}
		// --operators
		inline celem* operator[](v1u idx) const  { return get_elem(idx); }
		inline celem* operator[](cstr key) const { return get_elem(key); }
		// --core_methods
	protected:
		elems m_elems;
	};
}
#endif	// NW_API
#endif	// NW_INFO_LAYOUT_H
