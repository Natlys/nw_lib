#ifndef NW_MAT_CIRCLE_H
#define NW_MAT_CIRCLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_circ struct
	template<typename tval>
	struct t_circ
	{
	public:
		using circ_t = t_circ<tval>;
		using circ_tc = const circ_t;
		using val_t = tval;
		using val_tc = const tval;
		using vec_t = t_vec<tval, 2u>;
		using vec_tc = const vec_t;
	public:
		constexpr inline t_circ() : m_center(static_cast<val_t>(NW_NULL)), m_radius(static_cast<val_t>(NW_NULL)) { }
		constexpr inline t_circ(vec_tc& center, vec_tc& radius) : t_circ() { memcpy(&m_center, &center, sizeof(vec_t)); memcpy(&m_radius, &radius, sizeof(vec_t)); }
		constexpr inline t_circ(circ_t& copy) : t_circ() { memcpy(&m_center, &copy.m_center, sizeof(vec_t)); memcpy(&m_radius, &copy.m_radius, sizeof(vec_t)); }
		constexpr inline t_circ(circ_tc&& copy) : t_circ() { memmove(&m_center, &copy.m_center, sizeof(vec_t)); memmove(&m_radius, &copy.m_radius, sizeof(vec_t)); }
		inline ~t_circ() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
		// --core_methods
	public:
		vec_t m_center;
		vec_t m_radius;
	};
}
#endif	// NW_API
#endif	// NW_MAT_CIRCLE_H