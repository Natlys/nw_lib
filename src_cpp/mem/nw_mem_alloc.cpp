#include "nw_lib_pch.hpp"
#include "nw_mem_alloc.h"
#if (defined NW_API)
#	include "../info/nw_info_err.h"
namespace NW
{
	a_mem_alloc::a_mem_alloc(ptr_t data, size_t size) :
		m_data(static_cast<byte_t*>(data)),
		m_size(size),
		m_back(NW_NULL),
		m_used(NW_NULL)
	{
	}
	a_mem_alloc::~a_mem_alloc()
	{
		NW_CHECK(!has_used(), "memory leak!", return);
	}
	// --setters
	v1nil a_mem_alloc::set_data(ptr_t data) {
		m_data = reinterpret_cast<byte_t*>(data);
	}
	v1nil a_mem_alloc::set_size(size_tc size) {
		m_size = size;
		m_back = NW_NULL;
		m_used = NW_NULL;
	}
	// --==<core_methods>==--
	v1bit a_mem_alloc::remake()
	{
		NW_CHECK(has_data(), "no data!", return NW_FALSE);
		NW_CHECK(has_size(), "no size!", return NW_FALSE);
		NW_CHECK(has_free(), "must be free!", return NW_FALSE);
		NW_CHECK(!has_used(), "must not be used!", return NW_FALSE);

		return NW_TRUE;
	}
	ptr_t a_mem_alloc::realloc(ptr_t data, size_t size_old, size_t size_new) {
		size_t copy_size = NW_MATH_MIN(size_old, size_new);
		ptr_t new_data = alloc(size_new, NW_DEFAULT_SIZE);
		memmove(new_data, data, copy_size);
		dealloc(data, size_old, NW_DEFAULT_SIZE);
		return new_data;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_alloc_arena::mem_alloc_arena(ptr_t data, size_t size) :
		a_mem_alloc(data, size),
		m_free_list(NW_NULL)
	{
	}
	mem_alloc_arena::~mem_alloc_arena()
	{
	}
	// --==<core_methods>==--
	v1bit mem_alloc_arena::remake()
	{
		NW_CHECK(a_mem_alloc::remake(), "failed remake!", return NW_FALSE);

		return NW_TRUE;
	}
	ptr_t mem_alloc_arena::alloc(size_t size, size_t align) {
		NW_CHECK(size != NW_NULL, "memory error!", return NW_NULL);
		ptr_t data = NW_NULL;
		// 100% essential thing for this allocator!;
		align = NW_MATH_MAX(align, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, align);
		NW_CHECK(has_free(size), "memory error!", return NW_NULL);
#		if (NW_TRUE)
		if (m_free_list != NW_NULL) { // free list allocation is possible;
			if ((data = m_free_list->get_link(size)) != NW_NULL) { // free list search;
				if (m_free_list->m_size == NW_NULL) { // no more space; advance the head;
					m_free_list = m_free_list->m_link;
				}
			}
		}
#		endif
		if (data == NW_NULL) { // failed to get free_list block; default allocation with back-pointer advance;
			NW_CHECK(has_back(size), "memory error!", return NW_NULL);
			data = get_data(get_back());
			m_back += size;
		}
		m_used += size;
		return data;
	}
	v1nil mem_alloc_arena::dealloc(ptr_t data, size_t size, size_t align) {
		NW_CHECK(has_data(data), "memory error!", return);
		NW_CHECK(size > NW_NULL, "memory_error!", return);
		// 100% essential thing for this allocator!;
		align = NW_MATH_MAX(align, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, align);
		NW_CHECK(has_used(size), "memory error!", return);
		// memset(data, NW_NULL, size); dangerous to use because it can erase our free_list;
		mem_link* next_free_list = new(data)mem_link();
		next_free_list->m_link = m_free_list;
		next_free_list->m_size = size;
		m_free_list = next_free_list;
		// m_back -= size; it should not be changed back!
		m_used -= size;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_alloc_line::mem_alloc_line(ptr_t data, size_t size) :
		a_mem_alloc(data, size)
	{
	}
	mem_alloc_line::~mem_alloc_line()
	{
	}
	// --==<core_methods>==--
	v1bit mem_alloc_line::remake()
	{
		NW_CHECK(a_mem_alloc::remake(), "failed remake!", return NW_FALSE);

		return NW_TRUE;
	}
	ptr_t mem_alloc_line::alloc(size_t size, size_t align) {
		ptr_t data = NW_NULL;
		NW_CHECK(size != NW_NULL, "memory error", return NW_NULL);
		// not essential but i keep it just for consistency
		align = NW_MATH_MAX(align, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, align);
		NW_CHECK(has_free(size), "memory error!", return NW_NULL);
		data = get_data(get_used());
		m_back += size;
		m_used += size;
		return data;
	}
	v1nil mem_alloc_line::dealloc(ptr_t data, size_t size, size_t align) {
		NW_CHECK(data != get_data(m_used), "cannot linearly deallocate not the last block!", return);
		// not essential but i keep it just for consistency
		align = NW_MATH_MAX(align, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, align);
		NW_CHECK(has_used(size), "memory error!", return);
		// memset(data, NW_NULL, size); important data can be erased;
		m_back -= size;
		m_used -= size;
	}
	v1nil mem_alloc_line::clear() {
		// memset(m_data, NW_NULL, m_size); important data can be erased
		m_back = NW_NULL;
		m_used = NW_NULL;
	}
	// --==</core_methods>==--
}
#endif	// NW_API