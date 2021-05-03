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
#	endif	// constructor_destructor
		// --getters
#	if (NW_TRUE)
		static constexpr inline size_tc get_dcount() { return dims; }
		inline cv1f get_dst(circ_tc& circ) const { return make_dst(*this, circ); }
		inline cv1f get_dst(circ_tc& circ, size_tc dim) const { return make_dst(*this, circ, dim); }
		inline vert_tc get_vert(size_tc vcount, size_tc vindex) const { return make_vert(*this, vcount, vindex); }
		inline vdata_tc get_vdata(size_tc vcount) const { return make_vdata(*this, vcount); }
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
		static constexpr inline cv1f make_dst(circ_tc& circ0, circ_tc& circ1) {
			return vec_t::make_dst(circ0.m_center, circ1.m_center) - vec_t::make_len(circ0.m_halfsz + circ1.m_halfsz);
		}
		static constexpr inline cv1f make_dst(circ_tc& circ0, circ_tc& circ1, size_tc dim) {
			return NW_NUM_ABS(circ1.m_center[dim] - circ0.m_center[dim]) - NW_NUM_ABS(circ1.m_halfsz[dim] + circ0.m_halfsz[dim]);
		}
		static constexpr inline vert_tc make_vert(circ_tc& circ, size_tc vcount, size_tc vindex) {
			vert_t res(1.0f); cv1u dvcount( NW_NUM_ROOT(NW_CAST_FLOAT(vcount), NW_CAST_FLOAT(dims - 1u)) );
			num_vec_t<v1f, dims - 1u> angles(360.0f / dvcount);
			angles[0] *= NW_CAST_FLOAT(vindex % dvcount);
			if constexpr (dims > 2u) {
				for (v1u iangle(1u); iangle < dims - 1u; iangle++) {
					// angle in every dimension must be the step multiplied by index accordingly to a particular dimension;
					// we also need to divide it by ;
					angles[iangle] *= NW_CAST_FLOAT(vindex / NW_NUM_POW(dvcount, iangle));
					angles[iangle] /= NW_CAST_FLOAT(dims - iangle - 1u);
				}
			}
			if constexpr (dims == 2u) {
				res[0] = NW_NUM_COS(angles[0]);
				res[1] = NW_NUM_SIN(angles[0]);
			}
			if constexpr (dims == 3u) {
				res[0] = NW_NUM_SIN(angles[0]) * NW_NUM_COS(angles[1]);
				res[1] = NW_NUM_SIN(angles[1]);
				res[2] = NW_NUM_COS(angles[0]);
			}
			return circ.m_center + (circ.m_halfsz * res.get_norm());
		}
		static constexpr inline vdata_tc make_vdata(circ_tc& circ, size_tc vcount) {
			vdata_t res( NW_NUM_POW(vcount, dims) );
			for (v1u ivert(0u); ivert < res.size(); ivert++) {
				res[ivert] = make_vdata(circ, vcount, ivert);
			}
			return res;
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