#ifndef NW_MEM_REFERENCE_H
#define NW_MEM_REFERENCE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "nw_mem_alloc.h"
#include "nw_mem_sys.h"
#include "nw_mem_cmp.h"
namespace NW
{
	/// mem_ref class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The mem_reference gets deleted if there is no any other mem_refs for it
	/// Interface:
	/// -> Create mem_ref -> MakeRef with particular allocator -> set_ref for other keepers -> use as a pointer
	template <typename vtype>
	class mem_ref : public a_mem_cmp
	{
		using val_t = vtype;
		using val_tc = const val_t;
	public:
		inline mem_ref() : m_ref(NW_NULL), m_counter(NW_NULL) { }
		inline mem_ref(val_t& value) : mem_ref() { set_ref(value); }
		inline mem_ref(const mem_ref<val_t>& copy) : mem_ref() { set_ref(copy); }
		template<typename tname>
		inline mem_ref(const mem_ref<tname>& copy) : mem_ref() { set_ref<tname>(copy); }
		inline ~mem_ref() { reset(); }
		// --getters
		inline val_t* get_ref()        { return static_cast<val_t*>(m_ref); }
		inline val_tc* get_ref() const { return static_cast<val_tc*>(m_ref); }
		template<typename tname> tname* get_ref()             { return static_cast<tname*>(m_ref); }
		template<typename tname> const tname* get_ref() const { return static_cast<const tname*>(m_ref); }
		template<typename tname> tname& get_val()             { return *static_cast<tname*>(m_ref); }
		template<typename tname> const tname& get_val() const { return *static_cast<const tname*>(m_ref); }
		inline size_tc get_count() const    { return *m_counter; }
		inline size_t* get_counter()        { return m_counter; }
		inline size_tc* get_counter() const { return m_counter; }
		// --setters
		mem_ref<val_t>& set_ref(val_tc& ref) {
			reset();
			m_ref = &ref;
			m_counter = mem_sys::get().new_one<size_t>();
			*m_counter = 1;
			return *this;
		}
		mem_ref<val_t>& set_ref(const mem_ref<val_t>& ref) {
			reset();
			mem_ref<val_t>& temp = const_cast<mem_ref<val_t>&>(ref);
			m_ref = temp.get_ref<val_t>();
			m_counter = temp.get_counter();
			if (m_counter != NW_NULL) { *m_counter += 1; }
			return *this;
		}
		template<typename tname>
		mem_ref<tname>& set_ref(const mem_ref<tname>& ref) {
			reset();
			mem_ref<tname>& temp = const_cast<mem_ref<tname>&>(ref);
			m_ref = temp.get_ref<val_t>();
			m_counter = temp.get_counter();
			if (m_counter != NW_NULL) { *m_counter += 1; }
			return temp;
		}
		mem_ref<val_t>& reset() {
			if (m_counter != NW_NULL) {
				*m_counter -= 1;
				if (get_count() == 0) {
					delete m_ref;
					m_ref = NW_NULL;
					mem_sys::get().del_one<size_t>(m_counter);
					m_counter = NW_NULL;
				}
			}
			m_ref = NW_NULL;
			m_counter = NW_NULL;
			return *this;
		}
		// --predicates
		inline v1bit is_valid() const { return m_ref != NW_NULL && m_counter != NW_NULL; }
		// --operators
		inline mem_ref& operator=(const mem_ref& copy) { return set_ref(copy); }
		// --convertion
		inline operator v1bit() const     { return m_ref != NW_NULL; }
		inline val_t* operator->()        { return (m_ref); }
		inline val_tc* operator->() const { return (m_ref); }
		inline val_t& operator*()         { return *(m_ref); }
		inline val_tc& operator*() const  { return *(m_ref); }
		inline operator val_t*()        { return static_cast<val_t*>(m_ref); }
		inline operator val_tc*() const { return static_cast<val_tc*>(m_ref); }
		inline operator val_t&()        { return static_cast<val_t&>(*m_ref); }
		inline operator val_tc&() const { return static_cast<val_tc&>(*m_ref); }
		template<typename tname> operator tname*()               { return static_cast<tname*>(m_ref); }
		template<typename tname> operator const tname*() const   { return static_cast<const tname*>(m_ref); }
		template<typename tname> operator mem_ref<tname>() const { return mem_ref<tname>(*this); }
		// --core_methods
		template <typename tname, typename ... args> mem_ref<val_t>& make_ref(args&& ... arguments) {
			reset();
			m_ref = new tname(std::forward<args>(arguments)...);
			m_counter = mem_sys::get().new_one<size_t>();
			*m_counter = 1u;
			return *this;
		}
	private:
		mutable val_t* m_ref;
		mutable size_t* m_counter;
	};
}
#endif	// NW_API
#endif	// NW_MEM_REFERENCE_H