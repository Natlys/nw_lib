#include "nw_lib_pch.hpp"
#include "nw_mem_alloc.h"
#if (defined NW_API)
#	include "io/nw_io_err.h"
namespace NW
{
	// --getters
#	if (NW_FALSE)
	mem_link::link_t* mem_link::get_link(size_t size) {
		mem_link* block = NW_NULL;
#		if (NW_FALSE)		// old barely working version with dangerous operations;
		if (this->size >= size) { this->size -= size; return this; }
		mem_link* data = this;
		mem_link* next_ptr = NW_NULL;
		while (data != NW_NULL && next_ptr != NW_NULL) {
			if (data = data->data) {
				if (next_ptr = data->data) {
					if (next_ptr->size >= size) {
						next_ptr->size -= size;
						if (data->size == NW_NULL) { data->data = next_ptr->data; }
						return next_ptr;
					}
				}
				else { break; }
			}
			else { break; }
		}
#		elif (NW_FALSE)		// another version with only two operations: own check and recursive call on childs;
		if (this->size >= size) { this->size -= size; block = this; }
		if (data != NW_NULL) { data->get_block(size); if (data->size == NW_NULL) { data = NW_NULL; } }
#		elif (NW_FALSE)		// next version: same as before but it is better to get rid of tail before use the head;
		if (data != NW_NULL) { data->get_block(size); if (data->size == NW_NULL) { data = NW_NULL; } }
		if (this->size >= size) { this->size -= size; block = this; }
#		elif (NW_FALSE)		// next version, the bag is fixed: resulting block was not changed by child links;
		if (this->link != NW_NULL) { // try own links;
			if ((block = this->link->get_link(size)) != NW_NULL) {
				if (this->link->size == NW_NULL) { // no link space; maybe it is going to be used;
					this->link = this->link->link;
				}
			}
		}
		if (block == NW_NULL) { // no one link can help;
			if (this->size >= size) { // use own storage;
				this->size -= size;
				block = this;
			}
		}
#		elif (NW_TRUE)		// next version: blocks can be retunred with offset(not the entire block);
		if (this->link != NW_NULL) { // try own links;
			if ((block = this->link->get_link(size)) != NW_NULL) {
				if (this->link->size == NW_NULL) { // no more space; maybe it is going to be used;
					this->link = this->link->link;
				}
			}
		}
		if (block == NW_NULL) { // no one link can help;
			if (has_size(size)) { // use own storage;
				block = this + (this->size -= size);
			}
		}
#		else
		NW_ERROR("does not work for now!", return NW_NULL);
#		endif
		return block;
	}
#	endif
	
}
namespace NW
{
	a_mem_alloc::a_mem_alloc(ptr_t data, size_tc size) :
		m_data(static_cast<byte_t*>(data)),
		m_size(size),
		m_back(NW_NULL),
		m_used(NW_NULL)
	{
	}
	a_mem_alloc::~a_mem_alloc()
	{
		NW_CHECK(!has_used(1u), "memory leak!", return);
	}
	// --==<core_methods>==--
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
	mem_arena::mem_arena(ptr_t data, size_tc size) :
		a_mem_alloc(data, size),
		m_free_list(NW_NULL)
	{
	}
	mem_arena::~mem_arena()
	{
	}
	// --==<core_methods>==--
	ptr_t mem_arena::alloc(size_t size, size_t align) {
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
	v1nil mem_arena::dealloc(ptr_t data, size_t size, size_t align) {
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
	mem_alloc_line::mem_alloc_line(ptr_t data, size_tc size) :
		a_mem_alloc(data, size)
	{
	}
	mem_alloc_line::~mem_alloc_line()
	{
	}
	// --==<core_methods>==--
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