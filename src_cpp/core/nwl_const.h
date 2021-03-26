#ifndef NWL_SWITCH_H
#define NWL_SWITCH_H
#include <nwl_core.hpp>
namespace NW
{
	enum constants : v1ui {
		CST_DEFAULT = 0,
		CST_ZERO = 0,
		CST_NULL = 0,
		CST_FALSE = 0,
		CST_ONE = 1,
		CST_TRUE = 1
	};
	enum faces : v1ui {
		FACE_DEFAULT = 0,
		FACE_LEFT,
		FACE_RIGTH,
		FACE_LEFT_AND_RIGHT,
		FACE_BOT,
		FACE_TOP,
		FACE_BOT_AND_TOP,
		FACE_BACK,
		FACE_FRONT,
		FACE_BACK_AND_FRONT,
	};
	enum directions : v1ui {
		DIR_DEFAULT = 0,
		DIR_NORTH,
		DIR_SOUTH,
		DIR_EAST,
		DIR_WEST,
	};
	enum logic_opers : v1ui {
		LOGIC_DEFAULT = 0u,
		LOGIC_ALWAYS,
		LOGIC_NEVER,
		LOGIC_EQUAL,
		LOGIC_GREATER,
		LOGIC_LESSER,
		LOGIC_GEQUAL,
		LOGIC_LEQUAL,
	};
}
namespace NW
{
	/// native_types enumeration
	enum native_types : v1ui {
		NTP_DEFAULT = 0,
		NTP_BIT = 1,
		NTP_SINT8,
		NTP_UINT8,
		NTP_SINT16,
		NTP_UINT16,
		NTP_SINT32,
		NTP_UINT32,
		NTP_SINT64,
		NTP_UINT64,
		NTP_SNORM,
		NTP_UNORM,
		NTP_FLOAT32,
		NTP_FLOAT64,
		NTP_PTR,
		NTP_STRUCT,
	};
	/// pixel_formats enumeration
	enum pixel_formats : v1ui {
		PXF_DEFAULT = 0,
		PXF_R8_SINT8,
		PXF_R8_UINT8,
		PXF_R16_SINT16,
		PXF_R8G8_SINT16,
		PXF_R16_UINT16,
		PXF_R8G8_UINT16,
		PXF_R32_SINT32,
		PXF_R16G16_SINT32,
		PXF_R8G8B8_SINT32,
		PXF_R8G8B8A8_SINT32,
		PXF_R32_UINT32,
		PXF_R16G16_UINT32,
		PXF_R8G8B8_UINT32,
		PXF_R8G8B8A8_UINT32,
		PXF_S8_SINT8,
		PXF_D32_SINT32,
		PXF_S8_UINT8,
		PXF_D32_UINT32,
		PXF_D24S8_SINT32,
		PXF_D24S8_UINT32,
	};
}
namespace NW
{
	template<typename in_type, typename out_type>
	NW_API out_type convert();
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input);
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input, size count);
}
#endif	// NWL_SWITCH_H