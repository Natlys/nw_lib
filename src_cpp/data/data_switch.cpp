#include <nwl_pch.hpp>
#include "data_switch.h"
#include <core/nwl_switch.h>
#include <core/nwl_str.h>
#include <io/io_err.h>
namespace NW
{
	template<> cstr convert_enum<data_types, cstr>(data_types data_type) {
		switch (data_type) {
		case DT_BOOL: return "DT_BOOL";
		case DT_SINT8: return "DT_SINT8";
		case DT_VEC2_SINT8: return "DT_VEC2_UINT8";
		case DT_VEC3_SINT8: return "DT_VEC3_SINT8";
		case DT_VEC4_SINT8:	return "DT_VEC4_SINT8";

		case DT_UINT8: return "DT_UINT8";
		case DT_VEC2_UINT8: return "DT_VEC2_UINT8";
		case DT_VEC3_UINT8: return "DT_VEC3_UINT8";
		case DT_VEC4_UINT8: return "DT_VEC4_UINT8";

		case DT_SINT16: return "DT_SINT16";
		case DT_VEC2_SINT16: return "DT_VEC2_SINT16";
		case DT_VEC3_SINT16: return "DT_VEC3_SINT16";
		case DT_VEC4_SINT16: return "DT_VEC4_SINT16";

		case DT_UINT16: return "DT_UINT16";
		case DT_VEC2_UINT16: return "DT_VEC2_UINT16";
		case DT_VEC3_UINT16: return "DT_VEC3_UINT16";
		case DT_VEC4_UINT16: return "DT_VEC4_UINT16";

		case DT_SINT32: return "DT_SINT32";
		case DT_VEC2_SINT32: return "DT_VEC2_SINT32";
		case DT_VEC3_SINT32: return "DT_VEC3_SINT32";
		case DT_VEC4_SINT32: return "DT_VEC4_SINT32";

		case DT_UINT32: return "DT_UINT32";
		case DT_VEC2_UINT32: return "DT_VEC2_UINT32";
		case DT_VEC3_UINT32: return "DT_VEC3_UINT32";
		case DT_VEC4_UINT32: return "DT_VEC4_UINT32";

		case DT_FLOAT32: return "DT_FLOAT32";
		case DT_VEC2_FLOAT32: return "DT_VEC2_FLOAT32";
		case DT_VEC3_FLOAT32: return "DT_VEC3_FLOAT32";
		case DT_VEC4_FLOAT32: return "DT_VEC4_FLOAT32";

		case DT_USER_DATA: return "DT_USER_DATA";

		default: throw run_error(__FILE__, __LINE__); break;
		}
		return "DT_DEFAULT";
	}
	template<> cstr convert_enum<pixel_formats, cstr>(pixel_formats pxl_format) {
		switch (pxl_format) {
		case PXF_R8_SINT8: return "PXF_R8_SINT8"; break;

		case PXF_R32_SINT32: return "PXF_R32_SINT32"; break;
		case PXF_R16G16_SINT32: return "PXF_R16G16_SINT32"; break;
		case PXF_R8G8B8_SINT32: return "PXF_R8G8B8_SINT32"; break;
		case PXF_R8G8B8A8_SINT32: return "PXF_R8G8B8A8_SINT32"; break;

		case PXF_R32_UINT32: return "PXF_R32_UINT32"; break;
		case PXF_R16G16_UINT32: return "PXF_R16G16_UINT32"; break;
		case PXF_R8G8B8_UINT32: return "PXF_R8G8B8_UINT32"; break;
		case PXF_R8G8B8A8_UINT32: return "PXF_R8G8B8A8_UINT32"; break;

		case PXF_D24S8_UINT32: return "PXF_D24S8_UINT32"; break;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return "PXF_DEFAULT";
	}
	si32 dt_get_prim_count(data_types data_type) {
		switch (data_type) {
		case DT_BOOL: return 1;
		case DT_VEC2_BOOL: return 2;
		case DT_VEC3_BOOL: return 3;
		case DT_VEC4_BOOL: return 4;

		case DT_SINT8: return 1;
		case DT_VEC2_SINT8: return 2;
		case DT_VEC3_SINT8: return 3;
		case DT_VEC4_SINT8: return 4;

		case DT_UINT8: return 1;
		case DT_VEC2_UINT8: return 2;
		case DT_VEC3_UINT8: return 3;
		case DT_VEC4_UINT8: return 4;

		case DT_SINT16: return 1;
		case DT_VEC2_SINT16: return 2;
		case DT_VEC3_SINT16: return 3;
		case DT_VEC4_SINT16: return 4;

		case DT_UINT16: return 1;
		case DT_VEC2_UINT16: return 2;
		case DT_VEC3_UINT16: return 3;
		case DT_VEC4_UINT16: return 4;

		case DT_SINT32: return 1;
		case DT_VEC2_SINT32: return 2;
		case DT_VEC3_SINT32: return 3;
		case DT_VEC4_SINT32: return 4;

		case DT_UINT32: return 1;
		case DT_VEC2_UINT32: return 2;
		case DT_VEC3_UINT32: return 3;
		case DT_VEC4_UINT32: return 4;

		case DT_FLOAT32: return 1;
		case DT_VEC2_FLOAT32: return 2;
		case DT_VEC3_FLOAT32: return 3;
		case DT_VEC4_FLOAT32: return 4;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0;
	}
	size dt_get_size(data_types data_type, si32 count) {
		switch (data_type) {
		case DT_BOOL:
		case DT_SINT8: case DT_UINT8:
			return 1;
		case DT_VEC2_SINT8: case DT_VEC2_UINT8:
		case DT_SINT16: case DT_UINT16:
			return 2;
		case DT_FLOAT32:
		case DT_SINT32: case DT_UINT32:
		case DT_VEC2_SINT16: case DT_VEC2_UINT16:
			return 4;

		case DT_VEC2_FLOAT32:
		case DT_VEC2_SINT32: case DT_VEC2_UINT32:
		case DT_VEC4_SINT16: case DT_VEC4_UINT16:
			return 4 * 2;
		case DT_VEC3_FLOAT32:
		case DT_VEC3_SINT32: case DT_VEC3_UINT32:
			return 4 * 3;
		case DT_VEC4_FLOAT32:
		case DT_VEC4_SINT32: case DT_VEC4_UINT32:
			return 4 * 4;

		case DT_USER_DATA: return 4;
		default: throw run_error(__FILE__, __LINE__); break;
		}
		return 0;
	}
	size dt_get_aligned_size(data_types data_type, si32 count) {
		size aligned_size = 0;
		switch (data_type) {
		case DT_BOOL: aligned_size = 4; break;

		case DT_SINT8: aligned_size = 4; break;

		case DT_UINT8: aligned_size = 4; break;

		case DT_SINT16: aligned_size = 4; break;

		case DT_UINT16: aligned_size = 4; break;

		case DT_SINT32: aligned_size = 4; break;

		case DT_UINT32: aligned_size = 4; break;

		case DT_FLOAT32: aligned_size = 4; break;
		case DT_VEC2_FLOAT32: aligned_size = 8; break;
		case DT_VEC3_FLOAT32: aligned_size = 16; break;
		case DT_VEC4_FLOAT32: aligned_size = 16; break;
		case DT_MAT2_FLOAT32: aligned_size = 32; break;
		case DT_MAT3_FLOAT32: aligned_size = 64; break;
		case DT_MAT4_FLOAT32: aligned_size = 64; break;

		case DT_USER_DATA: aligned_size = 4; break;

		default: throw run_error(__FILE__, __LINE__); aligned_size = 0; break;
		}
		return count * ((aligned_size + (aligned_size - 1)) & ~(aligned_size - 1));
	}
	pixel_formats pxf_get(ui8 nof_channels) {
		switch (nof_channels) {
		case 1: return PXF_R8_UINT8;
		case 2: return PXF_R8G8_UINT16;
		case 3: return PXF_R8G8B8_UINT32;
		case 4: return PXF_R8G8B8A8_UINT32;
		default: break;
		}
		return PXF_DEFAULT;
	}
	ui8 pxf_get(pixel_formats pixel_format) {
		switch (pixel_format) {
		case PXF_R8_SINT8: case PXF_R8_UINT8:
		case PXF_D32_SINT32: case PXF_D32_UINT32:
		case PXF_S8_SINT8: case PXF_S8_UINT8:
		case PXF_R32_SINT32: case PXF_R32_UINT32:
			return 1;
		case PXF_R16G16_SINT32: case PXF_R16G16_UINT32:
		case PXF_D24S8_SINT32: case PXF_D24S8_UINT32:
			return 2;
		case PXF_R8G8B8_SINT32: case PXF_R8G8B8_UINT32:
			return 3;
		case PXF_R8G8B8A8_SINT32: case PXF_R8G8B8A8_UINT32:
			return 4;
		default: break;
		}
		return 0;
	}
}