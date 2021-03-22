#ifndef NWL_INFO_H
#define NWL_INFO_H
#include <nwl_core.hpp>
#include <io/io_stm.h>
#include "nwl_str.h"
namespace NW
{
	/// abstract info struct
	class NW_API a_info
	{
	public:
		a_info();
		virtual ~a_info() = default;
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
	};
	stm_out& operator<<(stm_out& stm, const a_info& info);
	stm_in& operator>>(stm_in& stm, a_info& info);
}
#endif	// NWL_INFO_H