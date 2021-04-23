#ifndef NW_INFO_MESH_H
#define NW_INFO_MESH_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../iop/nw_iop_stm.h"
#	include "../iop/nw_iop_cmp.h"
#	include "../std/nw_std_array.h"
#	include "../mem/nw_mem_elem.h"
namespace NW
{
	struct mesh_obj_info : public a_iop_cmp
	{
	public:
	public:
		// --operators
		virtual op_stream_t& operator<<(op_stream_t& stm) const override;
		virtual ip_stream_t& operator>>(ip_stream_t& stm) override;
	};
}
#endif	// NW_API
#endif	// NW_INFO_MESH_H