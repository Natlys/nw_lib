#include "nw_lib_pch.hpp"
#include "nw_mem_alloc.h"
#if (defined NW_API)
#	include "../std/nw_std_err.h"
namespace NW
{
	mem_giver::mem_giver() :
		m_data(NW_NULL),
		m_size(NW_NULL),
		m_back(NW_NULL),
		m_used(NW_NULL)
	{
	}
	mem_giver::mem_giver(ptr_t data, size_t size) :
		mem_giver()
	{
		NW_CHECK(remake(data, size), "remake error!", return);
	}
	mem_giver::~mem_giver()
	{
		NW_CHECK(!has_used(), "memory leak!", return);
	}
	// --setters
	v1nil mem_giver::set_data(ptr_t data) {
		m_data = reinterpret_cast<byte_t*>(data);
	}
	v1nil mem_giver::set_size(size_tc size) {
		m_size = size;
		m_back = NW_NULL;
		m_used = NW_NULL;
	}
	// --==<core_methods>==--
	v1bit mem_giver::remake()
	{
		NW_CHECK(has_data(), "no data!", return NW_FALSE);
		NW_CHECK(has_size(), "no size!", return NW_FALSE);
		NW_CHECK(has_free(), "must be free!", return NW_FALSE);
		NW_CHECK(!has_used(), "must not be used!", return NW_FALSE);

		return NW_TRUE;
	}
	// --==</core_methods>==--
}
namespace NW
{
	mem_giver_arena::mem_giver_arena() :
		mem_giver(),
		m_free_list(NW_NULL)
	{
	}
	mem_giver_arena::mem_giver_arena(ptr_t data, size_t size) :
		mem_giver(data, size),
		m_free_list(NW_NULL)
	{
	}
	mem_giver_arena::~mem_giver_arena()
	{
	}
	// --==<core_methods>==--
	v1bit mem_giver_arena::remake()
	{
		NW_CHECK(mem_giver::remake(), "remake error!", return NW_FALSE);

		m_free_list = NW_NULL;

		return NW_TRUE;
	}
	ptr_t mem_giver_arena::take(size_t size, size_t alig) {
		NW_CHECK(size != NW_NULL, "memory error!", return NW_NULL);
		ptr_t data = NW_NULL;
		// 100% essential thing for this allocator!;
		alig = NW_NUM_MAX(alig, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, alig);
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
	v1nil mem_giver_arena::free(ptr_t data, size_t size, size_t alig) {
		NW_CHECK(has_data(data), "memory error!", return);
		NW_CHECK(size > NW_NULL, "memory_error!", return);
		// 100% essential thing for this allocator!;
		alig = NW_NUM_MAX(alig, NW_DEFAULT_SIZE);
		size = NW_ALIGN(size, alig);
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
	mem_giver_heap::mem_giver_heap()
	{
	}
	mem_giver_heap::~mem_giver_heap()
	{
	}
	// --core_methods
	v1bit mem_giver_heap::remake()
	{
		NW_CHECK(has_data(), "this allocator must use only heap!", return NW_FALSE);
		NW_CHECK(has_size(), "this allocator must use only heap!", return NW_FALSE);

		return NW_TRUE;
	}
	ptr_t mem_giver_heap::take(size_t size, size_t alig)
	{
		size = NW_ALIGN(size, alig);
		m_used += size; m_back += size;
		return ::malloc(size);
	}
	v1nil mem_giver_heap::free(ptr_t data, size_t size, size_t alig)
	{
		size = NW_ALIGN(size, alig);
		m_used -= size; m_back -= size;
		::free(data);
	}
}
#endif	// NW_API