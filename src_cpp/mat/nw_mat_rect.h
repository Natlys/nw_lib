#ifndef NW_MAT_RECTANGLE_H
#define NW_MAT_RECTANGLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_rectangle struct
	template<typename tval>
	struct t_rect
	{
	public:
		using rect_t = t_rect<tval>;
		using rect_tc = const rect_t;
		using val_t = tval;
		using val_tc = const tval;
		using vec_t = t_vec<tval, 2u>;
		using vec_tc = const vec_t;
	public:
		constexpr inline t_rect() : m_center(static_cast<val_t>(NW_NULL)), m_halfsz(static_cast<val_t>(NW_NULL)) { }
		constexpr inline t_rect(vec_tc& center, vec_tc& halfsz) : t_rect() { memcpy(&m_center, &center, sizeof(vec_t)); memcpy(&m_halfsz, &halfsz, sizeof(vec_t)); }
		constexpr inline t_rect(rect_tc& copy) : t_rect() { memcpy(&m_center, &copy.m_center, sizeof(vec_t)); memcpy(&m_halfsz, &copy.m_halfsz, sizeof(vec_t)); }
		constexpr inline t_rect(rect_t&& copy) : t_rect() { memmove(&m_center, &copy.m_center, sizeof(vec_t)); memmove(&m_halfsz, &copy.m_halfsz, sizeof(vec_t)); }
		inline ~t_rect() = default;
		// --getters
		inline val_tc get_dist_x(rect_tc& rect) const  { return make_dist_x(*this, rect); }
		inline val_tc get_dist_y(rect_tc& rect) const  { return make_dist_y(*this, rect); }
		inline val_tc get_dist_xy(rect_tc& rect) const { return make_dist_xy(*this, rect); }
		// --setters
		// --predicates
		inline v1bit is_over(rect_tc& rect) const { return is_over(*this, rect); }
		static constexpr inline v1bit is_over(rect_tc& rect0, rect_tc& rect1) {
			if (make_dist_x(rect0, rect1) > make_half_x(rect0, rect1)) { return NW_FALSE; }
			if (make_dist_y(rect0, rect1) > make_half_y(rect0, rect1)) { return NW_FALSE; }
			return NW_TRUE;
		}
		// --operators
		// --core_methods
		static constexpr inline val_tc make_half_x(rect_tc& rect0, rect_tc& rect1)  { return rect0.m_halfsz[0] + rect0.m_halfsz[0]; }
		static constexpr inline val_tc make_half_y(rect_tc& rect0, rect_tc& rect1)  { return rect0.m_halfsz[1] + rect0.m_halfsz[1]; }
		static constexpr inline val_tc make_half_xy(rect_tc& rect0, rect_tc& rect1) { return vec_t::make_dst(rect0.m_halfsz, rect1.m_halfsz); }
		static constexpr inline val_tc make_dist_x(rect_tc& rect0, rect_tc& rect1)  { return NW_MATH_ABS(rect0.m_center[0] - rect1.m_center[0]); }
		static constexpr inline val_tc make_dist_y(rect_tc& rect0, rect_tc& rect1)  { return NW_MATH_ABS(rect0.m_center[1] - rect1.m_center[1]); }
		static constexpr inline val_tc make_dist_xy(rect_tc& rect0, rect_tc& rect1) { return vec_t::make_dst(rect0.m_center, rect1.m_center); }
	public:
		vec_t m_center;
		vec_t m_halfsz;
	};
}
#endif	// NW_API
#endif	// NW_MAT_RECTANGLE_H