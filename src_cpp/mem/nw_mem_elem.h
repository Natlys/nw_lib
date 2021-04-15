#ifndef NW_MEM_ELEMENT_H
#define NW_MEM_ELEMENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../info/nw_info_type.h"
#	include "nw_mem_cmp.h"
namespace NW
{
	/// memory_element class
	class NW_API mem_elem_t : public a_mem_cmp
	{
	public:
		using elem_t = mem_elem_t;
		using elem_tc = const elem_t;
	public:
		mem_elem_t(byte_t* buffer = NW_NULL, size_tc size = NW_NULL) : m_data(buffer), m_size(size) { }
		// --getters
		inline byte_t* get_data()        { return m_data; }
		inline byte_tc* get_data() const { return m_data; }
		template<typename tname> tname* get_data()             { return reinterpret_cast<tname*>(m_data); }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(m_data); }
		template<typename tname> tname& get()             { return *reinterpret_cast<tname*>(m_data); }
		template<typename tname> const tname& get() const { return *reinterpret_cast<const tname*>(m_data); }
		// --setters
		inline v1nil set_data(ptr_tc buffer) { memcpy(m_data, buffer, m_size); }
		template<typename tname> v1nil set_data(const tname* buffer) { memcpy(m_data, buffer, m_size); }
		template<typename tname> v1nil set(const tname& buffer)      { memcpy(m_data, &buffer, m_size); ; }
		// --operators
		template<typename tname> operator tname& ()             { return get<tname>(); }
		template<typename tname> operator const tname& () const { return get<tname>(); }
		template<typename tname> operator tname* ()             { return get_data<tname>(); }
		template<typename tname> operator const tname* () const { return get_data<tname>(); }
		template<typename tname> v1nil operator=(const tname* buffer) { set_data<tname>(buffer); }
		template<typename tname> v1nil operator=(const tname& buffer) { set<tname>(buffer); }
		template<typename tname> tname& operator[](cv1u key)             { return *(get_data<tname>() + key * m_size); }
		template<typename tname> const tname& operator[](cv1u key) const { return *(get_data<tname>() + key * m_size); }
	private:
		byte_t* m_data;
		size_t m_size;
	};
	/// memory_element constant class
	class NW_API mem_elem_tc
	{
	public:
		using elem_t = mem_elem_t;
		using elem_tc = const elem_t;
	public:
		mem_elem_tc(byte_tc* buffer = NW_NULL, size_tc size = NW_NULL) : m_data(buffer), m_size(size) { }
		// --getters
		inline byte_tc* get_data() const { return m_data; }
		template<typename tname> const tname* get_data() const { return reinterpret_cast<const tname*>(m_data); }
		template<typename tname> const tname& get() const { return *reinterpret_cast<const tname*>(m_data); }
		// --operators
		template<typename tname> operator const tname& () const { return get<tname>(); }
		template<typename tname> operator const tname* () const { return get_data<tname>(); }
		template<typename tname> const tname& operator[](cv1u key) const { return *(get_data<tname>() + key * m_size); }
	private:
		byte_tc* m_data;
		size_tc m_size;
	};
}
#endif	// NW_API
#endif	// NW_MEM_ELEMENT_H