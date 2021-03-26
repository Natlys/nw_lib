#ifndef NWL_MEMORY_SYSTEM_H
#define NWL_MEMORY_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_sing.h>
#include "mem_alloc.h"
namespace NW
{
	/// memory_system singleton class
	class NW_API mem_sys : public t_singleton<mem_sys>, public mem_arena
	{
		friend class t_singleton<mem_sys>;
	private:
		mem_sys();
	public:
		~mem_sys();
		// --core_methods
	};
}
namespace NW
{
	/// abstract memory_user
	/// description:
	/// --overrides default new/delete operators
	/// so that the memory is allocated by memory system
	class NW_API a_mem_user
	{
	protected:
		a_mem_user() = default;
	public:
		virtual ~a_mem_user() = default;
		// --operators
		inline void* operator new(size block_size, ptr block_ptr)     { return ::operator new(block_size, block_ptr); }
		inline void* operator new(size block_size)                    { return mem_sys::get().alloc(block_size); }
		inline void* operator new[](size block_size)                  { return mem_sys::get().alloc(block_size); }
		inline void operator delete(ptr block_ptr, size block_size)   { mem_sys::get().dealloc(block_ptr, block_size); }
		inline void operator delete[](ptr block_ptr, size block_size) { mem_sys::get().dealloc(block_ptr, block_size); }
	};
}
#endif	// NWL_MEMORY_SYSTEM_H