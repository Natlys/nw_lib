#ifndef NWL_DATA_COMPONENT_H
#define NWL_DATA_COMPONENT_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <core/nwl_type.h>
#include <core/nwl_id.h>
#include <io/io_stm.h>
#include "data_lib.h"
namespace NW
{
	/// abstract data_component class
	class NW_API a_data_cmp
	{
	protected:
		a_data_cmp();
	public:
		virtual ~a_data_cmp();
		// --getters
		// --setters
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const = 0;
		virtual stm_in& operator>>(stm_in& stm) = 0;
	};
	stm_out& operator<<(stm_out& stm, const a_data_cmp& cmp);
	stm_in& operator>>(stm_in& stm, a_data_cmp& cmp);
}
#endif // NWL_DATA_COMPONENT_H