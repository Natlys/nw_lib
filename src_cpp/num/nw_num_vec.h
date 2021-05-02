#ifndef NW_NUM_VECTOR_H
#define NW_NUM_VECTOR_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_val.h"
#	include "../std/nw_std_func.h"
namespace NW
{
	/// number_vector struct
	template<typename tval, size_tc dims>
	struct num_vec_t
	{
		// value
		using val_t = tval;
		using val_tc = const val_t;
		using vals_t = std::vector<val_t>;
		using vals_tc = const vals_t;
		using val_list_t = std::initializer_list<val_t>;
		using val_list_tc = const val_list_t;
		// vector
		using vec_t = num_vec_t<tval, dims>;
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		using vec_list_t = std::initializer_list<vec_t>;
		using vec_list_tc = const vec_list_t;
		// // --different type
		template<typename tname> using t_vec_t = num_vec_t<tname, dims>;
		template<typename tname> using t_vec_tc = const t_vec_t<tname>;
		// // --different size
		template<size_tc vec_dims> using d_vec_t = num_vec_t<tval, vec_dims>;
		template<size_tc vec_dims> using d_vec_tc = const d_vec_t<vec_dims>;
	public:
		// --ctor_dtor
#	if(NW_TRUE)
		constexpr inline num_vec_t() : m_val{ static_cast<val_t>(NW_NULL) } { memset(m_val, NW_NULL, sizeof(vec_t)); }
		constexpr inline num_vec_t(val_tc& val) : num_vec_t() { operator=(val); }
		constexpr inline num_vec_t(vals_tc& vals) : num_vec_t() { operator=(vals); }
		constexpr inline num_vec_t(val_list_tc& vals) : num_vec_t() { operator=(vals); }
		constexpr inline num_vec_t(vec_tc& vec) : num_vec_t() { operator=(vec); }
		constexpr inline num_vec_t(vec_t&& vec) : num_vec_t() { operator=(vec); }
		template<typename tname> constexpr inline num_vec_t(t_vec_tc<tname>& vec) : num_vec_t() { operator=(vec); }
		template<typename tname> constexpr inline num_vec_t(t_vec_t<tname>&& vec) : num_vec_t() { operator=(vec); }
		template<size_tc vec_dims> constexpr inline num_vec_t(d_vec_tc<vec_dims>& vec) : num_vec_t() { operator=(vec); }
		template<size_tc vec_dims> constexpr inline num_vec_t(d_vec_t<vec_dims>&& vec) : num_vec_t() { operator=(vec); }
		template<typename tname, size_tc vec_dims> constexpr inline num_vec_t(num_vec_t<tname, vec_dims>&& vec) : num_vec_t() { operator=(vec); }
		inline ~num_vec_t() = default;
#	endif	// constructor_destructor
		// --getters
#	if (NW_TRUE)
		// // --info
		static constexpr inline size_tc get_count() { return dims; }
		// // --value
		inline val_tc get_len() const { return make_len(*this); }
		inline val_tc get_dst(vec_tc& vec) const { return make_dst(*this, vec); }
		inline val_tc get_cos(vec_tc& vec) const { return make_cos(*this, vec); }
		inline val_tc get_dot(vec_tc& vec) const { return make_dot(*this, vec); }
		inline cv1u get_near_idx(vecs_tc& vecs) const { return make_near_idx(*this, vecs); }
		inline cv1u get_near_idx(vec_list_tc& vecs) const { return make_near_idx(*this, vecs); }
		inline val_tc get_near_dst(vecs_tc& vecs) const { return make_near_dst(*this, vecs); }
		inline val_tc get_near_dst(vec_list_tc& vecs) const { return make_near_dst(*this, vecs); }
		// // --vector
		inline vec_tc get_crs(vec_tc& vec) const { return make_crs(*this, vec); }
		inline vec_tc get_norm() const { return make_norm(*this); }
		inline vec_tc get_near(vecs_tc& vecs) const { return make_near(*this, vecs); }
		inline vec_tc get_near(vec_list_tc& vecs) const { return make_near(*this, vecs); }
		inline vec_tc get_pows(val_tc power) const { return make_pows(m_vals[0u], power); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
		inline vec_t& set_crs() { return *this = get_crs(); }
		inline vec_t& set_norm() { return *this = get_norm(); }
		inline vec_t& set_near(vecs_tc& vecs) { return *this = get_near(vecs); }
		inline vec_t& set_near(vec_list_tc& vecs) { return *this = get_near(vecs); }
		inline vec_t& set_pows(val_tc power) { return *this = get_pows(power); }
#	endif	// setters
		// --operators
#	if (NW_TRUE)
		// // --mathematics
#		if (NW_TRUE)
		// // // --value
		inline vec_tc operator+(val_tc val) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] + val; } return res; }
		inline vec_tc operator-(val_tc val) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] - val; } return res; }
		inline vec_tc operator*(val_tc val) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] * val; } return res; }
		inline vec_tc operator/(val_tc val) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] / val; } return res; }
		inline vec_t& operator+=(val_tc val) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] += val; } return *this; }
		inline vec_t& operator-=(val_tc val) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] -= val; } return *this; }
		inline vec_t& operator*=(val_tc val) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] *= val; } return *this; }
		inline vec_t& operator/=(val_tc val) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] /= val; } return *this; }
		// // // --vector
		inline vec_tc operator+(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] + vec[ix]; } return res; }
		inline vec_tc operator-(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] - vec[ix]; } return res; }
		inline vec_tc operator*(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] * vec[ix]; } return res; }
		inline vec_tc operator/(vec_tc& vec) const { val_t res; for (v1u ix(0u); ix < dims; ix++) { res[ix] = m_val[ix] / vec[ix]; } return res; }
		inline vec_t& operator+=(vec_tc& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] += vec[ix]; } return *this; }
		inline vec_t& operator-=(vec_tc& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] -= vec[ix]; } return *this; }
		inline vec_t& operator*=(vec_tc& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] *= vec[ix]; } return *this; }
		inline vec_t& operator/=(vec_tc& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] /= vec[ix]; } return *this; }
		inline vec_tc operator+() const { vec_t res(*this); for (v1u ix(0u); ix < dims; ix++) { res[ix] = +m_val[ix]; } return res; }
		inline vec_tc operator-() const { vec_t res(*this); for (v1u ix(0u); ix < dims; ix++) { res[ix] = -m_val[ix]; } return res; }
