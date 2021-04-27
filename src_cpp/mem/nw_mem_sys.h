#ifndef NW_MEM_SYSTEM_H
#define NW_MEM_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "std/nw_std_sing.h"
#	include "nw_mem_alloc.h"
#	define NW_MAX_MEMORY   1 << 23
namespace NW
{
	/// memory_system singleton class
	class NW_API mem_sys : public t_singleton<mem_sys>, public mem_giver_arena
	{
	public:
		friend class t_singleton<mem_sys>;
	public:
		mem_sys();
		~mem_sys();
		// --core_methods
		v1bit init();
		inline v1bit init(size_tc size) { set_size(size); return init(); }
		v1bit quit();
		v1nil update();
		static inline ptr_t static_take(size_t size, size_t alig)             { return mem_sys::get().take(size, alig); }
		static inline v1nil static_free(ptr_t data, size_t size, size_t alig) { mem_sys::get().free(data, size, alig); }
	};
}
#endif	// NW_API
#endif	// NW_MEM_SYSTEM_H