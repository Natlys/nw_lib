#ifndef NWLIB_MEM_SYSTEM_H
#define NWLIB_MEM_SYSTEM_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "nwlib_mem_alloc.h"
#include "std/nwlib_std_sing.h"
namespace NWLIB
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
		void update();
	};
}
namespace NWLIB
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
#endif	// NW_API
#endif	// NWLIB_MEM_SYSTEM_H