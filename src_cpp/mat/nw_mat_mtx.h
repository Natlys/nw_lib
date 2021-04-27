#ifndef NW_MAT_MATRIX_H
#define NW_MAT_MATRIX_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// typed_matrix struct
	template<typename tval, size_tc size_x, size_tc size_y = size_x>
	struct t_mat
	{
		static_assert(size_x > 1u && size_y > 1u, "mat must be greater than one value or a vec");
		// value type
		using val_t = tval;
		using val_tc = const val_t;
		using vals_t = std::vector<val_t>;
		using vals_tc = const vals_t;
		using val_list_t = std::initializer_list<val_t>;
		using val_list_tc = const val_list_t;
		// vector type
		using vec_t = t_vec<tval, size_y>;
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		using vec_list_t = std::initializer_list<vec_t>;
		using vec_list_tc = const vec_list_t;
		template<size_tc vec_size>
		using vec_t_s = t_vec<tval, vec_size>;
		template<size_tc vec_size>
		using vec_tc_s = const vec_t_s<vec_size>;
		// matrix type
		using mat_t = t_mat<tval, size_x, size_y>;
		using mat_tc = const mat_t;
		using mats_t = std::vector<mat_t>;
		using mats_tc = const mats_t;
		using mat_list_t = std::initializer_list<mat_t>;
		using mat_list_tc = const mat_list_t;
		// // same tval, same size_y
		template<size_tc mat_size_x>
		using mat_t_x = t_mat<tval, mat_size_x, size_y>;
		template<size_tc mat_size_x>
		// // same tval, same size_x
		using mat_tc_x = const mat_t_x<mat_size_x>;
		template<size_tc mat_size_y>
		using mat_t_y = t_mat<tval, size_x, mat_size_y>;
		template<size_tc mat_size_y>
		using mat_tc_y = const mat_t_y<mat_size_y>;
		// // same tval
		template<size_tc mat_size_x, size_tc mat_size_y>
		using mat_t_xy = NW::t_mat<tval, mat_size_x, mat_size_y>;
		template<size_tc mat_size_x, size_tc mat_size_y>
		using mat_tc_xy = const mat_t_xy<mat_size_x, mat_size_y>;
		// // same tval, square size
		template<size_tc mat_size_xy>
		using mat_t_s = t_mat<tval, mat_size_xy, mat_size_xy>;
		template<size_tc mat_size_xy>
		using mat_tc_s = const mat_t_s<mat_size_xy>;
	public:
		// --constructor_destructor
#	if(NW_TRUE)
		constexpr inline t_mat() : m_val{ static_cast<val_t>(NW_NULL) } { memset(m_val, NW_NULL, sizeof(mat_t)); }
		constexpr inline t_mat(val_tc& val) : t_mat() { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] = val; } } }
		constexpr inline t_mat(vec_tc& vec) : t_mat() { for (v1u iy(0u); iy < size_y; iy++) { m_val[iy] = vec; } }
		constexpr inline t_mat(vals_tc& vals) : t_mat() { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } }
		constexpr inline t_mat(vecs_tc& vecs) : t_mat() { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } }
		constexpr inline t_mat(val_list_tc& vals) : t_mat() { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } }
		constexpr inline t_mat(vec_list_tc& vecs) : t_mat() { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } }
		constexpr inline t_mat(mat_tc& copy) : t_mat() { memcpy(m_val, copy.m_val, sizeof(mat_t)); }
		constexpr inline t_mat(mat_t&& copy) : t_mat() { memmove(m_val, copy.m_val, sizeof(mat_t)); }
		inline ~t_mat() = default;
#	endif	// constructor_destructor
		// --getters
