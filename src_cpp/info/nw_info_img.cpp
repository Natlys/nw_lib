#include "nw_lib_pch.hpp"
#include "nw_info_img.h"
#if (defined NW_API)
#	include "nw_info_err.h"
namespace NW
{
	op_stream_t& img_bmp_info::operator<<(op_stream_t& stm) const {
		stm.write(reinterpret_cast<byte_tc*>(&file_info), sizeof(file_info));
		stm.write(reinterpret_cast<byte_tc*>(&data_info), sizeof(data_info));
		return stm;
	}
	ip_stream_t& img_bmp_info::operator>>(ip_stream_t& stm) {
		stm.read(reinterpret_cast<byte_t*>(&file_info), sizeof(file_info));
		stm.read(reinterpret_cast<byte_t*>(&data_info), sizeof(data_info));
		return stm;
	}
}
#endif	// NW_API