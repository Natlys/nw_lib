#ifndef NWL_RANDOM_H
#define NWL_RANDOM_H
#include <nwl_core.hpp>
#include <random>
#pragma warning(disable : 4067)
namespace NW
{
	// --getters
	extern NW_API bit get_rand_bit();
	extern NW_API bit get_rand_sint(v1si nmin = -128, v1si nmax = 127);
	extern NW_API bit get_rand_uint(v1ui nmin = 0, v1ui nmax = 255);
	extern NW_API v1si8 get_rand_sint8(v1si8 nmin = 0x00, v1si8 nmax = 0x01);
	extern NW_API v1ui8 get_rand_uint8(v1ui8 nmin = 0x00u, v1ui8 nmax = 0xffu);
	extern NW_API v1si16 get_rand_sint16(v1si16 nmin = 0x00'00, v1si16 nmax = 0x00'ff);
	extern NW_API v1ui16 get_rand_uint16(v1ui16 nmin = 0x00'00u, v1ui16 nmax = 0xff'ffu);
	extern NW_API v1si32 get_rand_sint32(v1si32 nmin = 0xff'ff'00'00, v1si32 nmax = 0x00'00'ff'ff);
	extern NW_API v1ui32 get_rand_uint32(v1ui32 nmin = 0x00'00'00'00, v1ui32 nmax = 0xff'ff'ff'ff);
	extern NW_API v1f32 get_rand_flt(v1f nmin = 0.0f, v1f nmax = 1.0f);
	extern NW_API v1f32 get_rand_f32(v1f32 nmin = 0.0f, v1f32 nmax = 1.0f);
	extern NW_API v1f64 get_rand_f64(v1f64 nmin = 0.0, v1f64 nmax = 1.0);
}

#endif	// NWL_RANDOM_H