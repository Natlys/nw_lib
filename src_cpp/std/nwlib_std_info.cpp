#include "nwlib_pch.hpp"
#include "nwlib_std_info.h"
#if (defined NW_API)
namespace NWLIB
{
	a_info::a_info()
	{
	}
	// --setters
	// --operators
	stm_out& operator<<(stm_out& stm, const a_info& info) { return info.operator<<(stm); }
	stm_in& operator>>(stm_in& stm, a_info& info) { return info.operator>>(stm); }
}
namespace NWLIB
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
#endif	// NW_API