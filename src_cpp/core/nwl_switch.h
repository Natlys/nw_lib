#ifndef NWL_SWITCH_H
#define NWL_SWITCH_H
#include <nwl_core.hpp>
namespace NW
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
	enum logic_opers : ui32 {
		LO_DEFAULT = 0u,
		LO_EQUAL = 1, LO_GREATER = 2, LO_LESSER = 2,
		LO_GEQUAL, LO_LEQUAL,
	};
}
namespace NW
{
	template<typename in_type, typename out_type>
	NW_API out_type convert_enum();
	template<typename in_type, typename out_type>
	NW_API out_type convert_enum(in_type input);
}
#endif	// NWL_SWITCH_H