#	if (NW_TRUE)
		static constexpr inline size_tc get_size() { return size_x * size_y; }
		static constexpr inline size_tc get_size_x() { return size_x; }
		static constexpr inline size_tc get_size_y() { return size_y; }
		static constexpr inline size_tc get_size_min() { return size_x < size_y ? size_x : size_y; }
		static constexpr inline size_tc get_size_max() { return size_x > size_y ? size_x : size_y; }
		static constexpr inline size_tc get_rows() { return size_y; }
		static constexpr inline size_tc get_cols() { return size_x; }
		inline mat_tc get_inver() { return make_inver(*this); }
		inline mat_tc get_trpos() { return make_trpos(*this); }
		template<size_tc vec_size> mat_tc get_scale(vec_tc_s<vec_size>& scale) const { return *this = make_scale(scale); }
		template<size_tc vec_size> mat_tc get_coord(vec_tc_s<vec_size>& coord) const { return *this * make_coord(coord); }
		inline mat_tc get_rotat_x(cv1f degree) const { return *this = make_rotat_x(degree); }
		inline mat_tc get_rotat_y(cv1f degree) const { return *this = make_rotat_y(degree); }
		inline mat_tc get_rotat_z(cv1f degree) const { return *this = make_rotat_z(degree); }
		inline mat_tc get_rotat_xyz(cv3f degree_xyz) const { return *this * make_rotat_xyz(degree_xyz); }
		inline mat_tc_xy<size_x - 1u, size_y - 1u> get_erase(v1u erase_x, v1u erase_y) const { return make_erase(*this, erase_x, erase_y); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
		inline mat_t& set_ident(cv1f val = static_cast<val_t>(1)) { return *this = make_ident(val); }
		inline mat_t& set_inver() { return *this = get_inver(); }
		inline mat_t& set_trpos() { return *this = get_trpos(); }
		template<size_tc vec_size> mat_t& set_scale(vec_tc_s<vec_size>& scale) { return *this *= make_scale(scale); }
		template<size_tc vec_size> mat_t& set_coord(vec_tc_s<vec_size>& coord) { return *this *= make_coord(coord); }
		inline mat_t& set_rotat_x(cv1f degree) { return *this *= make_rotat_x(degree); }
		inline mat_t& set_rotat_y(cv1f degree) { return *this *= make_rotat_y(degree); }
		inline mat_t& set_rotat_z(cv1f degree) { return *this *= make_rotat_z(degree); }
		inline mat_t& set_rotat_xyz(cv3f degree_xyz) { return *this *= make_rotat_xyz(degree_xyz); }
#	endif	// setters
		// --operators
#	if (NW_TRUE)
		// // --math
#		if (NW_TRUE)
		// // // --value
#			if (NW_TRUE)
		inline mat_tc operator+(val_tc& val) const { mat_t res; for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = m_val[iy][ix] + val; } } return res; }
		inline mat_tc operator-(val_tc& val) const { mat_t res; for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = m_val[iy][ix] - val; } } return res; }
		inline mat_tc operator*(val_tc& val) const { mat_t res; for (v1u iy(0u); iy < size_x; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = m_val[iy][ix] * val; } } return res; }
		inline mat_tc operator/(val_tc& val) const { mat_t res; for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = m_val[iy][ix] / val; } } return res; }
		inline mat_t& operator+=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] += val; } } return *this; }
		inline mat_t& operator-=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] -= val; } } return *this; }
		inline mat_t& operator*=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] *= val; } } return *this; }
		inline mat_t& operator/=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] /= val; } } return *this; }
#			endif	// value
		// // // --vector
#			if (NW_TRUE)
		inline vec_tc operator*(vec_tc& vec) const { vec_tc res; for (v1u iy; iy < size_x; iy++) { for (v1u itr; itr < size_x; itr++) { res[iy] += m_val[iy][itr] * vec[itr]; } } return res; }
#			endif	// vector
		// // // --matrix
#			if (NW_TRUE)
		inline mat_tc operator+(mat_tc& mat) const { mat_t res; for (v1u ix(0u); ix < size_x; ix++) { for (v1u iy(0u); iy < size_y; iy++) { res[iy][ix] + m_val[iy][ix]; } } return res; }
		inline mat_tc operator-(mat_tc& mat) const { mat_t res; for (v1u ix(0u); ix < size_x; ix++) { for (v1u iy(0u); iy < size_y; iy++) { res[iy][ix] - m_val[iy][ix]; } } return res; }
		inline mat_tc operator*(mat_tc& mat) const { mat_t res; for (v1u iy(0u); iy < size_x; iy++) { for (v1u ix(0u); ix < size_x; ix++) { for (v1u iz(0u); iz < size_x; iz++) { res[iy][ix] += m_val[iy][iz] * mat[iz][ix]; } } } return res; }
		inline mat_t& operator+=(mat_tc& mat) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] += mat[iy][ix]; } } return *this; }
		inline mat_t& operator-=(mat_tc& mat) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] -= mat[iy][ix]; } } return *this; }
		inline mat_t& operator*=(mat_tc& mat) { mat_t temp(*this); for (v1u iy(0u); iy < size_x; iy++) { for (v1u ix(0u); ix < size_x; ix++) { for (v1u iz(0u); iz < size_x; iz++) { m_val[iy][ix] += temp[iy][iz] * mat[iz][ix]; } } } return *this; }
