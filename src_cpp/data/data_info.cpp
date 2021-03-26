#include <nwl_pch.hpp>
#include "data_info.h"

namespace NW
{
	stm_out& img_bmp_info::operator<<(stm_out& stm) const {
		stm.write(reinterpret_cast<const sbyte*>(&file), sizeof(file));
		stm.write(reinterpret_cast<const sbyte*>(&data), sizeof(data));
		return stm;
	}
	stm_in& img_bmp_info::operator>>(stm_in& stm) {
		stm.read(reinterpret_cast<sbyte*>(&file), sizeof(file));
		stm.read(reinterpret_cast<sbyte*>(&data), sizeof(data));
		return stm;
	}
}