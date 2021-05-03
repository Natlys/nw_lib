#ifndef NW_NUM_EDGE_H
#define NW_NUM_EDGE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_vec.h"
namespace NW
{
	/// dimensional_edge struct
	template<size_tc dims>
	struct NW_API d_edge_t
	{ static_assert(dims >= 2u, "we cannot work with such edge!");
	public:
		// --edges
		using edge_t = d_edge_t<dims>;
		using edge_tc = const edge_t;
		// --vectors
		using vec_t = num_vec_t<v1f, dims>;
		using vec_tc = const vec_t;
		// --verticies
		using vert_t = vec_t;
		using vert_tc = const vert_t;
	public:
		// --ctor_dtor
		constexpr inline d_edge_t() : m_beg(NW_NULL), m_end(NW_NULL) { }
		constexpr inline d_edge_t(vec_tc& beg, vec_tc& end) : d_edge_t() { m_beg = beg; m_end = end; }
		constexpr inline d_edge_t(edge_tc& copy) : d_edge_t() { m_beg = copy.m_beg; m_end = copy.m_end; }
		constexpr inline d_edge_t(edge_t&& copy) : d_edge_t() { m_beg = copy.m_beg; m_end = copy.m_end; }
		inline ~d_edge_t() = default;
		// --getters
		// // --info
		static constexpr inline size_tc get_dcount() { return dims; }
		// --operators
		// // --mathematics
		// // --asignment
		inline edge_t& operator=(edge_tc& copy) { m_beg = copy.m_beg; m_end = copy.m_end; return *this; }
		inline edge_t& operator=(edge_t&& copy) { m_beg = copy.m_beg; m_end = copy.m_end; return *this; }
		// // --convertion
		// --core_methods
	public:
		vec_t m_beg;
		vec_t m_end;
	};
	typedef d_edge_t<2u> edge2d_t;
	typedef d_edge_t<3u> edge3d_t;
}
#endif	// NW_API
#endif	// NW_NUM_EDGE_H