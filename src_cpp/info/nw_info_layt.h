#ifndef NW_INFO_LAYOUT_H
#define NW_INFO_LAYOUT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "std/nw_std_cont.h"
#include "nw_info_type.h"
namespace NW
{
	/// value_element class
	class NW_API info_elem
	{
		using vtype = value_types;
	public:
		info_elem();
		info_elem(cstr name, vtype type, v1u count);
		info_elem(cstr name, vtype type, v1u count, v1u index);
		info_elem(cstr name, vtype type, v1u count, v1u index, size offset_size);
		// --getters
		inline size get_size() const  { return NW_GET_VTYPE_SIZE_D(m_type) * m_count; }
		inline vtype get_type() const { return m_type; }
		inline cv1u get_count() const { return m_count; }
		// --setters
		// --predicates
		inline cv1b check_type(vtype type) const      { return m_type == type; }
		template<typename vt> cv1b check_type() const { return m_type == NW_GET_VTYPE_ENUM_S(vt); }
		// --core_methods
	public:
		cstr name;
		v1u idx;
		size offset;
	private:
		vtype m_type;
		v1u m_count;
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
		void add_elem(cstr name, v1u count, v1u idx) { add_elem({ name, NW_GET_VTYPE_ENUM_S(type), count, idx }); }
		template<typename type>
		void add_elem(cstr name, v1u count, v1u idx, size offset) { add_elem({ name, NW_GET_VTYPE_ENUM_S(type), count, idx, offset }); }
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
