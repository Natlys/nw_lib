#include <nwl_pch.hpp>
#include "nwl_const.h"
#include <math/math_vec.h>
#include <math/math_mat.h>
#include <io/io_err.h>
namespace NW
{
	template<> native_types convert<v1si8, native_types>() { return NTP_SINT8; }
	template<> native_types convert<v2si8, native_types>() { return NTP_SINT8; }
	template<> native_types convert<v3si8, native_types>() { return NTP_SINT8; }
	template<> native_types convert<v4si8, native_types>() { return NTP_SINT8; }

	template<> native_types convert<v1ui8, native_types>() { return NTP_UINT8; }
	template<> native_types convert<v2ui8, native_types>() { return NTP_UINT8; }
	template<> native_types convert<v3ui8, native_types>() { return NTP_UINT8; }
	template<> native_types convert<v4ui8, native_types>() { return NTP_UINT8; }

	template<> native_types convert<v1si16, native_types>() { return NTP_SINT16; }
	template<> native_types convert<v2si16, native_types>() { return NTP_SINT16; }
	template<> native_types convert<v3si16, native_types>() { return NTP_SINT16; }
	template<> native_types convert<v4si16, native_types>() { return NTP_SINT16; }

	template<> native_types convert<v1ui16, native_types>() { return NTP_UINT16; }
	template<> native_types convert<v2ui16, native_types>() { return NTP_UINT16; }
	template<> native_types convert<v3ui16, native_types>() { return NTP_UINT16; }
	template<> native_types convert<v4ui16, native_types>() { return NTP_UINT16; }

	template<> native_types convert<v1si32, native_types>() { return NTP_SINT32; }
	template<> native_types convert<v2si32, native_types>() { return NTP_SINT16; }
	template<> native_types convert<v3si32, native_types>() { return NTP_SINT16; }
	template<> native_types convert<v4si32, native_types>() { return NTP_SINT16; }

	template<> native_types convert<v1ui32, native_types>() { return NTP_UINT32; }
	template<> native_types convert<v2ui32, native_types>() { return NTP_UINT32; }
	template<> native_types convert<v3ui32, native_types>() { return NTP_UINT32; }
	template<> native_types convert<v4ui32, native_types>() { return NTP_UINT32; }

	template<> native_types convert<v1si64, native_types>() { return NTP_SINT64; }
	template<> native_types convert<v2si64, native_types>() { return NTP_SINT64; }
	template<> native_types convert<v3si64, native_types>() { return NTP_SINT64; }
	template<> native_types convert<v4si64, native_types>() { return NTP_SINT64; }

	template<> native_types convert<v1ui64, native_types>() { return NTP_UINT64; }
	template<> native_types convert<v2ui64, native_types>() { return NTP_UINT64; }
	template<> native_types convert<v3ui64, native_types>() { return NTP_UINT64; }
	template<> native_types convert<v4ui64, native_types>() { return NTP_UINT64; }

	template<> native_types convert<v1f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<v2f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<v3f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<v4f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<m2f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<m3f32, native_types>() { return NTP_FLOAT32; }
	template<> native_types convert<m4f32, native_types>() { return NTP_FLOAT32; }

	template<> native_types convert<v1f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<v2f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<v3f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<v4f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<m2f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<m3f64, native_types>() { return NTP_FLOAT64; }
	template<> native_types convert<m4f64, native_types>() { return NTP_FLOAT64; }

	template<> native_types convert<void, native_types>() { return NTP_STRUCT; }
	template<> native_types convert<void*, native_types>(){ return NTP_STRUCT; }

	template<> size convert<native_types, size>(native_types type) {
		switch (type) {
		case NTP_BIT: return 1;
		case NTP_SINT8: return 1;
		case NTP_UINT8: return 1;
		case NTP_SINT16: return 2;
		case NTP_UINT16: return 2;
		case NTP_SINT32: return 4;
		case NTP_UINT32: return 4;
		case NTP_SINT64: return 8;
		case NTP_UINT64: return 8;
		case NTP_SNORM: return 4;
		case NTP_UNORM: return 4;
		case NTP_FLOAT32: return 4;
		case NTP_FLOAT64: return 8;
		case NTP_STRUCT: return 1;
		default: throw run_error(__FILE__, __LINE__);
		}
		return 0u;
	}
	template<>
	size convert(native_types input, size count) { return convert<native_types, size>(input) * count; }
}