#		endif	// mathematics
		// // --asignment
#		if (NW_TRUE)
		// // // --value
		inline vec_t& operator=(val_tc& val) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] = val; } return *this; }
		inline vec_t& operator=(vals_tc& vals) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] = vals[ix]; } return *this; }
		inline vec_t& operator=(val_list_tc& vals) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] = *(vals.begin() + ix); } return *this; }
		// // // --vector
		inline vec_t& operator=(vec_tc& vec) { memcpy(m_val, vec.m_val, sizeof(vec_t)); return *this; }
		inline vec_t& operator=(vec_t&& vec) { memmove(m_val, vec.m_val, sizeof(vec_t)); return *this; }
		template<typename tname> inline vec_t& operator=(t_vec_tc<tname>& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] = vec[ix]; } return *this; }
		template<typename tname> inline vec_t& operator=(t_vec_t<tname>&& vec) { for (v1u ix(0u); ix < dims; ix++) { m_val[ix] = vec[ix]; } return *this; }
		template<size_tc vec_dims> inline vec_t& operator=(d_vec_tc<vec_dims>& vec) { for (v1u ix(0u); ix < NW_NUM_MIN(vec_dims, dims); ix++) { m_val[ix] = vec[ix]; } return *this; }
		template<size_tc vec_dims> inline vec_t& operator=(d_vec_t<vec_dims>&& vec) { for (v1u ix(0u); ix < NW_NUM_MIN(vec_dims, dims); ix++) { m_val[ix] = vec[ix]; } return *this; }
#		endif	// assignment
		// // --conversion
#		if (NW_TRUE)
		// // // --value
		inline operator val_t() const { return get_len(); }
		// // // --vector
		template<typename tname> operator t_vec_t<tname>() { t_vec_t<tname> res; for (v1u ix(0u); ix < dim; ix++) { res[ix] = m_val[ix]; } return res; }
		template<size_tc vec_dims> operator d_vec_t<vec_dims>() { d_vec_t<vec_dims> res; for (v1u ix(0u); ix < NW_NUM_MIN(dims, vec_dims); ix++) { res[ix] = m_val[ix]; } return res; }
#		endif	// conversion
		// // --logic
