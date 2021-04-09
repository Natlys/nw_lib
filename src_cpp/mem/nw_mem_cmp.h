#ifndef NW_MEM_COMPONENT_H
#define NW_MEM_COMPONENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "nw_mem_sys.h"
namespace NW
{
	/// abstract memory_component
	/// description:
	/// --overrides default new/delete operators
	/// so that the memory is allocated by memory system
	class NW_API a_mem_cmp
	{
	protected:
		a_mem_cmp() = default;
	public:
		virtual ~a_mem_cmp() = default;
		// --operators
		inline void* operator new(size block_size, ptr block_ptr)     { return ::operator new(block_size, block_ptr); }
		inline void* operator new(size block_size)                    { return mem_sys::get().alloc(block_size); }
		inline void* operator new[](size block_size)                  { return mem_sys::get().alloc(block_size); }
		inline void operator delete(ptr block_ptr, size block_size)   { mem_sys::get().dealloc(block_ptr, block_size); }
		inline void operator delete[](ptr block_ptr, size block_size) { mem_sys::get().dealloc(block_ptr, block_size); }
	};
}
#endif
#endif	// NW_MEM_COMPONENT_H