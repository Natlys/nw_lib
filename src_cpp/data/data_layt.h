#include <nwl_core.hpp>
#include <core/nwl_type.h>
#include <core/nwl_str.h>
#include <core/nwl_cont.h>
namespace NW
{
	/// data element struct
	struct NW_API data_elem
	{
#		define NW_CONV_NTP_SIZE convert<native_types, size>
	public:
		data_elem();
		data_elem(cstr name, native_types type, v1ui count);
		data_elem(cstr name, native_types type, v1ui count, v1ui index);
		data_elem(cstr name, native_types type, v1ui count, v1ui index, size offset_size);
		// --getters
		inline size get_size() const                   { return NW_CONV_NTP_SIZE(type) * count; }
		inline size get_aligned_size() const           { return NW_ALIGN_FORWARD(NW_CONV_NTP_SIZE(type) * count, NW_CONV_NTP_SIZE(type)); }
		inline native_types get_type() const           { return type; }
		inline v1ui get_count() const                  { return count; }
		// --setters
		// --predicates
		inline bit check_type(native_types type) const { return type == type; }
		// --core_methods
	public:
		cstr name;
		v1ui idx;
		size offset;
	private:
		native_types type;
		v1ui count;
#		undef NW_CONV_NTP_SIZE
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
		using celems = const darray<data_elem>;
		using elem_iter = elems::iterator;
	public:
		data_layt();
		data_layt(elems&& elements);
		// --getters
		inline elems* get_elems()               { return &m_elems; }
		inline celem* get_elem(v1ui8 idx) const { return &m_elems[idx % m_elems.size()]; }
		inline celem* get_elem(cstr name) const { for (auto& ielem : m_elems) { if (str_is_equal(name, ielem.name)) { return &ielem; } } return nullptr; }
		inline size get_stride() const          { return m_stride; }
		inline elem_iter begin()                { return m_elems.begin(); }
		inline elem_iter end()                  { return m_elems.end(); }
		// --setters
		void set_elems(celems& elements);
		void set_elems(elems&& elements);
		void add_elem(elem&& element);
		void add_elem(celem& element, v1ui8 nof_elements = 1);
		template<typename type>
		void add_elem(cstr name, v1ui count, v1ui idx)              { add_elem({ name, t_ntp_info<type>::enum_type, count, idx }); }
		template<typename type>
		void add_elem(cstr name, v1ui count, v1ui idx, size offset) { add_elem({ name, t_ntp_info<type>::enum_type, count, idx, offset }); }
		void rmv_elem(v1ui8 idx);
		// --predicates
		// --operators
		inline celem* operator[](v1ui8 idx) const { return get_elem(idx); }
		inline celem* operator[](cstr key)const   { return get_elem(key); }
		// --core_methods
	protected:
		elems m_elems;
		size m_stride;
	};
}