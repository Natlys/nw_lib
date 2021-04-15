#ifndef NW_MEM_SYSTEM_H
#define NW_MEM_SYSTEM_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "std/nw_std_sing.h"
#	include "nw_mem_alloc.h"
namespace NW
{
	/// memory_system singleton class
	class NW_API mem_sys : public singleton_t<mem_sys>, public mem_arena
	{
		friend class singleton_t<mem_sys>;
	private:
		mem_sys();
	public:
		~mem_sys();
		// --core_methods
		void update();
	};
}
#endif	// NW_API
#endif	// NW_MEM_SYSTEM_H