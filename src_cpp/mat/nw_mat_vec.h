#ifndef NW_MAT_VECTOR_H
#define NW_MAT_VECTOR_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_vector struct
	template<typename tval, size_tc size_x>
	struct t_vec
	{
		// value
		using val_t = tval;
		using val_tc = const val_t;
		using vals_t = std::vector<val_t>;
		using vals_tc = const vals_t;
		using val_list_t = std::initializer_list<val_t>;
		using val_list_tc = const val_list_t;
		// vector
		using vec_t = t_vec<tval, size_x>;
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		using vec_list_t = std::initializer_list<vec_t>;
		using vec_list_tc = const vec_list_t;
		// // same size
		template<typename tname> using t_vec_t = t_vec<tname, size_x>;
		template<typename tname> using t_vec_tc = const t_vec_t<tname>;
	public:
		// --constructor_destructor
#	if(NW_TRUE)
		constexpr inline t_vec() : m_val{ static_cast<val_t>(NW_NULL) } { memset(m_val, NW_NULL, sizeof(vec_t)); }
		constexpr inline t_vec(val_tc& val) : t_vec() { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = val; } }
		constexpr inline t_vec(vals_tc& vals) : t_vec() { for (v1u ix(0u); ix < vals.size(); ix++) { m_val[ix] = *(vals.begin() + ix); } }
		constexpr inline t_vec(val_list_tc& vals) : t_vec() { for (v1u ix(0u); ix < vals.size(); ix++) { m_val[ix] = *(vals.begin() + ix); } }
		constexpr inline t_vec(vec_tc& copy) : t_vec() { memcpy(m_val, copy.m_val, sizeof(vec_t)); }
		constexpr inline t_vec(vec_t&& copy) : t_vec() { memmove(m_val, copy.m_val, sizeof(vec_t)); }
		template<typename tname> constexpr inline t_vec(t_vec_tc<tname>& copy) : t_vec() { operator=(copy); }
		template<typename tname> constexpr inline t_vec(t_vec_t<tname>&& copy) : t_vec() { operator=(copy); }
		inline ~t_vec() = default;
#	endif	// constructor_destructor
		// --getters
#	if (NW_TRUE)
		static constexpr inline size_tc get_size() { return size_x; }
		inline val_tc get_len() const { return make_len(*this); }
		inline val_tc get_dst(vec_tc& vec) const { return make_dst(*this, vec); }
		inline cv1f get_cos(vec_tc& vec) const { return make_cos(*this, vec); }
		inline cv1f get_dot(vec_tc& vec) const { return make_dot(*this, vec); }
		inline vec_tc get_crs(vec_tc& vec) const { return make_crs(*this, vec); }
		inline vec_tc get_nrm() const { return *this / make_len(*this); }
		inline cv1u get_near_idx(vecs_tc& vecs) const { return make_near_idx(*this, vecs); }
		inline cv1f get_near_dst(vecs_tc& vecs) const { return make_near_dst(*this, vecs); }
		inline vec_tc get_near(vecs_tc& vecs) const { return make_near(*this, vecs); }
		inline cv1u get_near_idx(vec_list_tc& vecs) const { return make_near_idx(*this, vecs); }
		inline cv1f get_near_dst(vec_list_tc& vecs) const { return make_near_dst(*this, vecs); }
		inline vec_tc get_near(vec_list_tc& vecs) const { return make_near(*this, vecs); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
		inline vec_t& set_crs() { return *this = get_crs(); }
		inline vec_t& set_nrm() { return *this = get_nrm(); }
		inline vec_tc& set_near(vecs_tc& vecs) { return *this = get_near(vecs); }
		inline vec_tc& set_near(vec_list_tc& vecs) { return *this = get_near(vecs); }
#	endif	// setters
		// --operators
#	if (NW_TRUE)
		// // --math
#		if (NW_TRUE)
		// // // --value
#			if (NW_TRUE)
		inline vec_tc operator+(val_tc val) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] + val; } return res; }
		inline vec_tc operator-(val_tc val) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] - val; } return res; }
		inline vec_tc operator*(val_tc val) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] * val; } return res; }
		inline vec_tc operator/(val_tc val) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] / val; } return res; }
		inline vec_t& operator+=(val_tc val) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] += val; } return *this; }
		inline vec_t& operator-=(val_tc val) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] -= val; } return *this; }
		inline vec_t& operator*=(val_tc val) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] *= val; } return *this; }
		inline vec_t& operator/=(val_tc val) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] /= val; } return *this; }
#			endif	// value
		// // // --vector
#			if (NW_TRUE)
		inline vec_tc operator+(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] + vec[ix]; } return res; }
		inline vec_tc operator-(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] - vec[ix]; } return res; }
		inline vec_tc operator*(vec_tc& vec) const { vec_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] * vec[ix]; } return res; }
		inline vec_tc operator/(vec_tc& vec) const { val_t res; for (v1u ix(0u); ix < size_x; ix++) { res[ix] = m_val[ix] / vec[ix]; } return res; }
		inline vec_t& operator+=(vec_tc& vec) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] += vec[ix]; } return *this; }
		inline vec_t& operator-=(vec_tc& vec) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] -= vec[ix]; } return *this; }
		inline vec_t& operator*=(vec_tc& vec) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] *= vec[ix]; } return *this; }
		inline vec_t& operator/=(vec_tc& vec) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] /= vec[ix]; } return *this; }
		inline vec_tc operator+() const { vec_t res(*this); for (v1u ix(0u); ix < size_x; ix++) { res[ix] = +m_val[ix]; } return res; }
		inline vec_tc operator-() const { vec_t res(*this); for (v1u ix(0u); ix < size_x; ix++) { res[ix] = -m_val[ix]; } return res; }
