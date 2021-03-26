#include <nwl_pch.hpp>
#include "nwl_rand.h"
std::mt19937 s_rand_engine(clock());
namespace NW
{
	bit get_rand_bit() {
		return  static_cast<bit>(get_rand_sint32(0, 1));
	}
	bit get_rand_sint(v1si nmin, v1si nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1si>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	bit get_rand_uint(v1ui nmin, v1ui nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1si>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1si8 get_rand_sint8(v1si8 nmin, v1si8 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1si8>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1ui8 get_rand_uint8(v1ui8 nmin, v1ui8 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1ui8>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1si16 get_rand_sint16(v1si16 nmin, v1si16 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1si16>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1ui16 get_rand_uint16(v1ui16 nmin, v1ui16 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1ui16>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1si32 get_rand_sint32(v1si32 nmin, v1si32 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1si32>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1ui32 get_rand_uint32(v1ui32 nmin, v1ui32 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1ui32>(std::round(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	v1f32 get_rand_flt(v1f nmin, v1f nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1f>(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
	v1f32 get_rand_f32(v1f32 nmin, v1f32 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1f32>(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
	v1f64 get_rand_f64(v1f64 nmin, v1f64 nmax) {
		constexpr v1f64 nfraction = 1.0 / (static_cast<v1f64>(s_rand_engine.max()));
		return  static_cast<v1f64>(static_cast<v1f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
}