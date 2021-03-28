#include "nwlib_core.hpp"
#if (defined NW_API)
namespace NWLIB
{
	// values of 8 bit boolean
	using v2b = glm::bvec2;
	using v3b = glm::bvec3;
	using v4b = glm::bvec4;
	using cv2b = const v2b;
	using cv3b = const v3b;
	using cv4b = const v4b;
	// values of 8 bit signed integer
	using v2s8 = glm::i8vec2;
	using v3s8 = glm::i8vec3;
	using v4s8 = glm::i8vec4;
	using cv2s8 = const v2s8;
	using cv3s8 = const v3s8;
	using cv4s8 = const v4s8;
	// values of 8 bit unsigned integer
	using v2u8 = glm::u8vec2;
	using v3u8 = glm::u8vec3;
	using v4u8 = glm::u8vec4;
	using cv2u8 = const v2u8;
	using cv3u8 = const v3u8;
	using cv4u8 = const v4u8;
	// values of 16 bit signed integer
	using v2s16 = glm::i16vec2;
	using v3s16 = glm::i16vec3;
	using v4s16 = glm::i16vec4;
	using cv2s16 = const v2s16;
	using cv3s16 = const v3s16;
	using cv4s16 = const v4s16;
	// values of 16 bit unsigned integer
	using v2u16 = glm::u16vec2;
	using v3u16 = glm::u16vec3;
	using v4u16 = glm::u16vec4;
	using cv2u16 = const v2u16;
	using cv3u16 = const v3u16;
	using cv4u16 = const v4u16;
	// values of 32 bit signed integer
	using v2s32 = glm::i32vec2;
	using v3s32 = glm::i32vec3;
	using v4s32 = glm::i32vec4;
	using cv2s32 = const v2s32;
	using cv3s32 = const v3s32;
	using cv4s32 = const v4s32;
	// values of 32 bit unsigned integer
	using v2u32 = glm::u32vec2;
	using v3u32 = glm::u32vec3;
	using v4u32 = glm::u32vec4;
	using cv2u32 = const v2u32;
	using cv3u32 = const v3u32;
	using cv4u32 = const v4u32;
	// values of 64 bit signed integer
	using v2s64 = glm::i64vec2;
	using v3s64 = glm::i64vec3;
	using v4s64 = glm::i64vec4;
	using cv2s64 = const v2s64;
	using cv3s64 = const v3s64;
	using cv4s64 = const v4s64;
	// values of 64 bit unsigned integer
	using v2u64 = glm::u64vec2;
	using v3u64 = glm::u64vec3;
	using v4u64 = glm::u64vec4;
	using cv2u64 = const v2u64;
	using cv3u64 = const v3u64;
	using cv4u64 = const v4u64;
	// values of 32 bit float
	using v2f32 = glm::f32vec2;
	using v3f32 = glm::f32vec3;
	using v4f32 = glm::f32vec4;
	using cv2f32 = const v2f32;
	using cv3f32 = const v3f32;
	using cv4f32 = const v4f32;
	// values of 64 bit float
	using v2f64 = glm::f64vec2;
	using v3f64 = glm::f64vec3;
	using v4f64 = glm::f64vec4;
	using cv2f64 = const v2f64;
	using cv3f64 = const v3f64;
	using cv4f64 = const v4f64;
	// values of default signed integer
	using v2s = v2s32;
	using v3s = v3s32;
	using v4s = v4s32;
	using cv2s = const v2s;
	using cv3s = const v3s;
	using cv4s = const v4s;
	// values of default unsigned integer
	using v2u = v2u32;
	using v3u = v3u32;
	using v4u = v4u32;
	using cv2u = const v2u;
	using cv3u = const v3u;
	using cv4u = const v4u;
	// values of default float
	using v2f = v2f32;
	using v3f = v3f32;
	using v4f = v4f32;
	using cv2f = const v2f32;
	using cv3f = const v3f32;
	using cv4f = const v4f32;
	// matrix n_to_n float 32 bit
	using m2f32 = glm::f32mat2;
	using m3f32 = glm::f32mat3;
	using m4f32 = glm::f32mat4;
	using cm2f32 = const m2f32;
	using cm3f32 = const m3f32;
	using cm4f32 = const m4f32;
	// matrix n_to_n float 64 bit
	using m2f64 = glm::f64mat2;
	using m3f64 = glm::f64mat3;
	using m4f64 = glm::f64mat4;
	using cm2f64 = const m2f64;
	using cm3f64 = const m3f64;
	using cm4f64 = const m4f64;
	// matrix n_to_n default float
	using m2f = m2f32;
	using m3f = m3f32;
	using m4f = m4f32;
	using cm2f = const m2f;
	using cm3f = const m3f;
	using cm4f = const m4f;
}
#endif	// NW_API