#		if (NW_TRUE)
		// // // --value
		inline v1bit operator==(val_tc& val) const { for (v1u ix(0u); ix < dims; ix++) { if (m_val[ix] != val) { return NW_FALSE; }} return NW_TRUE; }
		inline v1bit operator!=(val_tc& val) const { for (v1u ix(0u); ix < dims; ix++) { if (m_val[ix] == val) { return NW_FALSE; }} return NW_TRUE; }
		// // // --vector
		inline v1bit operator==(vec_tc& vec) const { for (v1u ix(0u); ix < dims; ix++) { if (m_val[ix] != vec[ix]) { return NW_FALSE; }} return NW_TRUE; }
		inline v1bit operator!=(vec_tc& vec) const { for (v1u ix(0u); ix < dims; ix++) { if (m_val[ix] == vec[ix]) { return NW_FALSE; }} return NW_TRUE; }
#		endif	// logic
		// // --accessors
#		if (NW_TRUE)
		// // --value
		inline val_t& operator()(cv1u ix)        { return m_val[ix]; }
		inline val_tc& operator()(cv1u ix) const { return m_val[ix]; }
		inline val_t& operator[](cv1u ix)        { return m_val[ix]; }
		inline val_tc& operator[](cv1u ix) const { return m_val[ix]; }
#		endif	// accessors
		// // --input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const { for (v1u ix(0u); ix < dims; ix++) { stm << m_val[ix] << "\t"; } return stm; }
		inline std::istream& operator>>(std::istream& stm) { for (v1u ix(0u); ix < dims; ix++) { stm >> m_val[ix]; stm.get(); } return stm; }