#			endif	// matrix
#		endif	// --math
		// // --assignment
#		if (NW_TRUE)
		inline mat_t& operator=(vals_tc& vals) { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } return *this; }
		inline mat_t& operator=(vecs_tc& vecs) { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } return *this; }
		inline mat_t& operator=(val_list_tc& vals) { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } return *this; }
		inline mat_t& operator=(vec_list_tc& vecs) { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } return *this; }
		inline mat_t& operator=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] = val; } } return *this; }
		inline mat_t& operator=(vec_tc& vec) { for (v1u iy(0u); iy < size_y; iy++) { m_val[iy] = vec; } return *this; }
		inline mat_t& operator=(mat_tc& mat) { memcpy(m_val, mat.m_val, sizeof(mat_t)); return *this; }
		inline mat_t& operator=(mat_t&& mat) { memmove(m_val, mat.m_val, sizeof(mat_t)); return *this; }
#		endif	// assignment
		// // --logic
#		if (NW_TRUE)
		inline v1bit operator==(val_tc& val) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] != val) { return NW_FALSE; } } } return NW_TRUE; }
		inline v1bit operator!=(val_tc& val) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] == val) { return NW_FALSE; } } } return NW_TRUE; }
		inline v1bit operator==(vec_tc& vec) const { for (v1u iy(0u); iy < size_y; iy++) { if (m_val[iy] != vec) { return NW_FALSE; } } return NW_TRUE; }
		inline v1bit operator!=(vec_tc& vec) const { for (v1u iy(0u); iy < size_y; iy++) { if (m_val[iy] == vec) { return NW_FALSE; } } return NW_TRUE; }
		inline v1bit operator==(mat_tc& mat) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] != mat[iy][ix]) { return NW_FALSE; } } } return NW_TRUE; }
		inline v1bit operator!=(mat_tc& mat) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] == mat[iy][ix]) { return NW_FALSE; } } } return NW_TRUE; }
#		endif	// logic
		// // --accessors
#		if (NW_TRUE)
		inline vec_t& operator[](cv1u idx)        { return m_val[idx]; }
		inline vec_tc& operator[](cv1u idx) const { return m_val[idx]; }
#		endif	// accessors
		// // --input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const { for (v1u ix(0u); ix < size_x; ix++) { stm << m_val[ix] << NW_STR_EOL; } return stm; }
		inline std::istream& operator>>(std::istream& stm) { for (v1u ix(0u); ix < size_x; ix++) { stm >> m_val[ix]; stm.get(); } return stm; }
#		endif	// input_output
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		static constexpr inline mat_tc make_ident(val_tc diag = static_cast<val_t>(1)) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square mat");
			mat_t res;
			for (v1u idiag(0u); idiag < get_size_max(); idiag++) { res[idiag][idiag] = diag; }
			return res;
		}
		static constexpr inline mat_tc make_trpos(mat_tc& mat) {
			mat_t res;
			for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[ix][iy]; } }
			return res;
		}
		static constexpr inline mat_tc make_inver(mat_tc& mat) {
			static_assert(size_x == size_y, "not square mat cannot be inversed!");
			static_assert(NW_FALSE, "the function is not ready!");
			return mat_t();
#			if (NW_FALSE)
			mat_t_xy<size_x, size_y * 2> result(static_cast<val_t>(0));
			for (v1u iy = 0; iy < size_y; iy++) {
				for (v1u ix = 0; ix < size_x; ix++) {
					result[iy][ix] = mat[iy][ix];
				}
				result[iy][iy + size_y] = static_cast<val_t>(1);
			}
			{
				for (v1u iy(0u), ix(0u); iy < size_y && ix < size_x; iy++, ix++) {
					v1u itr = iy;
					while (result[iy][ix] == static_cast<val_t>(0)) {
						if (itr == size_y) {
							itr = iy;
							if (ix++ == size_x) { return mat; }
						}
					}
					result.trpos();
					if (result[iy][ix] != static_cast<val_t>(0)) {
						val_t temp = result[iy][ix];
						for (v1u itr = 0u; itr < size_x; itr++)
							result[iy][ix] /= temp;
					}
					for (v1u itr_y = 0; itr_y < size_y; itr_y++) {
						if (itr_y == iy) { continue; }
						val_t temp = result[itr_y][ix];
						for (v1u itr_x = 0u; itr_x < size_x; itr_x++) {
							result[itr_y][itr_x] -= temp * result[iy][itr_x];
						}
					}
				}
			}
			t_mat inversed(static_cast<val_t>(0));
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					inversed[iy][ix] = result[iy][ix + size_y];
				}
			}
			return inversed;
