#ifndef NW_MAT_BOX_H
#define NW_MAT_BOX_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_box struct
	template<typename tval>
	struct t_box
	{
	public:
		using box_t = t_box<tval>;
		using box_tc = const box_t;
		using val_t = tval;
		using val_tc = const tval;
		using vec_t = t_vec<tval, 2u>;
		using vec_tc = const vec_t;
	public:
		constexpr inline t_box() : m_center(static_cast<val_t>(NW_NULL)), m_halfsz(static_cast<val_t>(NW_NULL)) { }
		constexpr inline t_box(vec_tc& center, vec_tc& halfsz) : t_box() { memcpy(&m_center, &center, sizeof(vec_t)); memcpy(&m_halfsz, &halfsz, sizeof(vec_t)); }
		constexpr inline t_box(box_tc& copy) : t_box() { memcpy(&m_center, &copy.m_center, sizeof(vec_t)); memcpy(&m_halfsz, &copy.m_halfsz, sizeof(vec_t)); }
		constexpr inline t_box(box_t&& copy) : t_box() { memmove(&m_center, &copy.m_center, sizeof(vec_t)); memmove(&m_halfsz, &copy.m_halfsz, sizeof(vec_t)); }
		inline ~t_box() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
		// --core_methods
	public:
		vec_t m_center;
		vec_t m_halfsz;
	};
}
#endif	// NW_API
#endif	// NW_MAT_BOX_H