#ifndef NW_MEM_REFERENCE_H
#define NW_MEM_REFERENCE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_mem_alloc.h"
#	include "nw_mem_sys.h"
#	include "nw_mem_cmp.h"
namespace NW
{
	/// mem_ref class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The mem_reference gets deleted if there is no any other mem_refs for it
	/// Interface:
	/// -> Create mem_ref -> MakeRef with particular allocator -> set_ref for other keepers -> use as a pointer
	template <typename tval, class tgiver = mem_sys>
	class mem_ref : public t_mem_user<tgiver>
	{
	public:
		using ref_t = mem_ref<tval, tgiver>;
		using ref_tc = const ref_t;
		using val_t = tval;
		using val_tc = const val_t;
		using count_t = size_t;
		using count_tc = count_t;
	public:
		inline mem_ref() : m_ref(NW_NULL), m_counter(NW_NULL) { }
		inline mem_ref(val_t& value) : mem_ref() { set_ref(value); }
		mem_ref(ref_tc& copy) : mem_ref() { set_ref(copy); }
		mem_ref(ref_t&& copy) : mem_ref() { set_ref(copy); }
		template<typename tval_ = tval, class tgiver_ = tgiver>
		mem_ref(const mem_ref<tval_, tgiver_>& copy) : mem_ref() { set_ref(copy); }
		template<typename tval_ = tval, class tgiver_ = tgiver>
		mem_ref(mem_ref<tval_, tgiver_>&& copy) : mem_ref() { set_ref(copy); }
		inline ~mem_ref() { reset(); }
		// --getters
		template<typename tname = val_t> tname* get_ref()             { return static_cast<tname*>(m_ref); }
		template<typename tname = val_t> const tname* get_ref() const { return static_cast<const tname*>(m_ref); }
		template<typename tname = val_t> tname& get_val()             { return *static_cast<tname*>(m_ref); }
		template<typename tname = val_t> const tname& get_val() const { return *static_cast<const tname*>(m_ref); }
		inline count_tc get_count() const    { return *m_counter; }
		inline count_t* get_counter()        { return m_counter; }
		inline count_tc* get_counter() const { return m_counter; }
		// --setters
		ref_t& set_ref(val_tc& ref) {
			reset();
			m_ref = &ref;
			m_counter = giver_t::take(sizeof(count_t), alignof(count_t));
			new(m_counter)count_t(NW_NULL);
			*m_counter = 1;
			return *this;
		}
		template<typename tval_ = tval, class tgiver_ = tgiver>
		ref_t& set_ref(const mem_ref<tval_, tgiver_>& ref) {
			reset();
			mem_ref<tval_, tgiver_>& temp = const_cast<mem_ref<tval_, tgiver_>&>(ref);
			m_ref = temp.get_ref<val_t>();
			m_counter = temp.get_counter();
			if (m_counter != NW_NULL) { *m_counter += 1; }
			return *this;
		}
		ref_t& reset() {
			if (m_counter != NW_NULL) {
				*m_counter -= 1;
				if (get_count() == 0) {
					delete m_ref;
					m_ref = NW_NULL;
					giver_t::static_free(m_counter, sizeof(count_t), alignof(count_t));
					m_counter = NW_NULL;
				}
			}
			m_ref = NW_NULL;
			m_counter = NW_NULL;
			return *this;
		}
		// --predicates
		inline v1bit has_ref() const { return m_ref != NW_NULL; }
		inline v1bit has_counter() const { return get_counter() != NW_NULL; }
		inline v1bit has_count() const               { return get_count() != NW_NULL; }
		inline v1bit has_count(count_tc count) const { return get_count() >= count; }
		inline v1bit is_valid() const { return has_ref() && has_counter(); }
		// --operators
		inline ref_t& operator=(ref_tc& copy) { return set_ref(copy); }
		inline ref_t& operator=(ref_t&& copy) { return set_ref(copy); }
		template<typename tval_ = tval, class tgiver_ = tgiver>
		inline ref_t& operator=(const mem_ref<tval_, tgiver_>& copy) { return set_ref(copy); }
		template<typename tval_ = tval, class tgiver_ = tgiver>
		inline ref_t& operator=(mem_ref<tval_, tgiver_>&& copy)      { return set_ref(copy); }
		// // --referencing
		inline val_t* operator&()         { return m_ref; }
		inline val_tc* operator&() const  { return m_ref; }
		inline val_t& operator*()         { return *(m_ref); }
		inline val_tc& operator*() const  { return *(m_ref); }
		inline val_t* operator->()        { return (m_ref); }
		inline val_tc* operator->() const { return (m_ref); }
		// // --convertion
		inline operator v1bit() const     { return m_ref != NW_NULL; }
		inline operator val_t*()        { return static_cast<val_t*>(m_ref); }
		inline operator val_tc*() const { return static_cast<val_tc*>(m_ref); }
		inline operator val_t&()        { return static_cast<val_t&>(*m_ref); }
		inline operator val_tc&() const { return static_cast<val_tc&>(*m_ref); }
		template<typename tname> operator tname*()               { return static_cast<tname*>(m_ref); }
		template<typename tname> operator const tname*() const   { return static_cast<const tname*>(m_ref); }
		template<typename tval_, class tgiver_> operator mem_ref<tval_, tgiver_>()       { return mem_ref<tval_, tgiver_>(*this); }
		template<typename tval_, class tgiver_> operator mem_ref<tval_, tgiver_>() const { return mem_ref<tval_, tgiver_>(*this); }
		// // --logic
		inline v1bit operator==(ref_tc& ref) const { return m_ref == ref.get_ref(); }
		inline v1bit operator!=(ref_tc& ref) const { return m_ref != ref.get_ref(); }
		// --core_methods
		template <typename tname, typename ... args> mem_ref<val_t>& make_ref(args&& ... arguments) {
			reset();
			m_ref = new tname(std::forward<args>(arguments)...);
			m_counter = reinterpret_cast<count_t*>(giver_t::static_take(sizeof(count_t), alignof(count_t)));
			new(m_counter)count_t(NW_NULL);
			*m_counter = 1u;
			return *this;
		}
	private:
		mutable val_t* m_ref;
		mutable count_t* m_counter;
	};
}
#endif	// NW_API
#endif	// NW_MEM_REFERENCE_H