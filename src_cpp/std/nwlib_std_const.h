#ifndef NWLIB_STD_CONST_H
#define NWLIB_STD_CONST_H
#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	enum constants : v1u {
		CONST_DEFAULT = 0,
		CONST_ZERO = 0,
		CONST_NULL = 0,
		CONST_FALSE = 0,
		CONST_ONE = 1,
		CONST_TRUE = 1,
	};
	enum faces : v1u {
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
	enum directions : v1u {
		DIR_DEFAULT = 0,
		DIR_NORTH,
		DIR_SOUTH,
		DIR_EAST,
		DIR_WEST,
	};
	enum logic_opers : v1u {
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
namespace NWLIB
{
	template<typename in_type, typename out_type>
	NW_API out_type convert();
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input);
	template<typename in_type, typename out_type>
	NW_API out_type convert(in_type input, size count);
}
#endif	// NW_API
#endif	// NWLIB_STD_CONST_H