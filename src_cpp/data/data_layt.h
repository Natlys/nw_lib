#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <core/nwl_cln.h>
#include "data_switch.h"
namespace NW
{
	/// data element struct
	struct NW_API data_elem
	{
	public:
		data_elem();
		data_elem(cstr name, data_types type, ui32 count = 1, ui32 index = 0, size offset_size = 0);
		// --getters
		inline size get_size() const				{ return dt_get_size(type); }
		inline size get_aligned_size() const		{ return dt_get_aligned_size(type, count); }
		inline data_types get_type() const			{ return type; }
		inline ui32 get_count() const				{ return count; }
		inline ui32 get_prim_count() const			{ return count * dt_get_prim_count(type); }
		// --setters
		// --predicates
		inline bit check_type(data_types type)const	{ return type == type; }
		// --core_methods
	public:
		cstr name;
		ui32 idx;
		size offset;
	private:
		data_types type;
		ui32 count;
	};
}
namespace NW
{
	class NW_API data_layt
	{
	public:
		using elem = data_elem;
		using celem = const data_elem;
		using elems = darray<data_elem>;
		using elem_iter = elems::iterator;
	public:
		data_layt();
		// --getters
		inline elems* get_elems()				{ return &m_elems; }
		inline celem* get_elem(ui8 idx) const	{ return &m_elems[idx % m_elems.size()]; }
		inline celem* get_elem(cstr name) const { for (auto& ielem : m_elems) { if (str_is_equal(name, ielem.name)) { return &ielem; } } return nullptr; }
		inline elem_iter begin()				{ return m_elems.begin(); }
		inline elem_iter end()					{ return m_elems.end(); }
		// --setters
		void add_elem(celem& element, ui8 nof_elements = 1);
		void rmv_elem(ui8 idx);
		// --predicates
		// --operators
		inline celem* operator[](ui8 idx) const	{ return get_elem(idx); }
		inline celem* operator[](cstr key)const	{ return get_elem(key); }
		// --core_methods
	protected:
		elems m_elems;
		size m_stride;
	};
}