#		endif	// input_output
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		// // --value
		static constexpr inline vec_tc make_add(vec_tc vec, val_tc val) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec[ix] + val[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_sub(vec_tc vec, val_tc val) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec[ix] - val[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_mul(vec_tc vec, val_tc val) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec[ix] * val[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_div(vec_tc vec, val_tc val) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec[ix] / val[ix]; }
			return res;
		}
		static constexpr inline val_tc make_dot(vec_tc& vec0, vec_tc& vec1) {
			v1f res(NW_NULL);
			for (v1u ix(0u); ix < dims; ix++) { res += vec0[ix] * vec1[ix]; }
			return res;
		}
		static constexpr inline val_tc make_cos(vec_tc& vec0, vec_tc& vec1) {
			return get_dot(vec0, vec1) / (vec0.get_len() * vec1.get_len());
		}
		static constexpr inline val_tc make_dst(vec_tc& vec0, vec_tc& vec1) {
			val_t res(NW_NULL);
			for (v1u ix(0u); ix < dims; ix++) { res += NW_NUM_POW(vec0[ix] - vec1[ix], 2); }
			return NW_NUM_ROOT(res, 2);
		}
		static constexpr inline val_tc make_len(vec_tc& vec) {
			val_t res(NW_NULL);
			for (v1u ix(0u); ix < dims; ix++) { res += NW_NUM_POW(vec[ix], 2); }
			return NW_NUM_ROOT(res, 2);
		}
		static constexpr inline val_tc make_near_dst(vec_tc& vec, vecs_tc& vecs) {
			v1f dst(INFINITY);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; }
			}
			return dst;
		}
		static constexpr inline val_tc make_near_dst(vec_tc& vec, vec_list_tc& vecs) {
			v1f dst(INFINITY);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; }
			}
			return dst;
		}
		static constexpr inline cv1u make_near_idx(vec_tc& vec, vecs_tc& vecs) {
			v1f dst(INFINITY);
			v1u idx(NW_NULL);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; idx = ixy; }
			}
			return idx;
		}
		static constexpr inline cv1u make_near_idx(vec_tc& vec, vec_list_tc& vecs) {
			v1f dst(INFINITY);
			v1u idx(NW_NULL);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; idx = ixy; }
			}
			return idx;
		}
		// // --vector
		static constexpr inline vec_tc make_add(vec_tc& vec0, vec_tc& vec1) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec0[ix] + vec1[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_sub(vec_tc& vec0, vec_tc& vec1) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec0[ix] - vec1[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_mul(vec_tc& vec0, vec_tc& vec1) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec0[ix] * vec1[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_div(vec_tc& vec0, vec_tc& vec1) {
			vec_t res;
			for (v1u ix(0u); ix < dims; ix++) { res[ix] = vec0[ix] / vec1[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_unit(val_tc val = NW_UNIT) { return vec_t(val); }
		static constexpr inline vec_tc make_crs(vec_tc& vec0, vec_tc& vec1) {
			static_assert(dims >= 3, "not enough dimensions for cross product");
			vec_t res(NW_NULL);
			res[0] = (vec0[1] * vec1[2]) - (vec0[2] * vec1[1]);
			res[1] = (vec0[2] * vec1[0]) - (vec0[0] * vec1[2]);
			res[2] = (vec0[0] * vec1[1]) - (vec0[1] * vec1[0]);
			return res;
		}
		static constexpr inline vec_tc make_norm(vec_tc& vec) { return vec / vec.get_len(); }
		static constexpr inline vec_tc make_near(vec_tc& vec, vecs_tc& vecs) {
			return vecs[make_near_idx(vec, vecs)];
		}
		static constexpr inline vec_tc make_near(vec_tc& vec, vec_list_tc& vecs) {
			return vecs[make_near_idx(vec, vecs)];
		}
		static constexpr inline vec_tc make_rand(val_tc vmin, val_tc vmax) {
			vec_t res(NW_NULL);
			for (v1u idim(0u); idim < get_count(); idim++) { res[idim] = get_rand<val_t>(vmin, vmax); }
			return res;
		}
		static constexpr inline vec_tc make_pows(val_tc first, cv1f power) {
			vec_t res(first);
			for (v1u idim(1u); idim < get_count(); idim++) { res[idim] = NW_NUM_POW(NW_CAST_FLOAT(res[idim]), NW_CAST_FLOAT(power)); }
			return res;
		}
		static constexpr inline vec_tc apply_all(vec_tc& vec, func_tc<val_tc(val_tc& val)>& func) { for (v1u idim(0u); idim < get_count(); idim++) { vec[idim] = func(vec[idim]); } }
		static constexpr inline vec_tc apply_all(vec_tc& vec, func_tc<val_tc(val_tc& val, cv1u dim)>& func) { for (v1u idim(0u); idim < get_count(); idim++) { vec[idim] = func(vec[idim], idim); } }
		inline vec_t& apply_all(func_tc<val_tc(val_tc& val)>& func) { return this* = apply_all(*this, func); }
		inline vec_t& apply_all(func_tc<val_tc(val_tc& val, cv1u dim)>& func) { return this* = apply_all(*this, func); }
#	endif	// core_methods
	public:
		val_t m_val[dims];
	};
	// --input_output
	template<typename tval, size_tc dims>
	inline std::ostream& operator<<(std::ostream& stm, const num_vec_t<tval, dims>& vector) { return vector.operator<<(stm); }
	template<typename tval, size_tc dims>
	inline std::istream& operator>>(std::istream& stm, num_vec_t<tval, dims>& vector) { return vector.operator>>(stm); }
	// typedefs
	template<typename tval, size_tc dims> using num_vec_tc = const num_vec_t<tval, dims>;
}
#	if (!defined NW_FOREACH && !defined NW_INVOKER && !defined NW_ITERATOR)
#	define NW_FOREACH(INVOKER, ITERATOR) \
	INVOKER(bit, ITERATOR) \
	INVOKER(s08, ITERATOR) \
	INVOKER(u08, ITERATOR) \
	INVOKER(s16, ITERATOR) \
	INVOKER(u16, ITERATOR) \
	INVOKER(s32, ITERATOR) \
	INVOKER(u32, ITERATOR) \
	INVOKER(s64, ITERATOR) \
	INVOKER(u64, ITERATOR) \
	INVOKER(f32, ITERATOR) \
	INVOKER(f64, ITERATOR) \
	INVOKER(b, ITERATOR) \
	INVOKER(s, ITERATOR) \
	INVOKER(u, ITERATOR) \
	INVOKER(f, ITERATOR) \
	INVOKER(n, ITERATOR) \
// that's it
#	define NW_INVOKER(tname, ITERATOR) \
	ITERATOR(v2##tname, v1##tname, 2u)  \
	ITERATOR(v3##tname, v1##tname, 3u)  \
	ITERATOR(v4##tname, v1##tname, 4u)  \
// that's it
#	define NW_ITERATOR(tname, vname, dims)   \
	typedef num_vec_t<vname, dims> tname; \
	typedef const tname       c##tname; \
// that's it
namespace NW { NW_FOREACH(NW_INVOKER, NW_ITERATOR); }
#	undef NW_ITERATOR
#	undef NW_INVOKER
#	undef NW_FOREACH
#	else
#		error "macroses named above must not be defined here!"
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
#endif	// NW_API
#endif	// NW_NUM_VECTOR_H