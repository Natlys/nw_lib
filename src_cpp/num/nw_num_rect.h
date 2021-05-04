#ifndef NW_NUM_RECTANGLE_H
#define NW_NUM_RECTANGLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_vec.h"
#	include "nw_num_edge.h"
#	pragma warning(disable:4774)
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
#		endif	// ctor_dtor
		// --getters
#		if (NW_TRUE)
		static constexpr inline size_tc get_dcount() { return dims; }
		static constexpr inline size_tc get_dcount(size_tc dcount) { return NW_NUM_POW(2u, dcount - dims) * NW_NUM_COMBIN(dcount, dims, NW_FALSE); }
		static constexpr inline size_tc get_vcount() { return NW_CAST_SIZE(1u) << NW_CAST_SIZE(get_dcount()); }
		static constexpr inline size_tc get_ecount() { return NW_CAST_SIZE( NW_CAST_FLOAT(get_vcount() * get_count()) * 0.5f ); }
		static constexpr inline size_tc get_fcount() { return get_dcount(3u); }
		inline cv1f get_half(size_tc dim) const { return m_halfsz[dim] * 1.0f; }
		inline cv1f get_size(size_tc dim) const { return m_halfsz[dim] * 2.0f; }
		inline cv1f get_dst(rect_tc& rect) const { return make_dst(*this, rect); }
		inline cv1f get_dst(rect_tc& rect, size_tc dim) const { return make_dst(*this, rect, dim); }
		inline vert_tc get_vert(size_tc vindex) const   { return make_vert(*this, vindex); }
		inline vdata_tc get_vdata(size_tc vindex) const { return make_vdata(*this, vindex); }
		inline idata_tc get_idata_vert(size_tc vindex) const { return make_idata_vert(vindex); }
		inline idata_tc get_idata_wire(size_tc vindex) const { return make_idata_wire(vindex); }
		inline idata_tc get_idata_trig(size_tc vindex) const { return make_idata_trig(vindex); }
		inline idata_tc get_idata_gizm_wire(size_tc vindex) const { return make_idata_gizm_wire(vindex); }
		inline idata_tc get_idata_gizm_trig(size_tc vindex) const { return make_idata_gizm_trig(vindex); }
		inline idata_tc get_idata_gizm_face(size_tc vindex) const { return make_idata_gizm_face(vindex); }
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
		static constexpr inline vert_tc make_vert(rect_tc& rect, size_tc vindex) { // make a vertex coordinate accordingly to it's index
			vert_t res(NW_NULL);
			NW_CHECK(vindex < get_vcount(), "index error!", return res);
			for (v1u idim(0u), ivtx(~vindex % get_vcount()); idim < get_dcount(); idim++, ivtx /= 2) {
				res[idim] = rect.m_center[idim] + (ivtx % 2 ? +rect.m_halfsz[idim] : -rect.m_halfsz[idim]);
			}
			return res;
		}
		static constexpr inline vdata_tc make_vdata(rect_tc& rect, size_tc vindex) { // make a list of all vertex coordinates
			vdata_t res(get_vcount() - vindex);
			for (v1u ivert(vindex); ivert < res.size(); ivert++) { res[ivert] = make_vert(rect, ivert); }
			return res;
		}
		static constexpr inline idata_tc make_idata_vert(size_tc vindex) { // make an indexed list of points
			idata_t res(get_vcount() - vindex);
			NW_CHECK(vindex < get_vcount(), "index error!", return res);
			for (v1u ivert(vindex); ivert < res.size(); ivert += 1u) { res[ivert] = ivert; }
			return res;
		}
		static constexpr inline idata_tc make_idata_wire(size_tc vindex) { // make an indexed list of lines
			NW_CHECK(vindex < get_vcount(), "index error!", return idata_t());
			idata_t res((get_vcount() - vindex) * (get_dcount() * 2u), 0u); // vertex "dcount" nodes; node = 1 edge; edge = 2 indices;
			for (v1u ivert(vindex), last(0u); ivert < get_vcount(); ivert += 1u) { // vertex = "dcount" nodes;
				for (v1u idim(0u), dgt(0u); idim < get_dcount(); idim += 1u, last += 2u) { // node = minuses and pluses;
					// add the vertex index every time;
					res[last + 0u] = ivert + 0u;
					// take every digit (idim-th from left) to define whether we add or substract one bit;
					dgt = ((get_vcount() + ivert) >> (idim)) % 2;
					res[last + 1u] = static_cast<v1s>(ivert) + (dgt == 0u ? +static_cast<v1s>(1u << idim) : -static_cast<v1s>(1u << idim) );
				}
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_trig(size_tc vindex) { // make an indexed list of triangles
			NW_CHECK(vindex < get_vcount(), "index error!", return idata_t());
			idata_t res((get_vcount() - vindex) * get_dcount() * ((get_dcount() - 1u) * 3u)); // vertex = "dcount" nodes; node = "dcount - 1" trigs; trig = 3 indicies;
			for (v1u ivert(vindex), last(0u); ivert < get_vcount(); ivert += 1u) { // vertex = "dcount" nodes;
				for (v1u idim(0u); idim < get_dcount(); idim += 1u) { // vertex -> "dcount" nodes;
					for (v1u inode(1u), dgt0(0u), dgt1(0u); inode < get_dcount(); inode += 1u, last += 3u) { // node -> "dcount - 1" trigs;
						res[last + 0u] = (ivert) % get_vcount();
						// take every digit (idim-th from left) to define whether we add or substract idim-th bit;
						dgt0 = ((get_vcount() + ivert) >> (idim)) % 2;
						res[last + 1u] = (static_cast<v1s>(ivert) + ( dgt0 == 0u ? +static_cast<v1s>(1u << idim) : -static_cast<v1s>(1u << idim) ) ) % get_vcount();
						// take every digit ((idim + ivert)-th from left) to define whether we add or substract (idim + ivert)-th bit;
						dgt1 = ((get_vcount() + ivert) >> (idim + inode)) % 2;
						res[last + 2u] = ( static_cast<v1s>(ivert) + ( dgt1 == 0u ? +static_cast<v1s>(1u << (idim + inode)) : -static_cast<v1s>(1u << (idim + inode)) ) ) % get_vcount();
					}
				}
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_gizm_wire(size_tc vindex) { // make an indexed list of gizmo wireframe;
			NW_CHECK(vindex < get_vcount(), "index error!", return idata_t());
			idata_t res(get_dcount() * 2u, 0u); // vertex = "dcount" edges; edge = 2 indicies;
			for (v1u idim(0u), dgt(0u), last(0u); idim < get_dcount(); idim += 1u, last += 2u) {
				res[last + 0u] = ( vindex ) % get_vcount();
				// take every digit (idim-th from left) to define whether we add or substract one bit;
				dgt = ((get_vcount() + vindex) >> (idim)) % 2;
				res[last + 1u] = ( static_cast<v1s>(vindex) + (dgt == 0u ?
					+static_cast<v1s>(1u << idim) :
					-static_cast<v1s>(1u << idim)
					) ) % get_vcount();
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_gizm_trig(size_tc vindex) { // make an indexed list of gizmo triangles;
			NW_CHECK(vindex < get_vcount(), "index error!", return idata_t());
			idata_t res(get_dcount() * (get_dcount() - 1u) * 3u, 0u); // vertex = "dcount" nodes; node = "dcount - 1" trigs; trig = 3 indices;
			for (v1u idim(0u), last(0u); idim < get_dcount(); idim += 1u) { // vertex -> "dcount" nodes;
				for (v1u inode(1u), dgt0(0u), dgt1(0u); inode < get_dcount(); inode += 1u, last += 3u) { // node -> "dcount - 1" trigs;
					res[last + 0u] = ( vindex ) % get_vcount();
					// take every digit (idim-th from left) to define whether we add or substract idim-th bit;
					dgt0 = ((get_vcount() + vindex) >> (idim)) % 2;
					res[last + 1u] = ( static_cast<v1s>(vindex) + ( dgt0 == 0u ?
						+static_cast<v1s>(1u << idim) :
						-static_cast<v1s>(1u << idim)
						) ) % get_vcount();
					// take every digit ((idim + ivert)-th from left) to define whether we add or substract (idim + ivert)-th bit;
					dgt1 = ((get_vcount() + vindex) >> (idim + inode)) % 2;
					res[last + 2u] = ( static_cast<v1s>(vindex) + ( dgt1 == 0u ?
						+static_cast<v1s>(1u << (idim + inode)) :
						-static_cast<v1s>(1u << (idim + inode))
						) ) % get_vcount();
				}
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_gizm_face(size_tc vindex) { // make an indexed list of gizmo faces;
			NW_CHECK(vindex < get_vcount(), "index error!", return idata_t());
			idata_t res(get_dcount() * (get_dcount() - 1u) * 3u * 2u, 0u); // vertex = "dcount" node; node = "dcount - 1" faces; face = 2 trigs; trig = 3 indicies;
			for (v1u idim(0u), last(0u); idim < get_dcount(); idim += 1u) { // vertex -> "dcount" nodes;
				for (v1u inode(1u), dgt0(0u), dgt1(0u); inode < get_dcount(); inode += 1u, last += 6u) { // node -> "dcount - 1" faces;
					res[last + 0u] = (vindex) % get_vcount();
					// take every digit (idim-th from left) to define whether we add or substract idim-th bit;
					dgt0 = ((get_vcount() + vindex) >> (idim)) % 2;
					res[last + 1u] = ( static_cast<v1s>(vindex) + ( dgt0 == 0u ?
						+static_cast<v1s>(1u << idim) :
						-static_cast<v1s>(1u << idim)
						) ) % get_vcount();
					// take every digit ((idim + ivert)-th from left) to define whether we add or substract (idim + ivert)-th bit;
					dgt1 = ((get_vcount() + vindex) >> (idim + inode)) % 2;
					res[last + 2u] = ( static_cast<v1s>(vindex) + ( dgt1 == 0u ?
						+static_cast<v1s>(1u << (idim + inode)) :
						-static_cast<v1s>(1u << (idim + inode))
						) ) % get_vcount();
					// add complementary triangle;
					res[last + 3u] = res[last + 2u];
					res[last + 4u] = res[last + 1u];
					res[last + 5u] = ( static_cast<v1s>(vindex)
						+ ( dgt0 == 0u ?
							+static_cast<v1s>(1u << idim) :
							-static_cast<v1s>(1u << idim) )
						+ ( dgt1 == 0u ?
							+static_cast<v1s>(1u << (idim + inode)) :
							-static_cast<v1s>(1u << (idim + inode)) )
						) % get_vcount();
				}
			}
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