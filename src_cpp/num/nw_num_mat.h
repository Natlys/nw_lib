#ifndef NW_NUM_MATRIX_H
#define NW_NUM_MATRIX_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../std/nw_std_func.h"
#	include "nw_num_val.h"
#	include "nw_num_vec.h"
namespace NW
{
	/// number_matrix struct
	template<typename tval, size_tc size_x, size_tc size_y = size_x>
	struct num_mat_t
	{ static_assert(size_x > 1u && size_y > 1u, "matrix must be greater than one value or a vec");
		// --value type
		using val_t = tval;
		using val_tc = const val_t;
		using vals_t = std::vector<val_t>;
		using vals_tc = const vals_t;
		using val_list_t = std::initializer_list<val_t>;
		using val_list_tc = const val_list_t;
		// --vector type
		using vec_t = num_vec_t<tval, size_y>;
		using vec_tc = const vec_t;
		using vecs_t = std::vector<vec_t>;
		using vecs_tc = const vecs_t;
		using vec_list_t = std::initializer_list<vec_t>;
		using vec_list_tc = const vec_list_t;
		template<size_tc vec_size>
		using d_vec_t = num_vec_t<tval, vec_size>;
		template<size_tc vec_size>
		using d_vec_tc = const d_vec_t<vec_size>;
		// --matrix type
		using mat_t = num_mat_t<tval, size_x, size_y>;
		using mat_tc = const mat_t;
		using mats_t = std::vector<mat_t>;
		using mats_tc = const mats_t;
		using mat_list_t = std::initializer_list<mat_t>;
		using mat_list_tc = const mat_list_t;
		// // --different type
		template<typename tname> using t_mat_t = num_mat_t<tname, size_x, size_y>;
		template<typename tname> using t_mat_tc = const t_mat_t<tname>;
		// // --different size
		template<size_tc mat_size_x, size_tc mat_size_y> using d_mat_t = num_mat_t<tval, mat_size_x, mat_size_y>;
		template<size_tc mat_size_x, size_tc mat_size_y> using d_mat_tc = const d_mat_t<mat_size_x, mat_size_y>;
	public:
		// --ctor_dtor
#	if(NW_TRUE)
		constexpr inline num_mat_t() : m_val{ NW_NULL } { memset(m_val, NW_NULL, sizeof(mat_t)); }
		constexpr inline num_mat_t(val_tc val) : num_mat_t() { operator=(val); }
		constexpr inline num_mat_t(vals_tc& vals) : num_mat_t() { operator=(vals); }
		constexpr inline num_mat_t(val_list_tc& vals) : num_mat_t() { operator=(vals); }
		constexpr inline num_mat_t(vec_tc& vec) : num_mat_t() { operator=(vec); }
		constexpr inline num_mat_t(vecs_tc& vecs) : num_mat_t() { operator=(vecs); }
		constexpr inline num_mat_t(vec_list_tc& vecs) : num_mat_t() { operator=(vecs); }
		constexpr inline num_mat_t(mat_tc& mat) : num_mat_t() { operator=(mat); }
		constexpr inline num_mat_t(mat_t&& mat) : num_mat_t() { operator=(mat); }
		template<typename tname> num_mat_t(t_mat_tc<tname>& mat) { operator=(mat); }
		template<typename tname> num_mat_t(t_mat_t<tname>&& mat) { operator=(mat); }
		template<size_tc mat_size_x, size_tc mat_size_y> num_mat_t(d_mat_tc<mat_size_x, mat_size_y>& mat) { operator=(mat); }
		template<size_tc mat_size_x, size_tc mat_size_y> num_mat_t(d_mat_t<mat_size_x, mat_size_y>&& mat) { operator=(mat); }
		inline ~num_mat_t() = default;
#	endif	// ctor_dtor
		// --getters
#	if (NW_TRUE)
		// // --info
		static constexpr inline size_tc get_size() { return size_x * size_y; }
		static constexpr inline size_tc get_size_x() { return size_x; }
		static constexpr inline size_tc get_size_y() { return size_y; }
		static constexpr inline size_tc get_size_min() { return size_x < size_y ? size_x : size_y; }
		static constexpr inline size_tc get_size_max() { return size_x > size_y ? size_x : size_y; }
		static constexpr inline size_tc get_rows() { return size_y; }
		static constexpr inline size_tc get_cols() { return size_x; }
		// // --value
		inline mat_tc get_add(val_tc val) const { return make_add(*this, val); }
		inline mat_tc get_sub(val_tc val) const { return make_sub(*this, val); }
		inline mat_tc get_mul(val_tc val) const { return make_mul(*this, val); }
		inline mat_tc get_div(val_tc val) const { return make_div(*this, val); }
		// // --vector
		inline vec_tc get_add(vec_tc& vec) const { return make_add(*this, vec); }
		inline vec_tc get_sub(vec_tc& vec) const { return make_sub(*this, vec); }
		inline vec_tc get_mul(vec_tc& vec) const { return make_mul(*this, vec); }
		inline vec_tc get_div(vec_tc& vec) const { return make_div(*this, vec); }
		// // --matrix
		inline mat_tc get_add(mat_tc& mat) const { return make_add(*this, mat); }
		inline mat_tc get_sub(mat_tc& mat) const { return make_sub(*this, mat); }
		inline mat_tc get_mul(mat_tc& mat) const { return make_mul(*this, mat); }
		inline mat_tc get_div(mat_tc& mat) const { return make_div(*this, mat); }
		inline mat_tc get_inver() { return make_inver(*this); }
		inline mat_tc get_trpos() { return make_trpos(*this); }
		template<size_tc vec_size> mat_tc get_scale(d_vec_tc<vec_size>& scale) const { return *this = make_scale(scale); }
		template<size_tc vec_size> mat_tc get_coord(d_vec_tc<vec_size>& coord) const { return *this * make_coord(coord); }
		inline mat_tc get_rotat_x(cv1f degree) const { return *this = make_rotat_x(degree); }
		inline mat_tc get_rotat_y(cv1f degree) const { return *this = make_rotat_y(degree); }
		inline mat_tc get_rotat_z(cv1f degree) const { return *this = make_rotat_z(degree); }
		inline mat_tc get_rotat_xyz(cv3f degree_xyz) const { return *this * make_rotat_xyz(degree_xyz); }
		inline d_mat_tc<size_x - 1u, size_y - 1u> get_erase(v1u erase_x, v1u erase_y) const { return make_erase(*this, erase_x, erase_y); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
		// // --value
		inline mat_t& set_add(val_tc val) { return *this = get_add(val); }
		inline mat_t& set_sub(val_tc val) { return *this = get_sub(val); }
		inline mat_t& set_mul(val_tc val) { return *this = get_mul(val); }
		inline mat_t& set_div(val_tc val) { return *this = get_div(val); }
		// // --vector
		inline mat_t& set_add(vec_tc& vec) { return *this = get_add(vec); }
		inline mat_t& set_sub(vec_tc& vec) { return *this = get_sub(vec); }
		inline mat_t& set_mul(vec_tc& vec) { return *this = get_mul(vec); }
		inline mat_t& set_div(vec_tc& vec) { return *this = get_div(vec); }
		// // --matrix
		inline mat_t& set_add(mat_tc& mat) { return *this = get_add(mat); }
		inline mat_t& set_sub(mat_tc& mat) { return *this = get_sub(mat); }
		inline mat_t& set_mul(mat_tc& mat) { return *this = get_mul(mat); }
		inline mat_t& set_div(mat_tc& mat) { return *this = get_div(mat); }
		inline mat_t& set_ident(val_tc val = NW_UNIT) { return *this = make_ident(val); }
		inline mat_t& set_inver() { return *this = get_inver(); }
		inline mat_t& set_trpos() { return *this = get_trpos(); }
		template<size_tc vec_size> mat_t& set_scale(d_vec_tc<vec_size>& scale) { return *this = get_scale(scale); }
		template<size_tc vec_size> mat_t& set_coord(d_vec_tc<vec_size>& coord) { return *this = get_coord(coord); }
		inline mat_t& set_rotat_x(cv1f degree) { return *this = get_rotat_x(degree); }
		inline mat_t& set_rotat_y(cv1f degree) { return *this = get_rotat_y(degree); }
		inline mat_t& set_rotat_z(cv1f degree) { return *this = get_rotat_z(degree); }
		inline mat_t& set_rotat_xyz(cv3f degree) { return *this = get_rotat_xyz(degree); }
#	endif	// setters
		// --operators
#	if (NW_TRUE)
		// // --math
#		if (NW_TRUE)
		// // // --value
		inline mat_tc operator+(val_tc val) const { return get_add(val); }
		inline mat_tc operator-(val_tc val) const { return get_add(val); }
		inline mat_tc operator*(val_tc val) const { return get_add(val); }
		inline mat_tc operator/(val_tc val) const { return get_add(val); }
		inline mat_t& operator+=(val_tc val) { return *this = get_add(val); }
		inline mat_t& operator-=(val_tc val) { return *this = get_sub(val); }
		inline mat_t& operator*=(val_tc val) { return *this = get_mul(val); }
		inline mat_t& operator/=(val_tc val) { return *this = get_div(val); }
		// // // --vector
		inline vec_tc operator+(vec_tc& vec) const { return get_add(vec); }
		inline vec_tc operator-(vec_tc& vec) const { return get_sub(vec); }
		inline vec_tc operator*(vec_tc& vec) const { return get_mul(vec); }
		inline vec_tc operator/(vec_tc& vec) const { return get_div(vec); }
		// // // --matrix
		inline mat_tc operator+(mat_tc& mat) const { return get_add(mat); }
		inline mat_tc operator-(mat_tc& mat) const { return get_sub(mat); }
		inline mat_tc operator*(mat_tc& mat) const { return get_mul(mat); }
		inline mat_tc operator/(mat_tc& mat) const { return get_div(mat); }
		inline mat_t& operator+=(mat_tc& mat) { return *this = get_add(mat) }
		inline mat_t& operator-=(mat_tc& mat) { return *this = get_sub(mat); }
		inline mat_t& operator*=(mat_tc& mat) { return *this = get_mul(mat); }
		inline mat_t& operator/=(mat_tc& mat) { return *this = get_div(mat); }
#		endif	// --math
		// // --assignment
#		if (NW_TRUE)
		// // --value
		inline mat_t& operator=(val_tc& val) { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { m_val[iy][ix] = val; } } return *this; }
		inline mat_t& operator=(vals_tc& vals) { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } return *this; }
		inline mat_t& operator=(val_list_tc& vals) { for (v1u ix(0u); ix < vals.size() / size_x; ix++) { m_val[ix / size_x][ix % size_x] = vals[ix]; } return *this; }
		// // --vector
		inline mat_t& operator=(vec_tc& vec) { for (v1u iy(0u); iy < size_y; iy++) { m_val[iy] = vec; } return *this; }
		inline mat_t& operator=(vecs_tc& vecs) { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } return *this; }
		inline mat_t& operator=(vec_list_tc& vecs) { for (v1u iy(0u); iy < vecs.size(); iy++) { m_val[iy] = vecs[iy]; } return *this; }
		// // --matrix
		inline mat_t& operator=(mat_tc& mat) { memcpy(m_val, mat.m_val, sizeof(mat_t)); return *this; }
		inline mat_t& operator=(mat_t&& mat) { memmove(m_val, mat.m_val, sizeof(mat_t)); return *this; }
		template<typename tname> mat_t& operator=(t_mat_tc<tname>& mat) { for (v1u iy(0u); iy < size_y; iy++) { m_val[iy] = mat[iy]; } return *this; }
		template<typename tname> mat_t& operator=(t_mat_t<tname>&& mat) { for (v1u iy(0u); iy < size_y; iy++) { m_val[iy] = mat[iy]; } return *this; }
		template<size_tc sz_x, size_tc sz_y> mat_t& operator=(d_mat_tc<sz_x, sz_y>& mat) { for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) { m_val[iy] = mat[iy]; } return *this; }
		template<size_tc sz_x, size_tc sz_y> mat_t& operator=(d_mat_t<sz_x, sz_y>&& mat) { for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) { m_val[iy] = mat[iy]; } return *this; }
