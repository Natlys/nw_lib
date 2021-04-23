#include "nw_lib_pch.hpp"
#include "nw_info_mesh.h"
#if (defined NW_API)
#	include "nw_info_err.h"
namespace NW
{
	op_stream_t& mesh_obj_info::operator<<(op_stream_t& stm) const {
		return stm;
	}
	ip_stream_t& mesh_obj_info::operator>>(ip_stream_t& stm) {
		return stm;
	}
}
#endif	// NW_API