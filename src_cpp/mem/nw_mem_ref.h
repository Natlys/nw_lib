#ifndef NW_MEM_REFERENCE_H
#define NW_MEM_REFERENCE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "nw_mem_alloc.h"
#include "nw_mem_sys.h"
namespace NW
{
	/// mem_ref class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The mem_reference gets deleted if there is no any other mem_refs for it
	/// Interface:
	/// -> Create mem_ref -> MakeRef with particular allocator -> set_ref for other keepers -> use as a pointer
	template <typename mt>
	class mem_ref : public a_mem_user
	{
		using cmt = const mt;
	public:
		mem_ref();
		mem_ref(mt& value);
		mem_ref(const mem_ref<mt>& copy);
		template<typename amt>
		mem_ref(const mem_ref<amt>& copy);
		~mem_ref();
		// --getters
		inline mt* get_ref()            { return static_cast<mt*>(m_ref); }
		inline size* get_counter()      { return m_counter; }
		template<typename amt>
		inline amt* get_ref()           { return static_cast<amt*>(m_ref); }
		// --setters
		mem_ref<mt>& set_ref(const mt& ref);
		mem_ref<mt>& set_ref(const mem_ref<mt>& ref);
		template<typename amt>
		mem_ref<amt>& set_ref(const mem_ref<amt>& ref);
		mem_ref<mt>& reset();
		// --predicates
		inline v1b is_valid() const         { return m_ref != nullptr && m_counter != nullptr; }
		// --operators
		inline operator v1b()               { return m_ref != nullptr; }
		inline mt* operator->()             { return (m_ref); }
		inline mt& operator*()              { return *(m_ref); }
		inline operator mt* ()              { return static_cast<mt*>(m_ref); }
		inline operator mt& ()              { return static_cast<mt&>(*m_ref); }
		inline const mt* operator->() const            { return (m_ref); }
		inline const mt& operator*() const             { return *(m_ref); }
		inline mem_ref& operator=(const mem_ref& copy) { set_ref(copy); return *this; }
		// --convertion
		inline operator cmt* () const                       { return static_cast<cmt*>(m_ref); }
		inline operator cmt& () const                       { return static_cast<cmt&>(*m_ref); }
		template<typename amt> operator amt*()              { return static_cast<amt*>(m_ref); }
		template<typename amt> operator const amt*() const  { return static_cast<const amt*>(m_ref); }
		template<typename amt> operator mem_ref<amt>()const { return mem_ref<amt>(*this); }
		// --core_methods
		template <typename amt, typename ... args> mem_ref<mt>& make_ref(args&& ... arguments);
	private:
		mutable mt* m_ref;
		mutable size* m_counter;
	};
	// --constructors_destructors
	template <typename mt>
	mem_ref<mt>::mem_ref() :
		m_ref(nullptr), m_counter(nullptr) { reset(); }
	template <typename mt>
	mem_ref<mt>::mem_ref(mt& ref) :
		mem_ref() { set_ref(ref); }
	template <typename mt>
	mem_ref<mt>::mem_ref(const mem_ref<mt>& copy) :
		mem_ref<mt>() { set_ref(copy); }
	template <typename mt> template <typename amt>
	mem_ref<mt>::mem_ref(const mem_ref<amt>& copy) :
		mem_ref<mt>() { set_ref<amt>(copy); }
	template <typename mt>
	mem_ref<mt>::~mem_ref() { reset(); }
	// --setters
	template <typename mt>
	mem_ref<mt>& mem_ref<mt>::set_ref(const mt& ref) {
		reset();
		m_ref = &ref;
		m_counter = mem_sys::get().new_one<ui64>();
		*m_counter = 1;
		return *this;
	}
	template <typename mt>
	mem_ref<mt>& mem_ref<mt>::set_ref(const mem_ref<mt>& ref) {
		reset();
		mem_ref<mt>& ref_keeper = const_cast<mem_ref<mt>&>(ref);
		m_ref = ref_keeper.get_ref<mt>();
		m_counter = ref_keeper.get_counter();
		if (m_counter != nullptr) { *m_counter += 1; }
		return *this;
	}
	template <typename mt> template <typename amt>
	mem_ref<amt>& mem_ref<mt>::set_ref(const mem_ref<amt>& ref) {
		reset();
		mem_ref<amt>& ref_keeper = const_cast<mem_ref<amt>&>(ref);
		m_ref = ref_keeper.get_ref<mt>();
		m_counter = ref_keeper.get_counter();
		if (m_counter != nullptr) { *m_counter += 1; }
		return ref_keeper;
	}
	template <typename mt>
	mem_ref<mt>& mem_ref<mt>::reset() {
		if (m_counter != nullptr) {
			*m_counter -= 1;
			if (*m_counter == 0) {
				delete m_ref;
				m_ref = nullptr;
				mem_sys::get().dealloc(m_counter, sizeof(*m_counter));
				m_counter = nullptr;
			}
		}
		m_ref = nullptr;
		m_counter = nullptr;
		return *this;
	}
	// --core_methods
	template <typename mt> template <typename amt, typename ... args> 
	mem_ref<mt>& mem_ref<mt>::make_ref(args&& ... arguments) {
		reset();
		m_ref = new amt(std::forward<args>(arguments)...);
		m_counter = mem_sys::get().new_one<size>();
		*m_counter = 1;
		return *this;
	}
}
#endif	// NW_API
#endif	// NW_MEM_REFERENCE_H