#		endif	// assignment
		// // --convertion
#		if (NW_TRUE)
		// // --value
		//inline operator val_t&()        { return m_val[0][0]; }
		//inline operator val_tc&() const { return m_val[0][0]; }
		// // --vector
		//inline operator vec_t&()        { return m_val[0]; }
		//inline operator vec_tc&() const { return m_val[0]; }
		// // --matrix
		template<size_tc sz_x, size_tc sz_y> operator d_mat_t<sz_x, sz_y>() const { return make_mat<sz_x, sz_y>(*this); }
#		endif	// convertion
		// // --logic
#		if (NW_TRUE)
		// // --value
		inline v1bit operator==(val_tc& val) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] != val) { return NW_FALSE; } } } return NW_TRUE; }
		inline v1bit operator!=(val_tc& val) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] == val) { return NW_FALSE; } } } return NW_TRUE; }
		// // --vector
		inline v1bit operator==(vec_tc& vec) const { for (v1u iy(0u); iy < size_y; iy++) { if (m_val[iy] != vec) { return NW_FALSE; } } return NW_TRUE; }
		inline v1bit operator!=(vec_tc& vec) const { for (v1u iy(0u); iy < size_y; iy++) { if (m_val[iy] == vec) { return NW_FALSE; } } return NW_TRUE; }
		// // --matrix
		inline v1bit operator==(mat_tc& mat) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] != mat[iy][ix]) { return NW_FALSE; } } } return NW_TRUE; }
		inline v1bit operator!=(mat_tc& mat) const { for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { if (m_val[iy][ix] == mat[iy][ix]) { return NW_FALSE; } } } return NW_TRUE; }
