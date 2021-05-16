#ifndef NC_LIB_REFERENCE_HPP
#	define NC_LIB_REFERENCE_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_REF)
#		if (NC_REF & NC_REF_STD)
#			include <new>
#			include <memory>
			#define nc_ref_tt shared_ptr
#		endif	// NC_REF_STD //
#		if (NC_REF & NC_REF_OWN)
#   		include <new>
/// heap_allocator_type
class nc_heap_alloc_t
{
public:
	// getters //
	// commands //
	static inline v1bit_t static_take(nil_t** data, size_t size, size_t alig) {
		NC_PCALL({ // checking //
			NC_CHECK(data != NC_NULL, "no data!", return NC_FALSE);
			NC_CHECK(size != NC_ZERO, "no size!", return NC_FALSE);
			NC_CHECK(alig != NC_ZERO, "cannot align to zero!", return NC_FALSE);
		}, "memory error!", return NC_FALSE);
		NC_PCALL({ // action //
			size = NC_ALIGN(size, alig);
			NC_MEM_TAKE(*data, size);
		}, "memory error!", return NC_FALSE);
		// results //
		return NC_TRUTH;
	}
	static inline v1bit_t static_free(nil_t** data, size_t size, size_t alig) {
		NC_PCALL({ // checking //
			NC_CHECK(data != NC_NULL, "no data!", return NC_FALSE);
			NC_CHECK(size != NC_ZERO, "no size!", return NC_FALSE);
			NC_CHECK(alig != NC_ZERO, "cannot align to zero!", return NC_FALSE);
		}, "memory error!", return NC_FALSE);
		NC_PCALL({ // action //
			size = NC_ALIGN(size, alig);
			NC_MEM_FREE(*data, size);
		}, "memory error!", return NC_FALSE);
		// results //
		return NC_TRUTH;
	}
private:
	static inline size_t& get_size_back() { static size_t s_size = NC_ZERO; return s_size; }
};
/// reference_type
/// description:
/// --smart "shared" pointer in nw implementation
/// --allocates object due to given allocator
/// --mem_reference gets deleted if there is no any other mem_refs for it
/// interface:
/// ->create nc_ref_tt
/// ->make_ref with particular allocator;
/// -> set_ref for other keepers -> use this as a pointer
template <typename tval, class tgiver = nc_heap_alloc_t>
class nc_ref_tt
{
public:
	using ref_t = nc_ref_tt<tval, tgiver>;
	using ref_tc = const ref_t;
	using val_t = tval;
	using val_tc = const val_t;
	using count_t = size_t;
	using count_tc = count_t;
public:
	inline nc_ref_tt() : m_ref(NC_NULL), m_counter(NC_NULL) { }
	inline nc_ref_tt(val_t& value) : nc_ref_tt() { set_ref(value); }
	inline nc_ref_tt(ref_tc& copy) : nc_ref_tt() { set_ref(copy); }
	inline nc_ref_tt(ref_t&& copy) : nc_ref_tt() { set_ref(copy); }
	template<typename tval_ = tval, class tgiver_ = tgiver>
	nc_ref_tt(const nc_ref_tt<tval_, tgiver_>& copy) : nc_ref_tt() { set_ref(copy); }
	template<typename tval_ = tval, class tgiver_ = tgiver>
	nc_ref_tt(nc_ref_tt<tval_, tgiver_>&& copy) : nc_ref_tt() { set_ref(copy); }
	inline ~nc_ref_tt() { remake(); }
	// getters //
	template<typename tname = val_t> tname* get_ref()             { return static_cast<tname*>(m_ref); }
	template<typename tname = val_t> const tname* get_ref() const { return static_cast<const tname*>(m_ref); }
	template<typename tname = val_t> tname& get_val()             { return *static_cast<tname*>(m_ref); }
	template<typename tname = val_t> const tname& get_val() const { return *static_cast<const tname*>(m_ref); }
	inline count_tc get_count() const    { return *m_counter; }
	inline count_t* get_counter()        { return m_counter; }
	inline count_tc* get_counter() const { return m_counter; }
	// setters //
	ref_t& set_ref(val_tc& ref) { // setting of allocated data //
		remake();
		m_ref = &ref;
		giver_t::static_take(&m_counter, sizeof(count_t), alignof(count_t));
		new(m_counter)count_t(NC_UNIT);
		return *this;
	}
	template<typename tval_ = tval, class tgiver_ = tgiver>
	ref_t& set_ref(const nc_ref_tt<tval_, tgiver_>& ref) { // sharing of references //
		remake();
		nc_ref_tt<tval_, tgiver_>& temp = const_cast<nc_ref_tt<tval_, tgiver_>&>(ref);
		m_ref = temp.get_ref<val_t>();
		m_counter = temp.get_counter();
		if (m_counter != NC_NULL) { *m_counter += 1; }
		return *this;
	}
	// predicates //
	inline v1bit_t has_ref() const     { return m_ref != NC_NULL; }
	inline v1bit_t has_counter() const { return get_counter() != NC_NULL; }
	inline v1bit_t has_count() const               { return get_count() != NC_NULL; }
	inline v1bit_t has_count(count_tc count) const { return get_count() >= count; }
	inline v1bit_t is_valid() const { return has_ref() && has_counter(); }
	// commands //
	inline ref_t& remake() {
		if (m_counter != NC_NULL) {
			if ((*m_counter -= 1) == NC_ZERO) {
				// we could deallocate it as well as we do with the counter but this pointer can be polymorphic; //
				NC_MEM_DEL_ONE(tval, m_ref);
				// NC_CHECK(giver_t::static_free(&m_counter, sizeof(count_t), alignof(count_t)), "memory error!", return *this);
				m_counter->~count_t();
				NC_CHECK(giver_t::static_free(&m_counter, sizeof(count_t), alignof(count_t)), "memory error!", return *this);
			}
		}
		m_ref = NC_NULL;
		m_counter = NC_NULL;
		return *this;
	}
	template <typename tname, typename ... targs> nc_ref_tt<val_t>& remake(targs&& ... args) {
		remake();
		NC_CHECK(giver_t::static_take(&m_ref, sizeof(tname), alignof(tname)), "memory error!", return *this);
		new(m_ref)tname(std::forward<targs>(args)...);
		NC_CHECK(giver_t::static_take(&m_counter, sizeof(count_t), alignof(count_t)), "memory error!", return *this);
		new(m_counter)count_t(NC_UNIT);
		return *this;
	}
	// operators //
	inline ref_t& operator=(ref_tc& copy) { return set_ref(copy); }
	inline ref_t& operator=(ref_t&& copy) { return set_ref(copy); }
	template<typename tval_ = tval, class tgiver_ = tgiver>
	inline ref_t& operator=(const nc_ref_tt<tval_, tgiver_>& copy) { return set_ref(copy); }
	template<typename tval_ = tval, class tgiver_ = tgiver>
	inline ref_t& operator=(nc_ref_tt<tval_, tgiver_>&& copy)      { return set_ref(copy); }
	// // referencing // //
	inline val_t* operator&()         { return m_ref; }
	inline val_tc* operator&() const  { return m_ref; }
	inline val_t& operator*()         { return *(m_ref); }
	inline val_tc& operator*() const  { return *(m_ref); }
	inline val_t* operator->()        { return (m_ref); }
	inline val_tc* operator->() const { return (m_ref); }
	// // convertion // //
	inline operator v1bit_t() const     { return m_ref != NC_NULL; }
	inline operator val_t*()        { return static_cast<val_t*>(m_ref); }
	inline operator val_tc*() const { return static_cast<val_tc*>(m_ref); }
	inline operator val_t&()        { return static_cast<val_t&>(*m_ref); }
	inline operator val_tc&() const { return static_cast<val_tc&>(*m_ref); }
	template<typename tname> operator tname*()               { return static_cast<tname*>(m_ref); }
	template<typename tname> operator const tname*() const   { return static_cast<const tname*>(m_ref); }
	template<typename tval_, class tgiver_> operator nc_ref_tt<tval_, tgiver_>()       { return nc_ref_tt<tval_, tgiver_>(*this); }
	template<typename tval_, class tgiver_> operator nc_ref_tt<tval_, tgiver_>() const { return nc_ref_tt<tval_, tgiver_>(*this); }
	// // --logic
	inline v1bit_t operator==(ref_tc& ref) const { return m_ref == ref.get_ref(); }
	inline v1bit_t operator!=(ref_tc& ref) const { return m_ref != ref.get_ref(); }
private:
	mutable val_t* m_ref;
	mutable count_t* m_counter;
};
#		endif	// NC_REF_OWN //
#	endif	// NC_REF //
// end_of_file //
#endif	// NC_LIB_REFERENCE_HPP //