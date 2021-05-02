#ifndef NW_NUM_RECTANGLE_H
#define NW_NUM_RECTANGLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_vec.h"
#	include "nw_num_edge.h"
namespace NW
{
	/// dimensional_rectangle struct
	template<size_tc dims>
	struct d_rect_t
	{ static_assert(dims >= 2u, "we cannot work with such rectangle!");
	public:
		// --rectangle
		using rect_t = d_rect_t<dims>;
		using rect_tc = const rect_t;
		// --vectors
		using vec_t = num_vec_t<v1f, dims>;
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		// --verticies
		using vert_t = vec_t;
		using vert_tc = const vert_t;
		using vdata_t = std::vector<vec_t>;
		using vdata_tc = const vdata_t;
		// --edges
		using edge_t = d_edge_t<dims>;
		using edge_tc = const edge_t;
		using edata_t = std::vector<edge_t>;
		using edata_tc = const edata_t;
		// --indices
		using idata_t = std::vector<v1u>;
		using idata_tc = const idata_t;
	public:
		// --ctor_dtor
#		if (NW_TRUE)
		constexpr inline d_rect_t() : m_center(NW_NULL), m_halfsz(NW_NULL) { }
		constexpr inline d_rect_t(vec_tc& center, cv1f halfsz) : d_rect_t() { m_center = center; m_halfsz = halfsz; }
		constexpr inline d_rect_t(vec_tc& center, vec_tc& halfsz) : d_rect_t() { m_center = center; m_halfsz = halfsz; }
		constexpr inline d_rect_t(rect_tc& copy) : d_rect_t() { m_center = copy.m_center; m_halfsz = copy.m_halfsz; }
		constexpr inline d_rect_t(rect_t&& copy) : d_rect_t() { m_center = copy.m_center; m_halfsz = copy.m_halfsz; }
		inline ~d_rect_t() = default;
#		endif	// constructor_destructor
		// --getters
#		if (NW_TRUE)
		static constexpr inline size_tc get_count() { return dims; }
		static constexpr inline size_tc get_vcount() { return 1ul << get_count(); }
		static constexpr inline size_tc get_ecount() { return NW_CAST_SIZE( NW_CAST_FLOAT(get_vcount() * get_count()) * 0.5f ); }
		static constexpr inline size_tc get_fcount() { return get_vcount() * 1u; }
		static constexpr inline size_tc get_count(size_tc dcount) { return NW_NUM_POW(2u, dcount - dims) * NW_NUM_COMBIN(dcount, dims, NW_FALSE); }
		inline cv1f get_half(size_tc dim) const { return m_halfsz[dim] * 1u; }
		inline cv1f get_size(size_tc dim) const { return m_halfsz[dim] * 2u; }
		inline cv1f get_dst(rect_tc& rect) const { return make_dst(*this, rect); }
		inline cv1f get_dst(rect_tc& rect, size_tc dim) const { return make_dst(*this, rect, dim); }
		inline vert_tc get_vert(size_t vindex) const { return make_vert(*this, vindex); }
		inline vdata_tc get_vdata() const            { return make_vdata(*this); }
		inline edge_tc get_edge(size_t eindex) const { return make_edge(*this, eindex); }
		inline edata_tc get_edata() const            { return make_edata(*this); }
		inline idata_tc get_idata_vert() const { return make_idata_vert(); }
		inline idata_tc get_idata_wire() const { return make_idata_wire(); }
		inline idata_tc get_idata_trig() const { return make_idata_trig(); }
#		endif	// getters
		// --setters
#		if (NW_TRUE)
#		endif	// setters
		// --predicates
#		if (NW_TRUE)
		inline v1bit is_colid_aabb(rect_tc& rect) const { return is_colid_aabb(*this, rect); }
		static constexpr inline v1bit is_colid_aabb(rect_tc& rect0, rect_tc& rect1) {
			for (v1u idim(0u); idim < get_count(); idim++) { if (make_dst(rect0, rect1, idim) > NW_NULL) { return NW_FALSE; } }
			return NW_TRUE;
		}
#		endif	// predicates
		// --operators
#		if (NW_TRUE)
		inline d_rect_t& operator=(rect_tc& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; }
		inline d_rect_t& operator=(rect_t&& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; }
#		endif	// operators
		// --core_methods
#		if (NW_TRUE)
		static constexpr inline vert_tc make_vert(rect_tc& rect, size_t vindex) { // make a vertex coordinate accordingly to it's index
			vert_t res;
			vindex = ~vindex;
			for (v1u idim(0u); idim < get_count(); idim++) {
				res[idim] = rect.m_center[idim] + (vindex % 2 ? +rect.m_halfsz[idim] : -rect.m_halfsz[idim]);
				vindex /= 2u;
			}
			return res;
		}
		static constexpr inline vdata_tc make_vdata(rect_tc& rect) { // make a list of all vertex coordinates
			vdata_t res(get_vcount());
			for (v1u ivert(0u); ivert < res.size(); ivert++) { res[ivert] = make_vert(rect, ivert); }
			return res;
		}
		static constexpr inline edge_tc make_edge(rect_tc& rect, size_t eindex) { // make an edge coordinate accordingly to it's index
			edge_t res;
			res.m_beg = make_vert(rect, (eindex + (eindex + 0) % get_count()));
			res.m_end = make_vert(rect, (eindex + (eindex + 1 ) % get_count()));
			return res;
		}
		static constexpr inline edata_tc make_edata(rect_tc& rect) { // make a list of all edge coordinates
			edata_t res(get_ecount());
			for (v1u iedge(0u); iedge < res.size(); iedge++) { res[iedge] = make_edge(rect, iedge); }
			return res;
		}
		static constexpr inline idata_tc make_idata_vert() { // make an indexed list of points
			idata_t res(get_vcount());
			for (v1u idx(0u); idx < res.size(); idx += 1u) { res[idx] = idx; }
			return res;
		}
		static constexpr inline idata_tc make_idata_wire() { // make an indexed list of lines
			idata_t res; res.reserve(get_vcount() + get_ecount());
			v1u last(0u), inum(0u);
			for ( v1u idim(0u); idim < get_count(); inum = (1 << (idim += 1u)) ) {
				for ( v1u istep(1u << dims >> 1u); istep > (idim << 1u); istep >>= 1u ) {
					res.push_back(inum);
					res.push_back(inum + istep);
					res.push_back(get_vcount() - 1u - inum);
					res.push_back(get_vcount() - 1u - inum - istep);
				}
				for ( v1u istep(1u); istep < (idim << 1u); istep <<= 1u ) {
					res.push_back(inum);
					res.push_back(inum + istep);
					res.push_back(get_vcount() - 1u - inum);
					res.push_back(get_vcount() - 1u - inum - istep);
				}
				inum = 1u << idim;
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_trig() { // make an indexed list of triangles
			idata_t res(get_fcount());
			for (v1u idx(0u); idx < res.size(); idx += 3u) { res[idx] = idx; }
			return res;
		}
		static constexpr inline cv1f make_dst(rect_tc& rect0, rect_tc& rect1) { // make the distance between two rectangles using a vector;
			return vec_t::make_dst(rect0.m_center, rect1.m_center) - vec_t::make_len(rect0.m_halfsz + rect1.m_halfsz);
		}
		static constexpr cv1f make_dst(rect_tc& rect0, rect_tc& rect1, size_tc dim) {  // make the distance between two rectangles using one dimension;
			return NW_NUM_ABS(rect1.m_center[dim] - rect0.m_center[dim]) - NW_NUM_ABS(rect1.m_halfsz[dim] + rect0.m_halfsz[dim]);
		}
#		endif	// core_methods
	public:
		vec_t m_center;
		vec_t m_halfsz;
	};
	template<size_tc dims> using d_rect_tc = const d_rect_t<dims>;
	typedef d_rect_t<2u> rect2d_t;
	typedef d_rect_t<3u> rect3d_t;
	typedef d_rect_t<4u> rect4d_t;
}
#endif	// NW_API
#endif	// NW_NUM_RECTANGLE_H