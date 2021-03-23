#ifndef NW_DATA_RESOURCE_H
#define NW_DATA_RESOURCE_H
#include <nwl_core.hpp>
#include <core/nwl_str.h>
#include <io/io_stm.h>
namespace NW
{
	/// abstract data_resource class
	class NW_API a_data_rsc
	{
	protected:
		a_data_rsc();
	public:
		virtual ~a_data_rsc();
		// --getters
		// --setters
		// --operators
		virtual stm_out& operator<<(stm_out& stm) const;
		virtual stm_in& operator>>(stm_in& stm);
	};
	stm_out& operator<<(stm_out& stm, const a_data_rsc& rsc);
	stm_in& operator>>(stm_in& stm, a_data_rsc& rsc);
}
#endif // NW_DATA_RESOURCE_H