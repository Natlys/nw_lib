#ifndef NW_NUM_CIRCLE_H
#define NW_NUM_CIRCLE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_vec.h"
#	include "nw_num_edge.h"
namespace NW
{
	/// dimensional_circle struct
	template<size_tc dims>
	struct d_circ_t
	{ static_assert(dims >= 2u, "we cannot work with such circle!");
	public:
		// --circle
		using circ_t = d_circ_t<dims>;
		using circ_tc = const circ_t;
		template<size_tc circ_dims> using d_circ_tc = const d_circ_t<circ_dims>;
		// --vectors
		using vec_t = num_vec_t<v1f, dims>; 
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		// --vertices
		using vert_t = vec_t;
		using vert_tc = const vert_t;
		using vdata_t = std::vector<vert_t>;
		using vdata_tc = const vdata_t;
		// --edges
		using edge_t = d_edge_t<dims>;
		using edge_tc = const edge_t;
		using edata_t = std::vector<edge_t>;
		using edata_tc = const edata_t;
		// --faces
		// --indices
		using idata_t = std::vector<v1u>;
		using idata_tc = const idata_t;
	public:
		// --ctor_dtor
#	if (NW_TRUE)
		constexpr inline d_circ_t() : m_center(NW_NULL), m_halfsz(NW_NULL) { }
		constexpr inline d_circ_t(vec_tc& center, cv1f halfsz) : d_circ_t() { m_center = center; m_halfsz = halfsz; }
		constexpr inline d_circ_t(vec_tc& center, vec_tc& halfsz) : d_circ_t() { m_center = center; m_halfsz = halfsz; }
		constexpr inline d_circ_t(circ_tc& copy) : d_circ_t() { operator=(copy); }
		constexpr inline d_circ_t(circ_t&& copy) : d_circ_t() { operator=(copy); }
		template<size_tc circ_dims> constexpr inline d_circ_t(d_circ_tc<circ_dims>& copy) : d_circ_t() { operator=(copy); }
		template<size_tc circ_dims> constexpr inline d_circ_t(d_circ_t<circ_dims>&& copy) : d_circ_t() { operator=(copy); }
		inline ~d_circ_t() = default;
#	endif	// ctor_dtor
		// --getters
#	if (NW_TRUE)
		static constexpr inline size_tc get_dcount() { return dims; }
		static constexpr inline size_tc get_vcount(size_tc vcount) { return NW_NUM_ROOT(NW_CAST_FLOAT(vcount), NW_CAST_FLOAT(dims - 1u)); }
		inline vert_tc get_vert(size_tc vcount, size_tc vindex) const { return make_vert(*this, vcount, vindex); }
		inline vdata_tc get_vdata(size_tc vcount, size_tc vindex) const { return make_vdata(*this, vcount, vindex); }
		inline idata_tc get_idata_vert(size_tc vcount, size_tc vindex) { return make_idata_vert(vcount, vindex); }
		inline idata_tc get_idata_wire(size_tc vcount, size_tc vindex) { return make_idata_wire(vcount, vindex); }
		inline idata_tc get_idata_trig(size_tc vcount, size_tc vindex) { return make_idata_trig(vcount, vindex); }
		inline idata_tc get_idata_gizm_wire(size_tc vcount, size_tc vindex) { return make_idata_gizm_wire(vcount, vindex); }
		inline cv1f get_dst(circ_tc& circ) const { return make_dst(*this, circ); }
		inline cv1f get_dst(circ_tc& circ, size_tc dim) const { return make_dst(*this, circ, dim); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
#	endif	// setters
		// --predicates
#	if (NW_TRUE)
		inline v1bit is_colid(circ_tc& circ) const { return is_colid(*this, circ); }
		static constexpr inline v1bit is_colid(circ_tc& circ0, circ_tc& circ1) {
		 for (v1u idim(0u); idim < get_count(); idim++) { if (make_dst(circ0, circ1) > NW_NULL) { return NW_FALSE; } }
			return NW_TRUE;
		}
#	endif	// predicates
		// --operators
		// // --assignment
#	if (NW_TRUE)
#		if (NW_TRUE)
		inline circ_t& operator=(circ_tc& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; return *this; }
		inline circ_t& operator=(circ_t&& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; return *this; }
		template<size_tc circ_dims> circ_t& operator=(d_circ_tc<circ_dims>& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; return *this; }
		template<size_tc circ_dims> circ_t& operator=(d_circ_t<circ_dims>&& copy) { m_center = copy.m_center; m_halfsz = copy.m_halfsz; return *this; }
#		endif	// assignment
		// // --convertion
#		if (NW_TRUE)
		template<size_tc circ_dims> operator d_circ_tc<circ_dims>() { return d_circ_t(*this); }
#		endif	// assignment
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		static constexpr inline vert_tc make_vert(circ_tc& circ, size_tc vcount, size_tc vindex) {
			NW_CHECK(vindex < vcount, "index error!", return vert_t());
			if constexpr (get_dcount() == 2u) {
				vert_t res(NW_NULL);
				res[0] = NW_NUM_COS((360.0f / NW_CAST_FLOAT(vcount)) * NW_CAST_FLOAT(vindex));
				res[1] = NW_NUM_SIN((360.0f / NW_CAST_FLOAT(vcount)) * NW_CAST_FLOAT(vindex));
				return circ.m_center + (circ.m_halfsz * res.get_norm());
			}
			if constexpr (get_dcount() >= 3u) {
				vert_t res(1.0f); size_tc dvcount(get_vcount(vcount));
				num_vec_t<v1f, get_dcount() - 1u> angles(360.0f / dvcount);
				angles[0] *= NW_CAST_FLOAT(vindex % dvcount);
				for (v1u idim(1u); idim < get_dcount() - 1u; idim += 1u) {
					// angle in every dimension must be the step multiplied by index accordingly to a particular dimension;
					// we also need to divide it by the number of dimentions - current dimention - 1;
					// (because we don't need to draw the same circle on the second side);
					angles[idim] *= NW_CAST_FLOAT(vindex / NW_NUM_POW(dvcount, idim));
					angles[idim] /= NW_CAST_FLOAT(get_dcount() - idim - 1u);
				}
				for (v1u idim(0u); idim < get_dcount() - 1u; idim += 1u) {
					// generic formula: x0=cos([0])*cos([1]); x1=sin([0])*cos([1]); x2=sin([1])*cos([2]); ... xd=sin([xd-1]);
					for (v1u iprev(0u); iprev <= idim; iprev += 1u) { res[iprev] *= NW_NUM_COS(angles[idim]); }
					res[idim + 1u] *= NW_NUM_SIN(angles[idim]);
				}
				return circ.m_center + (circ.m_halfsz * res.get_norm());
			}
			return vert_t();
		}
		static constexpr inline vdata_tc make_vdata(circ_tc& circ, size_tc vcount, size_tc vindex) {
			NW_CHECK(vindex < vcount, "index error!", return vdata_t());
			vdata_t res( NW_NUM_POW(vcount - vindex, dims) );
			for (v1u ivert(vindex + 1u); ivert < res.size(); ivert++) { res[ivert] = make_vert(circ, vcount, ivert); }
			return res;
		}
		static constexpr inline idata_tc make_idata_vert(size_tc vcount, size_tc vindex) {
			NW_CHECK(vindex < vcount, "index error!", return idata_t());
			idata_t res((vcount - vindex), 0u);
			for (v1u idx(vindex); idx < res.get_count(); idx += 1u) { res[idx] = idx; }
			return res;
		}
		static constexpr inline idata_tc make_idata_wire(size_tc vcount, size_tc vindex) {
			NW_CHECK(vindex < vcount, "index error!", return idata_t());
			idata_t res((vcount - vindex) * 2u, 0u);
			for (v1u idx(vindex); idx < res.size(); idx += 2u) {
				res[idx + 0u] = ((idx / 2u) + 0u) % vcount;
				res[idx + 1u] = ((idx / 2u) + 1u) % vcount;
			}
			return res;
		}
		static constexpr inline idata_tc make_idata_trig(size_tc vcount, size_tc vindex) { // make indexed triangle list;
			NW_CHECK(vindex < vcount, "index error!", return idata_t());
			if constexpr (get_dcount() == 2u) {
				idata_t res((vcount - vindex) * 3u, 0u);
				for (v1u idx(vindex), last(0u); idx < vcount; idx += 1u, last += 3u) { // compose 2d-circle out of triangles;
					res[last + 0u] = vindex;
					res[last + 1u] = (idx + 0u) % vcount;
					res[last + 2u] = (idx + 1u) % vcount;
				}
				return res;
			}
			if constexpr (get_dcount() >= 3u) { // compose hypercircle out of quads;
				size_t icount(NW_NULL);
				num_vec_t<v1u, circ_t::get_dcount() - 1u> isizes(NW_NULL);
				for (v1u idim(0u); idim < get_dcount() - 1u; idim++) {
					isizes[idim] = NW_NUM_POW(NW_CAST_FLOAT(get_vcount(vcount)), get_dcount() - 1u - idim);
					icount += isizes[idim] * 6u;
				}
				idata_t res(icount * (get_dcount() - 1u), 0u);
				for (v1u idim(1u), last(0u); idim < get_dcount() - 1u; idim += 1u) {
					for (v1u idx(vindex); idx < icount; idx += 6u, last += 6u) {
						res[last + 0u] = (idx / 6u + 0u) % isizes[idim - 1u];
						res[last + 1u] = (idx / 6u + 1u) % isizes[idim - 1u];
						res[last + 2u] = (idx / 6u + isizes[idim] + 0u) % isizes[idim - 1u];
						res[last + 3u] = (idx / 6u + isizes[idim] + 0u) % isizes[idim - 1u];
						res[last + 4u] = (idx / 6u + isizes[idim] + 1u) % isizes[idim - 1u];
						res[last + 5u] = (idx / 6u + 1u) % isizes[idim - 1u];
					}
				}
				return res;
			}
			return idata_t();
		}
		static constexpr inline idata_tc make_idata_gizm_wire(size_tc vcount, size_tc vindex) { // make indexed list of gizmo wireframe;
			NW_CHECK(vindex < vcount, "index error!", return idata_t());
			if constexpr (get_dcount() == 2u) { return make_idata_wire(vcount, vindex); }
			if constexpr (get_dcount() >= 3u) {
				size_t icount(get_vcount(vcount)), last(0u);
				idata_t res(icount * get_dcount() * 2u, 0u);
				for (v1u idim(0u), istep(icount >> 1u); idim < get_dcount() - 1u; idim += 1u, istep >>= 1u) {
					for (v1u idx(vindex); idx < icount; idx += 1u, last += 2u) {
						res[last + 0u] = ( ((idx + 0u) % icount) * icount + istep ) % vcount;
						res[last + 1u] = ( ((idx + 1u) % icount) * icount + istep ) % vcount;
					}
				}
				return res;
			}
			return idata_t();
		}
		static constexpr inline cv1f make_dst(circ_tc& circ0, circ_tc& circ1) {
			return vec_t::make_dst(circ0.m_center, circ1.m_center) - vec_t::make_len(circ0.m_halfsz + circ1.m_halfsz);
		}
		static constexpr inline cv1f make_dst(circ_tc& circ0, circ_tc& circ1, size_tc dim) {
			return NW_NUM_ABS(circ1.m_center[dim] - circ0.m_center[dim]) - NW_NUM_ABS(circ1.m_halfsz[dim] + circ0.m_halfsz[dim]);
		}
#	endif	// core_methods
	public:
		vec_t m_center;
		vec_t m_halfsz;
	};
	template<size_tc dims> using d_circ_tc = const d_circ_t<dims>;
	typedef d_circ_t<2u> circ2d_t;
	typedef d_circ_t<3u> circ3d_t;
	typedef d_circ_t<4u> circ4d_t;
}
#endif	// NW_API
#endif	// NW_NUM_CIRCLE_H