#ifndef NW_INFO_CMP_H
#define NW_INFO_CMP_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#include "ecs/nw_ecs_cmp.h"
#include "io/nw_io_stm.h"
namespace NW
{
	/// abstract information_component class
	class NW_API a_info_cmp
	{
	protected:
		a_info_cmp() = default;
	public:
		virtual ~a_info_cmp() = default;
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
	};
	inline stm_out& operator<<(stm_out& stm, const a_info_cmp& info) { return info.operator<<(stm); }
	inline stm_in& operator>>(stm_in& stm, a_info_cmp& info) { return info.operator>>(stm); }
}
#endif	// NW_API
#endif	// NW_INFO_CMP_H