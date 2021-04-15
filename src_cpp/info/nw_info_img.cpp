#include "nw_lib_pch.hpp"
#include "nw_info_img.h"
#if (defined NW_API)
#	include "../io/nw_io_err.h"
namespace NW
{
	stm_out& img_bmp_info::operator<<(stm_out& stm) const {
		stm.write(reinterpret_cast<sbyte_tc*>(&file_info), sizeof(file_info));
		stm.write(reinterpret_cast<sbyte_tc*>(&data_info), sizeof(data_info));
		return stm;
	}
	stm_in& img_bmp_info::operator>>(stm_in& stm) {
		stm.read(reinterpret_cast<sbyte_t*>(&file_info), sizeof(file_info));
		stm.read(reinterpret_cast<sbyte_t*>(&data_info), sizeof(data_info));
		
		NW_CHECK(get_channels() >= 1u && get_channels() <= 4u, "load error!", return stm);

		if (get_channels() == 1u) {
			pal_pxl.resize(data_info.clrs_used * get_channels(), 0u);
			pal_idx.resize(data_info.image_size, 0u);

			stm.read(reinterpret_cast<sbyte_t*>(&pal_pxl[0]), pal_pxl.size());
			stm.read(reinterpret_cast<sbyte_t*>(&pal_idx[0]), pal_idx.size());

			for (v1s idx = 0; idx < pal_idx.size(); idx++) {
				set_pixel(pal_pxl[pal_idx[idx]], idx);
			}
		}
		else {
			v1s pad = ((get_size_x()) % 4) % 4;
			v1s beg_x, beg_y;
			v1s end_x, end_y;
			v1s dir_x, dir_y;
			if (data_info.width < 0) { beg_x = +data_info.width - 1; end_x = -1; dir_x = -1; }
			else { beg_x = +0; end_x = +data_info.width; dir_x = +1; }
			if (data_info.height < 0) { beg_y = +data_info.height - 1; end_y = -1; dir_y = -1; }
			else { beg_y = +0; end_y = +data_info.height; dir_y = +1; }
			stm.seekg(file_info.data_offset, stm.beg);
			for (v1s iy = beg_y; iy != end_y; iy += dir_y) {
				for (v1s ix = beg_x; ix != end_x; ix += dir_x) {
					v1u32 temp;
					stm >> temp;
					set_pixel(temp, ix, iy);
				}
				stm.seekg(pad, stm.cur);
			}
		}
		return stm;
	}
}
#endif	// NW_API