#		endif	// logic
		// // --accessors
#		if (NW_TRUE)
		// // --value
		inline val_t& operator()(cv1u iy, cv1u ix)        { return m_val[iy][ix]; }
		inline val_tc& operator()(cv1u iy, cv1u ix) const { return m_val[iy][ix]; }
		// // --vector
		inline val_t& operator()(cv1u iy)        { return m_val[iy]; }
		inline val_tc& operator()(cv1u iy) const { return m_val[iy]; }
		inline vec_t& operator[](cv1u iy)        { return m_val[iy]; }
		inline vec_tc& operator[](cv1u iy) const { return m_val[iy]; }
#		endif	// accessors
		// // --input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const { for (v1u ix(0u); ix < size_x; ix++) { stm << m_val[ix] << NW_STR_EOL; } return stm; }
		inline std::istream& operator>>(std::istream& stm) { for (v1u ix(0u); ix < size_x; ix++) { stm >> m_val[ix]; stm.get(); } return stm; }
#		endif	// input_output
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		// // --value
		static constexpr inline mat_tc make_add(mat_tc& mat, val_tc val) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[iy][ix] + val; }
			}
			return res;
		}
		static constexpr inline mat_tc make_sub(mat_tc& mat, val_tc val) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[iy][ix] - val; }
			}
			return res;
		}
		static constexpr inline mat_tc make_mul(mat_tc& mat, val_tc val) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[iy][ix] * val; }
			}
			return res;
		}
		static constexpr inline mat_tc make_div(mat_tc& mat, val_tc val) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[iy][ix] / val; }
			}
			return res;
		}
		// // --vector
		static constexpr inline vec_tc make_add(mat_tc& mat, vec_tc& vec) {
			vec_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy] += mat[iy][ix] + vec[ix]; }
			}
			return res;
		}
		static constexpr inline vec_tc make_sub(mat_tc& mat, vec_tc& vec) {
			vec_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy] += mat[iy][ix] - vec[ix]; }
			}
			return res;
		}
		static constexpr inline vec_tc make_mul(mat_tc& mat, vec_tc& vec) {
			vec_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy] += mat[iy][ix] * vec[ix]; }
			}
			return res;
		}
		static constexpr inline vec_tc make_div(mat_tc& mat, vec_tc& vec) {
			vec_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy] += mat[iy][ix] / vec[ix]; }
			}
			return res;
		}
		// // --matrix
		static constexpr inline mat_tc make_add(mat_tc& mat0, mat_tc& mat1) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat0[iy][ix] + mat1[iy][ix]; }
			}
			return res;
		}
		static constexpr inline mat_tc make_sub(mat_tc& mat0, mat_tc& mat1) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat0[iy][ix] - mat1[iy][ix]; }
			}
			return res;
		}
		static constexpr inline mat_tc make_mul(mat_tc& mat0, mat_tc& mat1) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					for (v1u iz(0u); iz < size_y; iz++) { res[iy][ix] += mat0[iy][iz] * mat1[iz][ix]; }
				}
			}
			return res;
		}
		static constexpr inline mat_tc make_div(mat_tc& mat0, mat_tc& mat1) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					for (v1u iz(0u); iz < size_y; iz++) { res[iy][ix] += mat0[iy][iz] / mat1[iz][ix]; }
				}
			}
			return res;
		}
		template<size_tc sz_x, size_tc sz_y> static constexpr d_mat_tc<sz_x, sz_y> make_add(mat_tc& mat0, d_mat_tc<sz_x, sz_y>& mat1) {
			d_mat_t<sz_x, size_y> res(NW_NULL);
			for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) {
				for (v1u ix(0u); ix < NW_NUM_MIN(sz_x, size_x); ix++) { res[iy][ix] += mat0[iy][ix] + mat1[iy][ix]; }
			}
			return res;
		}
		template<size_tc sz_x, size_tc sz_y> static constexpr d_mat_tc<sz_x, sz_y> make_sub(mat_tc& mat0, d_mat_tc<sz_x, sz_y>& mat1) {
			d_mat_t<sz_x, size_y> res(NW_NULL);
			for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) {
				for (v1u ix(0u); ix < NW_NUM_MIN(sz_x, size_x); ix++) { res[iy][ix] += mat0[iy][ix] - mat1[iy][ix]; }
			}
			return res;
		}
		template<size_tc sz_x> static constexpr d_mat_tc<sz_x, size_x> make_mul(mat_tc& mat0, d_mat_tc<sz_x, size_x>& mat1) {
			d_mat_t<sz_x, size_y> res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					for (v1u iz(0u); iz < sz_x; iz++) { res[iy][ix] += mat0[iy][iz] * mat1[iz][ix]; }
				}
			}
			return res;
		}
		template<size_tc sz_x> static constexpr d_mat_tc<sz_x, size_x> make_div(mat_tc& mat0, d_mat_tc<sz_x, size_x>& mat1) {
			d_mat_t<sz_x, size_y> res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					for (v1u iz(0u); iz < sz_x; iz++) { res[iy][ix] += mat0[iy][iz] / mat1[iz][ix]; }
				}
			}
			return res;
		}
		template<size_tc sz_x, size_tc sz_y> static constexpr d_mat_tc<sz_x, sz_y> make_mat(mat_tc& mat) {
			d_mat_t<sz_x, sz_y> res(NW_NULL);
			for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) {
				for (v1u ix(0u); ix < NW_NUM_MIN(sz_x, size_x); ix++) { res[iy][ix] = mat[iy][ix]; }
			}
			return res;
		}
		template<size_tc sz_x, size_tc sz_y> static constexpr d_mat_tc<sz_x, sz_y> make_mat(mat_tc&& mat) {
			d_mat_t<sz_x, sz_y> res(NW_NULL);
			for (v1u iy(0u); iy < NW_NUM_MIN(sz_y, size_y); iy++) {
				for (v1u ix(0u); ix < NW_NUM_MIN(sz_x, size_x); ix++) { res[iy][ix] = mat[iy][ix]; }
			}
			return res;
		}
		static constexpr inline mat_tc make_ident(val_tc diag = NW_UNIT) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square mat");
			mat_t res(NW_NULL);
			for (v1u idiag(0u); idiag < get_size_max(); idiag++) { res[idiag][idiag] = diag; }
			return res;
		}
		static constexpr inline mat_tc make_trpos(mat_tc& mat) {
			mat_t res(NW_NULL);
			for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = mat[ix][iy]; } }
			return res;
		}
		static constexpr inline mat_tc make_inver(mat_tc& mat) {
			static_assert(size_x == size_y, "not square mat cannot be inversed!");
			static_assert(NW_FALSE, "the function is not ready!");
			mat_t res(make_ident());
			return res;
		}
		template<size_tc vec_size> static constexpr inline mat_tc make_scale(d_vec_tc<vec_size>& scale) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square mat");
			static_assert(vec_size <= get_size_min(), "diagonal is too big for this mat");
			mat_t res(make_ident());
			for (v1u idiag(0u); idiag < vec_size; idiag++) { res[idiag][idiag] *= scale[idiag]; }
			return res;
		}
		template<size_tc vec_size> static constexpr inline mat_tc make_coord(d_vec_tc<vec_size>& coord) {
			static_assert(size_x > 1u, "mat is too small for this operation");
			static_assert(vec_size <= size_y, "vec is too big for this mat");
			mat_t res(make_ident());
			for (v1u iside(0u); iside < vec_size; iside++) { res[size_x - 1u][iside] += coord[iside]; }
			return res;
		}
		static constexpr inline mat_tc make_rotat_x(cv1f degree) { // rotate around axis "x"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_NUM_COS(degree);
			cv1f sin_x = NW_NUM_SIN(degree);
			res[1][1] = +cos_x; res[1][2] = -sin_x;
			res[2][1] = +sin_x; res[2][2] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_y(cv1f degree) { // rotate around axis "y"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_NUM_COS(degree);
			cv1f sin_x = NW_NUM_SIN(degree);
			res[0][0] = +cos_x; res[0][2] = +sin_x;
			res[2][0] = -sin_x; res[2][2] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_z(cv1f degree) { // rotate around axis "z"
			static_assert(size_x >= 2u && size_y >= 2u, "mat size is too small for this operation");
			mat_t res(make_ident());
			cv1f cos_x = NW_NUM_COS(degree);
			cv1f sin_x = NW_NUM_SIN(degree);
			res[0][0] = +cos_x; res[0][1] = -sin_x;
			res[1][0] = +sin_x; res[1][1] = +cos_x;
			return res;
		}
		static constexpr inline mat_tc make_rotat_xyz(cv3f& degree_xyz) { // rotate around "x" "y" "z"
			static_assert(size_x >= 3u && size_y >= 3u, "mat size is too small for this operation");
			/// i advice you not to change this order;
			/// we were suffering two weeks with "drunk" gfx_tform_cam because of this;
			return make_rotat_y(degree_xyz[1]) * make_rotat_x(degree_xyz[0]) * make_rotat_z(degree_xyz[2]);
		}
		static constexpr inline d_mat_tc<size_x - 1u, size_y - 1u> make_erase(mat_tc& mat, v1u erase_x, v1u erase_y) {
			d_mat_t<size_x - 1u, size_y - 1u> res;
			for (v1u iy(0u); iy < size_y; iy++) {
				for (v1u ix(0u); ix < size_x; ix++) {
					if (iy < erase_y) {
						if (ix < erase_x) { res[iy - 0u][ix - 0u] = mat[iy + 0u][ix + 0u]; }
						if (ix > erase_x) { res[iy - 0u][ix - 1u] = mat[iy + 0u][ix + 0u]; }
					}
					if (iy > erase_y) {
						if (ix < erase_x) { res[iy - 1u][ix - 0u] = mat[iy + 0u][ix + 0u]; }
						if (ix > erase_x) { res[iy - 1u][ix - 1u] = mat[iy + 0u][ix + 0u]; }
					}
				}
			}
			return res;
		}
		static constexpr inline mat_tc make_pows(val_tc first, cv1f power) {
			mat_t res(first);
			for (v1u iy(0u); iy < get_size_y(); iy++) {
				for (v1u ix(0u); ix < get_size_x(); ix++) {
					res[iy][ix] = NW_NUM_POW(NW_CAST_FLOAT(res[iy][ix]), NW_CAST_FLOAT(power));
				}
			}
			return res;
		}
		static constexpr inline mat_tc make_rand(val_tc vmin, val_tc vmax) {
			mat_t res(first);
			for (v1u iy(0u); iy < get_size_y(); iy++) { res[iy] = vec_t::make_rand(vmin, vmax); }
			return res;
		}
		static constexpr inline mat_tc apply_all(mat_tc& mat, func_tc<vec_tc(val_tc& val)>& func) {
			mat_t res;
			for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = func(mat[iy][ix]); } }
			return res;
		}
		static constexpr inline mat_tc apply_all(mat_tc& mat, func_tc<vec_tc(vec_tc& vec, cv1u iy)>& func) {
			mat_t res;
			for (v1u iy(0u); iy < size_y; iy++) { mat[iy] = func(mat[iy], iy); }
			return res;
		}
		static constexpr inline mat_tc apply_all(mat_tc& mat, func_tc<val_tc(val_tc& val, cv1u iy, cv1u ix)>& func) {
			mat_t res;
			for (v1u iy(0u); iy < size_y; iy++) { for (v1u ix(0u); ix < size_x; ix++) { res[iy][ix] = func(mat[iy][ix], iy, ix); } }
			return res;
		}
		inline mat_t& apply_all(func_tc<val_tc(val_tc& val)>& func) { return *this = apply_all(*this, func); }
		inline mat_t& apply_all(func_tc<val_tc(vec_tc& vec, cv1u iy)>& func) { return *this = apply_all(*this, func); }
		inline mat_t& apply_all(func_tc<val_tc(val_tc& val, cv1u iy, cv1u ix)>& func) { return *this = apply_all(*this, func); }
#	endif	// core_methods
	public:
		vec_t m_val[size_y];
	};
	// --typedefs
	template<typename tval, size_tc size_x, size_tc size_y> using num_mat_tc = const num_mat_t<tval, size_x, size_y>;
	// --mathematics
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator+(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator+(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator-(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator-(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator*(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator*(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator/(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator/(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator+=(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator+=(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator-=(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator-=(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator*=(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator*=(val); }
	template<typename tname, typename tval, size_tc size_x, size_tc size_y> num_mat_tc<tval, size_x, size_y> operator/=(tname val, num_mat_tc<tval, size_x, size_y> mat) { return mat.operator/=(val); }
	// --input_output
	template<typename tval, size_tc size_x, size_tc size_y>
	inline std::ostream& operator<<(std::ostream& stm, const num_mat_t<tval, size_x, size_y>& matrix) { return matrix.operator<<(stm); }
	template<typename tval, size_tc size_x, size_tc size_y>
	inline std::istream& operator>>(std::istream& stm, num_mat_t<tval, size_x, size_y>& matrix) { return matrix.operator>>(stm); }
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
	typedef num_mat_t<vname, size_x, size_y> tname;  \
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