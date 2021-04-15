#ifndef NW_MEM_ALLOCATOR_H
#define NW_MEM_ALLOCATOR_H
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
	template<typename link_type>
	struct t_mem_link
	{
		using link_t = t_mem_link<link_type>;
	public:
		constexpr inline t_mem_link() : m_link(NW_NULL) {}
		// --getters
		// --operators
		template <typename tname> operator tname* () { return static_cast<tname*>(m_data); }
		template <typename tname> operator const tname* () const { return static_cast<const tname*>(m_data); }
		template <typename tname> operator tname& () { return *static_cast<tname*>(m_data); }
		template <typename tname> operator const tname& () const { return *static_cast<const tname*>(m_data); }
	public:
		link_t* m_link;
		link_type* m_data;
	};
}
namespace NW
{
	/// abstract memory_allocator class
	class NW_API a_mem_alloc
	{
	public:
		a_mem_alloc(ptr_t buffer = NW_NULL, size_tc space = NW_NULL);
		virtual ~a_mem_alloc();
		// --getters
		inline ptr_t get_data()        { return m_data; }
		inline ptr_tc get_data() const { return m_data; }
		inline ptr_t get_data(size_tc offset)        { return &m_data[offset]; }
		inline ptr_tc get_data(size_tc offset) const { return &m_data[offset]; }
		inline size_tc get_size() const { return m_size; }
		inline size_tc get_back() const { return m_back; }
		inline size_tc get_used() const { return m_used; }
		inline size_tc get_free() const { return m_size - m_used; }
		// --predicates
		inline v1bit has_data(ptr_t data) const   { return (data >= &m_data[0]) && (data <= &m_data[m_size]); }
		inline v1bit has_back(size_tc size) const { return (m_size - get_back()) >= size; }
		inline v1bit has_used(size_tc size) const { return get_used() >= size; }
		inline v1bit has_free(size_tc size) const { return get_free() >= size; }
		// --core_methods
		virtual ptr_t alloc(size_t size, size_t align) = 0;
		template<typename tname> tname* alloc(size_t count) { return reinterpret_cast<tname*>(alloc(count * sizeof(tname), alignof(tname))); }
		virtual v1nil dealloc(ptr_t data, size_t size, size_t align) = 0;
		template<typename tname> v1nil dealloc(tname* data, size_t count) { dealloc(data, count * sizeof(tname), alignof(tname)); }
		ptr_t realloc(ptr_t data, size_t size_old, size_t size_new);
		template<typename tname, typename ... args>
		tname* new_one(args&& ... arguments)     { return new(alloc<tname>(1u))tname(std::forward<args>(arguments)...); }
		template<typename tname>
		tname* new_arr(size_t count)             { return alloc<tname>(count); }
		template<typename tname>
		v1nil del_one(tname* data)               { data->~tname(); dealloc<tname>(data, 1u); }
		template <typename tname>
		v1nil del_arr(tname* data, size_t count) { for (v1u itr = 0u; itr < count; itr++) { data[itr].~tname(); } dealloc<tname>(data, count); }
	protected:
		byte_t* m_data; // chunck of bytes;
		size_t m_size;  // current block space;
		size_t m_back;  // maximally used space;
		size_t m_used;  // currently used space;
	};
}
namespace NW
{
	/// memory_arena class
	/// Description:
	/// --just a chunk of bytes works with ptr and char* pointers
	class NW_API mem_arena : public a_mem_alloc
	{
	public:
		mem_arena(ptr_t data = NW_NULL, size_tc space = NW_NULL);
		virtual ~mem_arena();
		// --core_methods
		virtual ptr_t alloc(size_t size, size_t align = NW_DEFAULT_SIZE) override;
		virtual v1nil dealloc(ptr_t data, size_t size, size_t align = NW_DEFAULT_SIZE) override;
	private:
		mem_link* m_free_list;
	};
}
namespace NW
{
	/// linear_memory_allocator class
	class NW_API mem_alloc_line: public a_mem_alloc
	{
	public:
		mem_alloc_line(ptr_t data = NW_NULL, size_t size = NW_NULL);
		virtual ~mem_alloc_line();
		// --core_methods
		virtual ptr_t alloc(size_t size, size_t align = NW_DEFAULT_SIZE) override;
		virtual v1nil dealloc(ptr_t data, size_t size, size_t align = NW_DEFAULT_SIZE) override;
		v1nil clear();
	};
}
#endif	// NW_API
#endif	// NW_MEM_ALLOCATOR_H