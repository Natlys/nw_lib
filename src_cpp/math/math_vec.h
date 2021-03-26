#ifndef NWL_MATH_VECTOR_H
#define NWL_MATH_VECTOR_H
#include <nwl_core.hpp>
namespace NW
{
	using v2bit = glm::bvec2;
	using v3bit = glm::bvec3;
	using v4bit = glm::bvec4;
	using cv2bit = const v2bit;
	using cv3bit = const v3bit;
	using cv4bit = const v4bit;

	using v2si8 = glm::i8vec2;
	using v3si8 = glm::i8vec3;
	using v4si8 = glm::i8vec4;
	using cv2si8 = const v2si8;
	using cv3si8 = const v3si8;
	using cv4si8 = const v4si8;

	using v2ui8 = glm::u8vec2;
	using v3ui8 = glm::u8vec3;
	using v4ui8 = glm::u8vec4;
	using cv2ui8 = const v2ui8;
	using cv3ui8 = const v3ui8;
	using cv4ui8 = const v4ui8;
	
	using v2si16 = glm::i16vec2;
	using v3si16 = glm::i16vec3;
	using v4si16 = glm::i16vec4;
	using cv2si16 = const v2si16;
	using cv3si16 = const v3si16;
	using cv4si16 = const v4si16;

	using v2ui16 = glm::u16vec2;
	using v3ui16 = glm::u16vec3;
	using v4ui16 = glm::u16vec4;
	using cv2ui16 = const v2ui16;
	using cv3ui16 = const v3ui16;
	using cv4ui16 = const v4ui16;
	
	using v2si32 = glm::i32vec2;
	using v3si32 = glm::i32vec3;
	using v4si32 = glm::i32vec4;
	using cv2si32 = const v2si32;
	using cv3si32 = const v3si32;
	using cv4si32 = const v4si32;
	
	using v2ui32 = glm::u32vec2;
	using v3ui32 = glm::u32vec3;
	using v4ui32 = glm::u32vec4;
	using cv2ui32 = const v2ui32;
	using cv3ui32 = const v3ui32;
	using cv4ui32 = const v4ui32;
	
	using v2si64 = glm::i64vec2;
	using v3si64 = glm::i64vec3;
	using v4si64 = glm::i64vec4;
	using cv2si64 = const v2si64;
	using cv3si64 = const v3si64;
	using cv4si64 = const v4si64;
	
	using v2ui64 = glm::u64vec2;
	using v3ui64 = glm::u64vec3;
	using v4ui64 = glm::u64vec4;
	using cv2ui64 = const v2ui64;
	using cv3ui64 = const v3ui64;
	using cv4ui64 = const v4ui64;
	
	using v2f32 = glm::f32vec2;
	using v3f32 = glm::f32vec3;
	using v4f32 = glm::f32vec4;
	using cv2f32 = const v2f32;
	using cv3f32 = const v3f32;
	using cv4f32 = const v4f32;

	using v2f64 = glm::f64vec2;
	using v3f64 = glm::f64vec3;
	using v4f64 = glm::f64vec4;
	using cv2f64 = const v2f64;
	using cv3f64 = const v3f64;
	using cv4f64 = const v4f64;

	using v2si = v2si32;
	using v3si = v3si32;
	using v4si = v4si32;
	using cv2si = const v2si;
	using cv3si = const v3si;
	using cv4si = const v4si;

	using v2ui = v2ui32;
	using v3ui = v3ui32;
	using v4ui = v4ui32;
	using cv2ui = const v2ui;
	using cv3ui = const v3ui;
	using cv4ui = const v4ui;

	using v2f = v2f32;
	using v3f = v3f32;
	using v4f = v4f32;
	using cv2f = const v2f32;
	using cv3f = const v3f32;
	using cv4f = const v4f32;
}
#endif // NW_MATH_VECTOR_H