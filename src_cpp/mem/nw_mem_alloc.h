#ifndef NW_MEM_ALLOCATOR_H
#define NW_MEM_ALLOCATOR_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// memory_link struct
	struct NW_API mem_link
	{
	public:
		mem_link* block_ptr = nullptr;
		size block_size = 0;
	public:
		// --getters
		mem_link* get_block(size nof_bytes);
		// --operators
		template <typename mtype> inline operator mtype*() { return reinterpret_cast<mtype*>(this); }
	};
}
namespace NW
{
	/// abstract memory_allocator class
	class NW_API a_mem_alloc
	{
	public:
		a_mem_alloc(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~a_mem_alloc();
		// --getters
		inline ptr get_data()               { return &m_data_ptr[0]; }
		inline size get_data_size() const   { return m_data_size; }
		inline size get_alloc_size() const  { return m_alloc_size; }
		inline size get_free_size() const   { return m_data_size - m_alloc_size; }
		// --predicates
		inline v1b has_block(ptr block_ptr) const          { return (block_ptr >= &m_data_ptr[0]) && (block_ptr <= &m_data_ptr[m_data_size]); }
		inline v1b has_enough_size(size szof_memory) const { return get_free_size() > szof_memory; }
		// --core_methods
		virtual void* alloc(size memory_size, size align_size = sizeof(mem_link)) = 0;
		virtual void dealloc(ptr block_ptr, size dealloc_size) = 0;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) = 0;
		template<typename mtype, typename ... Args>
		mtype* new_one(Args&& ... Arguments);
		template<typename mtype>
		mtype* new_arr(size nof_alloc);
		template<typename mtype>
		void del_one(mtype* block_ptr);
		template<typename mtype>
		void del_arr(mtype* block_ptr, size nof_dealloc);
	protected:
		sbyte* m_data_ptr;
		size m_data_size;
		size m_alloc_size;
	};
	template<typename mtype, typename ... args>
	mtype* a_mem_alloc::new_one(args&& ... arguments) {
		mtype* block_ptr = reinterpret_cast<mtype*>(alloc(1ul * sizeof(mtype), __alignof(mtype)));
		new(block_ptr) mtype(std::forward<args>(arguments)...);
		return block_ptr;
	}
	template <typename mtype>
	mtype* a_mem_alloc::new_arr(size nof_alloc) {
		return reinterpret_cast<mtype*>(alloc(nof_alloc* sizeof(mtype), __alignof(mtype)));
	}
	template<typename mtype>
	void a_mem_alloc::del_one(mtype* block_ptr) {
		block_ptr->~mtype();
		dealloc(block_ptr, 1 * sizeof(mtype));
	}
	template <typename mtype>
	void a_mem_alloc::del_arr(mtype* block_ptr, size nof_dealloc) {
		for (size bi = 0; bi < nof_dealloc; bi++) { block_ptr[bi].~mtype(); }
		dealloc(block_ptr, nof_dealloc * sizeof(mtype));
	}
}
namespace NW
{
	/// memory_arena class
	/// Description:
	/// --Just a chunk of bytes works with Ptr and char* pointers
	class NW_API mem_arena : public a_mem_alloc
	{
	public:
		mem_arena(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~mem_arena();
		// --core_methods
		virtual void* alloc(size alloc_size, size align_size = sizeof(mem_link)) override;
		virtual void dealloc(ptr block_ptr, size dealloc_size) override;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) override;
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
		mem_alloc_line(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~mem_alloc_line();
		// --core_methods
		virtual void* alloc(size alloc_size, size align_size = sizeof(int)) override;
		virtual void dealloc(ptr block_ptr, size dealloc_size) override;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) override;
		void clear();
	};
}
#endif	// NW_API
#endif	// NW_MEM_ALLOCATOR_H