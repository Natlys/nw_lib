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
		inline ptr_t operator new(size_t size, ptr_t ptr) { return ::operator new(size, ptr); }
		inline ptr_t operator new(size_t size)            { return mem_sys::get().alloc(size); }
		inline ptr_t operator new[](size_t size)          { return mem_sys::get().alloc(size); }
		inline v1nil operator delete(ptr_t ptr, size_t size)   { mem_sys::get().dealloc(ptr, size); }
		inline v1nil operator delete[](ptr_t ptr, size_t size) { mem_sys::get().dealloc(ptr, size); }
	};
}
#endif
#endif	// NW_MEM_COMPONENT_H