#			endif	// vector
#		endif	// math
		// // --asignment
#		if (NW_TRUE)
		inline vec_t& operator=(val_tc& val) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = val; } return *this; }
		inline vec_t& operator=(vals_tc& vals) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = vals[ix]; } return *this; }
		inline vec_t& operator=(val_list_tc& vals) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = vals[ix]; } return *this; }
		inline vec_t& operator=(vec_tc& copy) { memcpy(m_val, copy.m_val, sizeof(vec_t)); return *this; }
		inline vec_t& operator=(vec_t&& copy) { memmove(m_val, copy.m_val, sizeof(vec_t)); return *this; }
		template<typename tname> inline vec_t& operator=(t_vec_tc<tname>& copy) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = copy[ix]; } return *this; }
		template<typename tname> inline vec_t& operator=(t_vec_t<tname>&& copy) { for (v1u ix(0u); ix < size_x; ix++) { m_val[ix] = copy[ix]; } return *this; }
#		endif	// assignment
		// // --logic
#		if (NW_TRUE)
		inline v1bit operator==(val_tc& val) const { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[ix] != val) { return NW_FALSE; }} return NW_TRUE; }
		inline v1bit operator!=(val_tc& val) const { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[ix] == val) { return NW_FALSE; }} return NW_TRUE; }
		inline v1bit operator==(vec_tc& vec) const { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[ix] != vec[ix]) { return NW_FALSE; }} return NW_TRUE; }
		inline v1bit operator!=(vec_tc& vec) const { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[ix] == vec[ix]) { return NW_FALSE; }} return NW_TRUE; }
#		endif	// logic
		// // --accessors
#		if (NW_TRUE)
		inline val_t& operator[](cv1u idx)        { return m_val[idx]; }
		inline val_tc& operator[](cv1u idx) const { return m_val[idx]; }
#		endif	// accessors
		// // --input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const { for (v1u ix(0u); ix < size_x; ix++) { stm << m_val[ix] << "\t"; } return stm; }
		inline std::istream& operator>>(std::istream& stm) { for (v1u ix(0u); ix < size_x; ix++) { stm >> m_val[ix]; stm.get(); } return stm; }
#		endif	// input_output
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		static constexpr inline val_tc make_dst(vec_tc& vec0, vec_tc& vec1) {
			val_t res(NW_NULL);
			for (v1u ix(0u); ix < size_x; ix++) { res += NW_MATH_POW(vec0[ix] - vec1[ix], 2); }
			return NW_MATH_ROOT(res, 2);
		}
		static constexpr inline val_tc make_len(vec_tc& vec) {
			val_t res(NW_NULL);
			for (v1u ix(0u); ix < size_x; ix++) { res += NW_MATH_POW(vec[ix], 2); }
			return NW_MATH_ROOT(res, 2);
		}
		static constexpr inline cv1f make_cos(vec_tc& vec0, vec_tc& vec1) {
			return get_dot(vec0, vec1) / (vec0.get_len() * vec1.get_len());
		}
		static constexpr inline cv1f make_dot(vec_tc& vec0, vec_tc& vec1) {
			v1f res(NW_NULL);
			for (v1u ix(0u); ix < size_x; ix++) { res += vec0[ix] * vec1[ix]; }
			return res;
		}
		static constexpr inline vec_tc make_crs(vec_tc& vec0, vec_tc& vec1) {
			static_assert(size_x >= 3, "not enough dimensions for cross product");
			vec_t res(NW_NULL);
			res[0] = (vec0[1] * vec1[2]) - (vec0[2] * vec1[1]);
			res[1] = (vec0[2] * vec1[0]) - (vec0[0] * vec1[2]);
			res[2] = (vec0[0] * vec1[1]) - (vec0[1] * vec1[0]);
			return res;
		}
		static constexpr inline vec_tc make_nrm(vec_tc& vector) { return vector / vector.get_len(); }
		static constexpr inline cv1u make_near_idx(vec_tc& vec, vecs_tc& vecs) {
			v1f dst(INFINITY);
			v1u idx(NW_NULL);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; idx = ixy; }
			}
			return idx;
		}
		static constexpr inline cv1f make_near_dst(vec_tc& vec, vecs_tc& vecs) {
			v1f dst(INFINITY);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; }
			}
			return dst;
		}
		static constexpr inline vec_tc make_near(vec_tc& vec, vecs_tc& vecs) {
			return vecs[make_near_idx(vec, vecs)];
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
		static constexpr inline cv1f make_near_dst(vec_tc& vec, vec_list_tc& vecs) {
			v1f dst(INFINITY);
			for (v1u ixy = 0u; ixy < vecs.size(); ixy++) {
				v1f next = vec.get_dst(vecs[ixy]);
				if (next < dst) { dst = next; }
			}
			return dst;
		}
		static constexpr inline vec_tc make_near(vec_tc& vec, vec_list_tc& vecs) {
			return vecs[make_near_idx(vec, vecs)];
		}
#	endif	// core_methods
	public:
		val_t m_val[size_x];
	};
	// --input_output
	template<typename tval, size_tc size_x>
	inline std::ostream& operator<<(std::ostream& stm, const t_vec<tval, size_x>& vector) { return vector.operator<<(stm); }
	template<typename tval, size_tc size_x>
	inline std::istream& operator>>(std::istream& stm, t_vec<tval, size_x>& vector) { return vector.operator>>(stm); }
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
#	define NW_ITERATOR(tname, vname, size_x)   \
	typedef t_vec<vname, size_x> tname; \
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
#endif	// NW_MAT_VECTOR_H