#ifndef NWL_DATA_SWITCH_H
#define NWL_DATA_SWITCH_H
#include <nwl_core.hpp>
namespace NW
{
	enum data_types : ui32 {
		DT_DEFAULT = 0,
		DT_BOOL = 1,
		DT_VEC2_BOOL, DT_VEC3_BOOL, DT_VEC4_BOOL,
		DT_MAT2_BOOL, DT_MAT3_BOOL, DT_MAT4_BOOL,
		DT_SINT8,
		DT_VEC2_SINT8, DT_VEC3_SINT8, DT_VEC4_SINT8,
		DT_MAT2_SINT8, DT_MAT3_SINT8, DT_MAT4_SINT8,
		DT_UINT8,
		DT_VEC2_UINT8, DT_VEC3_UINT8, DT_VEC4_UINT8,
		DT_MAT2_UINT8, DT_MAT3_UINT8, DT_MAT4_UINT8,
		DT_SINT16,
		DT_VEC2_SINT16, DT_VEC3_SINT16, DT_VEC4_SINT16,
		DT_MAT2_SINT16, DT_MAT3_SINT16, DT_MAT4_SINT16,
		DT_UINT16,
		DT_VEC2_UINT16, DT_VEC3_UINT16, DT_VEC4_UINT16,
		DT_MAT2_UINT16, DT_MAT3_UINT16, DT_MAT4_UINT16,
		DT_SINT32,
		DT_VEC2_SINT32, DT_VEC3_SINT32, DT_VEC4_SINT32,
		DT_MAT2_SINT32, DT_MAT3_SINT32, DT_MAT4_SINT32,
		DT_UINT32,
		DT_VEC2_UINT32, DT_VEC3_UINT32, DT_VEC4_UINT32,
		DT_MAT2_UINT32, DT_MAT3_UINT32, DT_MAT4_UINT32,
		DT_FLOAT32,
		DT_VEC2_FLOAT32, DT_VEC3_FLOAT32, DT_VEC4_FLOAT32,
		DT_MAT2_FLOAT32, DT_MAT3_FLOAT32, DT_MAT4_FLOAT32,
		DT_FLOAT64,
		DT_VEC2_FLOAT64, DT_VEC3_FLOAT64, DT_VEC4_FLOAT64,
		DT_MAT2_FLOAT64, DT_MAT3_FLOAT64, DT_MAT4_FLOAT64,
		DT_SNORM,
		DT_VEC2_SNORM, DT_VEC3_SNORM, DT_VEC4_SNORM,
		DT_MAT2_SNORM, DT_MAT3_SNORM, DT_MAT4_SNORM,
		DT_UNORM,
		DT_VEC2_UNORM, DT_VEC3_UNORM, DT_VEC4_UNORM,
		DT_MAT2_UNORM, DT_MAT3_UNORM, DT_MAT4_UNORM,
		DT_USER_DATA = 99
	};
	enum pixel_formats : ui32 {
		PXF_DEFAULT = 0,
		PXF_R8_SINT8,
		PXF_R8_UINT8,
		PXF_R16_SINT16, PXF_R8G8_SINT16,
		PXF_R16_UINT16, PXF_R8G8_UINT16,
		PXF_R32_SINT32, PXF_R16G16_SINT32, PXF_R8G8B8_SINT32, PXF_R8G8B8A8_SINT32,
		PXF_R32_UINT32, PXF_R16G16_UINT32, PXF_R8G8B8_UINT32, PXF_R8G8B8A8_UINT32,
		PXF_S8_SINT8, PXF_D32_SINT32,
		PXF_S8_UINT8, PXF_D32_UINT32,
		PXF_D24S8_SINT32,
		PXF_D24S8_UINT32,
	};
}
namespace NW
{
	NW_API si32 dt_get_prim_count(data_types data_type);
	NW_API size dt_get_size(data_types data_type, si32 count = 1);
	NW_API size dt_get_aligned_size(data_types data_type, si32 count = 1);

	NW_API pixel_formats pxf_get(ui8 nchannels);
	NW_API ui8 pxf_get(pixel_formats pixel_format);
}
#endif	// NWL_DATA_SWITCH_H