#			endif
		}
		template<size_tc vec_size> static constexpr inline mat_tc make_scale(vec_tc_s<vec_size>& scale) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square mat");
			static_assert(vec_size <= get_size_min(), "diagonal is too big for this mat");
			mat_t res(make_ident());
			for (v1u idiag(0u); idiag < vec_size; idiag++) { res[idiag][idiag] *= scale[idiag]; }
			return res;
		}
		template<size_tc vec_size> static constexpr inline mat_tc make_coord(vec_tc_s<vec_size>& coord) {
			static_assert(size_x > 1u, "mat is too small for this operation");
			static_assert(vec_size <= size_y, "vec is too big for this mat");
			mat_t res(make_ident());
			for (v1u iside(0u); iside < vec_size; iside++) { res[size_x - 1u][iside] += coord[iside]; }
			return res;
		}
		static constexpr inline mat_tc make_rotat_x(cv1f degree) { // rotate around axis "x"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_MATH_COS(degree);
			cv1f sin_x = NW_MATH_SIN(degree);
			res[1][1] = +cos_x; res[1][2] = -sin_x;
			res[2][1] = +sin_x; res[2][2] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_y(cv1f degree) { // rotate around axis "y"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_MATH_COS(degree);
			cv1f sin_x = NW_MATH_SIN(degree);
			res[0][0] = +cos_x; res[0][2] = +sin_x;
			res[2][0] = -sin_x; res[2][2] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_z(cv1f degree) { // rotate around axis "z"
			static_assert(size_x >= 2u && size_y >= 2u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_MATH_COS(degree);
			cv1f sin_x = NW_MATH_SIN(degree);
			res[0][0] = +cos_x; res[0][1] = -sin_x;
			res[1][0] = +sin_x; res[1][1] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_xyz(vec_tc_s<3u>& degree_xyz) { // rotate around "x" "y" "z"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			/// i advice you not to change this order;
			/// we were suffering two weeks with "drunk" gfx_cam because of this;
			return make_rotat_y(degree_xyz[1]) * make_rotat_x(degree_xyz[0]) * make_rotat_z(degree_xyz[2]);
		}
		static constexpr inline mat_tc_xy<size_x - 1u, size_y - 1u> make_erase(mat_tc& mat, v1u erase_x, v1u erase_y) {
			mat_t_xy<size_x - 1u, size_y - 1u> res;
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					if (iy < erase_y) {
						if (ix < erase_x) { res[iy - 0u][ix - 0u] = mat[iy + 0u][ix + 0u]; }
						else if (ix > erase_x) { res[iy - 0u][ix - 1u] = mat[iy + 0u][ix + 0u]; }
					}
					else if (iy > erase_y) {
						if (ix < erase_x) { res[iy - 1u][ix - 0u] = mat[iy + 0u][ix + 0u]; }
						else if (ix > erase_x) { res[iy - 1u][ix - 1u] = mat[iy + 0u][ix + 0u]; }
					}
				}
			}
			return res;
		}
#	endif	// core_methods
	public:
		vec_t m_val[size_y];
	};
	template<typename tval, size_tc size_x, size_tc size_y>
	inline std::ostream& operator<<(std::ostream& stm, const t_mat<tval, size_x, size_y>& matrix) { return matrix.operator<<(stm); }
	template<typename tval, size_tc size_x, size_tc size_y>
	inline std::istream& operator>>(std::istream& stm, t_mat<tval, size_x, size_y>& matrix) { return matrix.operator>>(stm); }
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
#	define NW_INVOKER(tname, ITERATOR)     \
	ITERATOR(m2##tname, v1##tname, 2u, 2u) \
	ITERATOR(m3##tname, v1##tname, 3u, 3u) \
	ITERATOR(m4##tname, v1##tname, 4u, 4u) \
// that's it
#	define NW_ITERATOR(tname, vname, size_x, size_y)    \
	typedef t_mat<vname, size_x, size_y> tname;  \
	typedef const tname               c##tname;  \
// that's it
namespace NW { NW_FOREACH(NW_INVOKER, NW_ITERATOR); }
#	undef NW_ITERATOR
#	undef NW_FOREACH
#	undef NW_INVOKER
#	else
#		error "macroses named above must not be defined here"
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
#endif	// NW_API
#endif	// NW_MAT_MATRIX_H