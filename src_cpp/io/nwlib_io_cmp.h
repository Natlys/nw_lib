#ifndef NWLIB_IO_COMPONENT_H
#define NWLIB_IO_COMPONENT_H
#include "nwlib_core.hpp"
#if (defined NW_API)
#include "nwlib_io_flib.h"
#include "nwlib_io_stm.h"
namespace NWLIB
{
	/// input_output_component
	class NW_API a_io_cmp
	{
	protected:
		a_io_cmp();
	public:
		virtual ~a_io_cmp();
		// --getters
		// --setters
		// --predicates
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
		// --core_methods
	};
	NW_API stm_out& operator<<(stm_out& stm, const a_io_cmp& cmp);
	NW_API stm_in& operator>>(stm_in& stm, a_io_cmp& cmp);
}
#endif	// NW_API
#endif	// NWLIB_IO_COMPONENT_H