#ifndef NWL_ENUM_H
#define NWL_ENUM_H
#include <nwl_core.hpp>
namespace NWL
{
	enum constants : ui32 {
		C_DEFAULT = 0,
		C_ZERO = 0, C_NULL = 0, C_FALSE = 0,
		C_ONE = 1, C_TRUE = 1
	};
	enum faces : ui32 {
		FACE_DEFAULT = 0,
		FACE_FRONT_AND_BACK = 1,
		FACE_BACK, FACE_FRONT, FACE_LEFT, FACE_RIGTH,
	};
	enum directions : ui32 {
		DIR_DEFAULT = 0,
		DIR_NORTH = 1, DIR_SOUTH = 2,
		DIR_EAST = 3, DIR_WEST = 4,
	};
	enum error_codes : ui32 {
		ERC_DEFAULT = 0,
		ERC_NO_INIT = 1, ERC_NO_QUIT = 2,
		ERC_NO_SUPPORT, ERC_NO_STATE,
		ERC_NO_LOAD, ERC_NO_SAVE,
		ERC_DATA_BAD, ERC_DATA_LOSS, ERC_DATA_OVERFLOW, ERC_DATA_UNDERFLOW,
		ERC_UNKNOWN_ID, ERC_UNKNOWN_NAME,
		ERC_INVALID_FORMAT, ERC_INVALID_SYNTAX, ERC_INVALID_TYPE, ERC_INVALID_ENUM,
		ERC_COMPILLATION, ERC_LINKAGE
	};
	enum logic_opers : ui32 {
		LO_DEFAULT = 0u,
		LO_EQUAL = 1, LO_GREATER = 2, LO_LESSER = 2,
		LO_GEQUAL, LO_LEQUAL,
	};
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
		PXF_DEFAULT = C_DEFAULT,
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
namespace NWL
{
	NWL_API pixel_formats pxf_get(ui8 nchannels);
	NWL_API ui8 pxf_get(pixel_formats pixel_format);
}
#endif	// NWL_SWITCH_H