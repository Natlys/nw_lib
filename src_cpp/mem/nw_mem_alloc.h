#ifndef NW_MEM_ALLOCATION_H
#define NW_MEM_ALLOCATION_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	define NW_DEFAULT_SIZE NW_CAST_SIZE(16ul)
namespace NW
{
	/// memory_link struct
	struct NW_API mem_link
	{
		using link_t = mem_link;
	public:
		link_t* m_link;
		size_t m_size;
	public:
		constexpr inline mem_link() : m_link(NW_NULL), m_size(NW_NULL) { }
		// --getters
		inline link_t* get_link(size_t size) {
			link_t* data = NW_NULL;
			if (m_link != NW_NULL) { // try own links;
				if (data = m_link->get_link(size)) {
					if (m_link->m_size == NW_NULL) { // no more space; maybe it is going to be used;
						m_link = m_link->m_link;
					}
				}
			}
			if (data == NW_NULL && this->has_size(size)) { // no one link can help; try own storage;
				data = this;
				m_size -= size;
			}
			return data;
		}
		// --predicates
		inline v1bit has_size(size_t size) const { return m_size == size; }
		inline v1bit has_link(size_t size) const { if (m_link) { return m_link->has_link(size); } return has_size(size); }
		// --operators
		template <typename tname> operator tname* () { return reinterpret_cast<tname*>(this); }
		template <typename tname> operator const tname* () const { return reinterpret_cast<const tname*>(this); }
		template <typename tname> operator tname& () { return *reinterpret_cast<tname*>(this); }
		template <typename tname> operator const tname& () const { return *reinterpret_cast<const tname*>(this); }
	};
	/// memory_link typed struct
	template<typename tdata>
	struct t_mem_link
	{
		using link_t = t_mem_link<tdata>;
		using link_tc = const link_t;
		using data_t = tdata;
		using data_tc = const data_t;
	public:
		constexpr inline t_mem_link() : m_link(NW_NULL), m_data(NW_NULL) {}
		// --getters
		// --operators
		inline link_t* operator++(void)        { return m_link; }
		inline link_tc* operator++(void) const { return m_link; }
		inline link_t* operator++(int)        { return m_link; }
		inline link_tc* operator++(int) const { return m_link; }
		template <typename tname> operator tname* ()             { return static_cast<tname*>(m_data); }
		template <typename tname> operator const tname* () const { return static_cast<const tname*>(m_data); }
		template <typename tname> operator tname& ()             { return *static_cast<tname*>(m_data); }
		template <typename tname> operator const tname& () const { return *static_cast<const tname*>(m_data); }
	public:
		link_t* m_link;
		data_t* m_data;
	};
}
namespace NW
{
	/// abstract memory_giver class
	class NW_API mem_giver
	{
	public:
		mem_giver();
		mem_giver(ptr_t data, size_t size);
		virtual ~mem_giver();
		// --getters
		inline ptr_t get_data()        { return m_data; }
		inline ptr_tc get_data() const { return m_data; }
		inline ptr_t get_data(size_tc offset)        { return &m_data[offset]; }
		inline ptr_tc get_data(size_tc offset) const { return &m_data[offset]; }
		inline size_tc get_size() const { return m_size; }
		inline size_tc get_back() const { return m_back; }
		inline size_tc get_used() const { return m_used; }
		inline size_tc get_free() const { return m_size - m_used; }
		// --setters
		v1nil set_data(ptr_t data);
		v1nil set_size(size_tc size);
		// --predicates
		inline v1bit has_data() const { return m_data != NW_NULL; }
		inline v1bit has_data(ptr_tc data) const { return (data >= &m_data[0]) && (data <= &m_data[m_size]); }
		inline v1bit has_size(size_tc size = 1u) const { return m_size >= size; }
		inline v1bit has_back(size_tc size = 1u) const { return (m_size - get_back()) >= size; }
		inline v1bit has_used(size_tc size = 1u) const { return get_used() >= size; }
		inline v1bit has_free(size_tc size = 1u) const { return get_free() >= size; }
		// --core_methods
		virtual v1bit remake();
		v1bit remake(ptr_t data, size_tc size) { set_data(data); set_size(size); return remake(); }
		// // --instance
		virtual ptr_t take(size_t size, size_t align) = 0;
		template<typename tname> tname* take(size_t count) { return reinterpret_cast<tname*>(take(count * sizeof(tname), alignof(tname))); }
		virtual v1nil free(ptr_t data, size_t size, size_t align) = 0;
		template<typename tname> v1nil free(tname* data, size_t count) { free(data, count * sizeof(tname), alignof(tname)); }
		template<typename tname, typename ... args>
		tname* new_one(args&& ... arguments)     { return new(take<tname>(1u))tname(std::forward<args>(arguments)...); }
		template<typename tname>
		tname* new_arr(size_t count)             { return take<tname>(count); }
		template<typename tname>
		v1nil del_one(tname* data)               { data->~tname(); free<tname>(data, 1u); }
		template <typename tname>
		v1nil del_arr(tname* data, size_t count) { for (v1u itr = 0u; itr < count; itr++) { data[itr].~tname(); } free<tname>(data, count); }
	protected:
		byte_t* m_data; // chunck of bytes;
		size_t m_size;  // current block space;
		size_t m_back;  // maximally used space;
		size_t m_used;  // currently used space;
	};
}
namespace NW
{
	/// memory_giver_arena class
	/// description:
	/// --just a chunk of bytes works with ptr and char* pointers
	class NW_API mem_giver_arena : public mem_giver
	{
	public:
		mem_giver_arena();
		mem_giver_arena(ptr_t data, size_t size);
		virtual ~mem_giver_arena();
		// --core_methods
		virtual v1bit remake() override;
		virtual ptr_t take(size_t size, size_t alig) override;
		virtual v1nil free(ptr_t data, size_t size, size_t alig) override;
	private:
		mem_link* m_free_list;
	};
}
namespace NW
{
	class NW_API mem_giver_heap : public mem_giver
	{
	public:
		mem_giver_heap();
		virtual ~mem_giver_heap();
		// --core_methods
		virtual v1bit remake() override;
		virtual ptr_t take(size_t size, size_t alig) override;
		virtual v1nil free(ptr_t data, size_t size, size_t alig) override;
		static inline ptr_t static_take(size_t size, size_t alig)             { return ::malloc(NW_ALIGN(size, alig)); }
		static inline v1nil static_free(ptr_t data, size_t size, size_t alig) { ::free(data); }
	private:
	};
}
#endif	// NW_API
#endif	// NW_MEM_ALLOCATION_H