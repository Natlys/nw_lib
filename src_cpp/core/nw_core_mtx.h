#ifndef NW_CORE_MATRIX_H
#define NW_CORE_MATRIX_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	/// value matrix struct template
	template<typename vtype, cv1u size_x, cv1u size_y = size_x>
	struct t_mat
	{
		static_assert(size_x > 1u && size_y > 1u, "matrix must be greater than one value or a vector");
		// value type
		using val_t = vtype;
		using val_tc = const val_t;
		// vector type
		using vec_t = t_vec<vtype, size_y>;
		using vec_tc = const vec_t;
		template<cv1u vec_size>
		using vec_t_s = t_vec<vtype, vec_size>;
		template<cv1u vec_size>
		using vec_tc_s = const vec_t_s<vec_size>;
		// matrix type
		using mat_t = t_mat<vtype, size_x, size_y>;
		using mat_tc = const mat_t;
		// // same vtype, same size_y
		template<cv1u mat_size_x>
		using mat_t_x = t_mat<vtype, mat_size_x, size_y>;
		template<cv1u mat_size_x>
		// // same vtype, same size_x
		using mat_tc_x = const mat_t_x<mat_size_x>;
		template<cv1u mat_size_y>
		using mat_t_y = t_mat<vtype, size_x, mat_size_y>;
		template<cv1u mat_size_y>
		using mat_tc_y = const mat_t_y<mat_size_y>;
		// // same vtype
		template<cv1u mat_size_x, cv1u mat_size_y>
		using mat_t_xy = NW::t_mat<vtype, mat_size_x, mat_size_y>;
		template<cv1u mat_size_x, cv1u mat_size_y>
		using mat_tc_xy = const mat_t_xy<mat_size_x, mat_size_y>;
		// // same vtype, square size
		template<cv1u mat_size_xy>
		using mat_t_s = t_mat<vtype, mat_size_xy, mat_size_xy>;
		template<cv1u mat_size_xy>
		using mat_tc_s = const mat_t_s<mat_size_xy>;
	public:
		constexpr inline t_mat(val_tc& value = static_cast<val_t>(0)) : elems{ value }
		{
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = value;
				}
			}
		}
		constexpr inline t_mat(const std::initializer_list<val_t>& value) : t_mat()
		{
			for (v1u iy = 0u; iy < value.size() / size_y; iy++) {
				for (v1u ix = 0u; ix < value.size() % size_x; ix++) {
					this->elems[iy][ix] = *(value.begin() + NW_XY_TO_X(ix, iy, size_x));
				}
			}
		}
		constexpr inline t_mat(mat_tc& cpy) = default;
		constexpr inline t_mat(mat_t&& cpy) = default;
		inline ~t_mat() = default;
		// --getters
#	if (NW_TRUE)
		static constexpr inline cv1u get_size() { return size_x * size_y; }
		static constexpr inline cv1u get_size_x() { return size_x; }
		static constexpr inline cv1u get_size_y() { return size_y; }
		static constexpr inline cv1u get_size_min() { return size_x < size_y ? size_x : size_y; }
		static constexpr inline cv1u get_size_max() { return size_x > size_y ? size_x : size_y; }
		static constexpr inline cv1u get_rows() { return size_y; }
		static constexpr inline cv1u get_cols() { return size_x; }
#	endif
		// --operators
		// math
#	if (NW_TRUE)
		// // matrix - value
#		if (NW_TRUE)
		inline mat_tc operator+(val_tc& value) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] + value;
				}
			}
			return result;
		}
		inline mat_tc operator-(val_tc& value) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] - value;
				}
			}
			return result;
		}
		inline mat_tc operator*(val_tc& value) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] * value;
				}
			}
			return result;
		}
		inline mat_tc operator/(val_tc& value) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] / value;
				}
			}
			return result;
		}
		inline t_mat& operator+=(val_tc& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] += value;
				}
			}
			return *this;
		}
		inline t_mat& operator-=(val_tc& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] -= value;
				}
			}
			return *this;
		}
		inline t_mat& operator*=(val_tc& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] *= value;
				}
			}
			return *this;
		}
		inline t_mat& operator/=(val_tc& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] /= value;
				}
			}
			return *this;
		}
		inline t_mat& operator=(val_tc& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = value;
				}
			}
			return *this;
		}
#		endif
		// // matrix - vector
#		if (NW_TRUE)
		inline vec_tc operator*(vec_tc& vector) const {
			vec_tc result(static_cast<val_t>(0));
			for (v1u iy; iy < size_x; iy++) {
				for (v1u itr; itr < size_x; itr++) {
					result[iy] += this->elems[iy][itr] * vector[itr];
				}
			}
		}
#		endif
		// // matrix - matrix
#		if (NW_TRUE)
		inline mat_tc operator+(mat_tc& matrix) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] + matrix[iy][ix];
				}
			}
			return result;
		}
		inline mat_tc operator-(mat_tc& matrix) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] - matrix[iy][ix];
				}
			}
			return result;
		}
		inline mat_tc operator*(mat_tc& matrix) const {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					for (v1u itr = 0u; itr < size_x; itr++) {
						result[iy][ix] += this->elems[iy][itr] * matrix[itr][ix];
					}
				}
			}
			return result;
		}
		inline t_mat& operator+=(mat_tc& matrix) {
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					this->elems[iy][ix] += matrix[iy][ix];
				}
			}
			return *this;
		}
		inline t_mat& operator-=(mat_tc& matrix) {
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					this->elems[iy][ix] -= matrix[iy][ix];
				}
			}
			return *this;
		}
		inline t_mat& operator*=(mat_tc& matrix) {
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					for (v1u itr = 0u; itr < size_x; itr++) {
						this->elems[iy][ix] += this->elems[iy][itr] * matrix[itr][ix];
					}
				}
			}
			return *this;
		}
		inline t_mat& operator=(mat_tc& matrix) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = matrix[iy][ix];
				}
			}
			return *this;
		}
#		endif
		// logic
		// accessors
#		if (NW_TRUE)
		inline vec_t& operator[](cv1u idx)        { return this->elems[idx]; }
		inline vec_tc& operator[](cv1u idx) const { return this->elems[idx]; }
#		endif
		// input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const {
			for (v1u ix = 0u; ix < size_x; ix++) {
				stm << this->elems[ix] << NW_STR_EOL;
			}
			return stm;
		}
		inline std::istream& operator>>(std::istream& stm) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				stm >> this->elems[ix];
				stm.get();
			}
			return stm;
		}
#		endif
#	endif
		// --core_methods
#	if (NW_TRUE)
		static constexpr inline mat_tc make_ident(vtype value = static_cast<vtype>(1)) {
			mat_t result(static_cast<vtype>(0));
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			for (v1u idiag = 0u; idiag < get_size_max(); idiag++) {
				result[idiag][idiag] = value;
			}
			return result;
		}
		static constexpr inline mat_tc make_trpos(mat_tc& matrix) {
			mat_t result(static_cast<val_t>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = matrix[ix][iy];
				}
			}
			return result;
		}
		static constexpr inline mat_tc make_inver(mat_tc& matrix) {
			static_assert(size_x == size_y, "not square matrix cannot be inversed!");
			static_assert(NW_FALSE, "the function is not ready!");
			return mat_t();
#			if (NW_FALSE)
			mat_t_xy<size_x, size_y * 2> result(static_cast<val_t>(0));
			for (v1u iy = 0; iy < size_y; iy++) {
				for (v1u ix = 0; ix < size_x; ix++) {
					result[iy][ix] = matrix[iy][ix];
				}
				result[iy][iy + size_y] = static_cast<val_t>(1);
			}
			{
				for (v1u iy = 0u, ix = 0u; iy < size_y && ix < size_x; iy++, ix++) {
					v1u itr = iy;
					while (result[iy][ix] == static_cast<val_t>(0)) {
						if (itr == size_y) {
							itr = iy;
							if (ix++ == size_x) { return matrix; }
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
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					inversed[iy][ix] = result[iy][ix + size_y];
				}
			}
			return inversed;
#			endif
		}
		template<cv1u diag_size>
		static constexpr inline mat_tc make_scale(vec_tc_s<diag_size>& diagonal) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			static_assert(diag_size <= get_size_min(), "diagonal is too big for this matrix");
			
			mat_t result = make_ident();
			for (v1u idiag = 0u; idiag < diag_size; idiag++) {
				result[idiag][idiag] *= diagonal[idiag];
			}

			return result;
		}
		template<cv1u vec_size>
		static constexpr inline mat_tc make_coord(vec_tc_s<vec_size>& vector) {
			static_assert(size_x > 1u, "matrix is too small for this operation");
			static_assert(vec_size <= size_y, "vector is too big for this matrix");
			
			mat_t result = make_ident();
			for (v1u itr = 0u; itr < vec_size; itr++) {
				result[size_x - 1u][itr] += vector[itr];
			}

			return result;
		}
		static constexpr inline mat_tc make_rotat_x(cv1f& value) { // rotate around axis "x"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");

			mat_t result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[1][1] = +cos_x; result[1][2] = -sin_x;
			result[2][1] = +sin_x; result[2][2] = +cos_x;

			return result;
		}
		static constexpr inline mat_tc make_rotat_y(cv1f& value) { // rotate around axis "y"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");

			mat_t result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[0][0] = +cos_x; result[0][2] = +sin_x;
			result[2][0] = -sin_x; result[2][2] = +cos_x;

			return result;
		}
		static constexpr inline mat_tc make_rotat_z(cv1f& value) { // rotate around axis "z"
			static_assert(size_x >= 2u && size_y >= 2u, "matrix size is too small for this operation");

			mat_t result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[0][0] = +cos_x; result[0][1] = -sin_x;
			result[1][0] = +sin_x; result[1][1] = +cos_x;

			return result;
		}
		static constexpr inline mat_tc make_rotat_xyz(vec_tc_s<3u>& vector) { // rotate around "x" "y" "z"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");
			/// i advice you not to change this order;
			/// we were suffering two weeks with "drunk" gfx_cam because of this;
			return make_rotat_y(vector[1]) * make_rotat_x(vector[0]) * make_rotat_z(vector[2]);
		}
		static constexpr inline mat_tc_xy<size_x - 1u, size_y - 1u> make_erase(mat_tc& matrix, v1u erase_x, v1u erase_y) {
			mat_t_xy<size_x - 1u, size_y - 1u> result(static_cast<vtype>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					if (iy < erase_y) {
						if (ix < erase_x) {
							result[iy - 0u][ix - 0u] = matrix[iy + 0u][ix + 0u];
						}
						else if (ix > erase_x) {
							result[iy - 0u][ix - 1u] = matrix[iy + 0u][ix + 0u];
						}
					}
					else if (iy > erase_y) {
						if (ix < erase_x) {
							result[iy - 1u][ix - 0u] = matrix[iy + 0u][ix + 0u];
						}
						else if (ix > erase_x) {
							result[iy - 1u][ix - 1u] = matrix[iy + 0u][ix + 0u];
						}
					}
				}
			}
			return result;
		}
		inline t_mat& ident(v1f value) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix!");
			for (v1u idiag = 0u; idiag < get_size_max(); idiag++) {
				this->elems[idiag][idiag] = value;
			}
			return *this;
		}
		inline t_mat& inver() {
			static_assert(size_x == size_y, "not square matrix cannot be inversed!");
			static_assert(false, "the function is not ready!");
			
			return *this;
		}
		inline t_mat& trpos() {
			mat_t temp(*this);
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = temp[ix][iy];
				}
			}
			return *this;
		}
		template<cv1u vec_size>
		inline t_mat& scale(vec_tc_s<vec_size>& vector) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix!");
			static_assert(vec_size <= size_y, "vector size is too big for this operation!");
			for (v1u idiag = 0u; idiag < vec_size; idiag++) {
				this->elems[idiag][idiag] *= value;
			}
			return *this;
		}
		template<cv1u vec_size>
		inline t_mat& coord(vec_tc_s<vec_size>& vector) {
			static_assert(size_x > 1u, "matrix size is too small for this operation!");
			static_assert(vec_size <= size_y, "vector size is too big for this operation!");
			for (v1u itr = 0u; itr < vec_size; itr++) {
				this->elems[size_x - 1u][itr] += vector[itr];
			}
			return *this;
		}
		inline mat_tc_xy<size_x - 1u, size_y - 1u> erase(v1u erase_x, v1u erase_y) const { return make_erase(*this, erase_x, erase_y); }
#	endif
	public:
		vec_t elems[size_y];
	};
}
#	if (defined NW_FOREACH || defined NW_INVOKER || defined NW_ITERATOR)
#		error "macroses named above must not be defined here"
#	else
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
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
namespace NW
{
#	define NW_ITERATOR(tname, vname, size_x, size_y)    \
	typedef t_mat<vname, size_x, size_y> tname;  \
	typedef const tname               c##tname;  \
// that's it
	NW_FOREACH(NW_INVOKER, NW_ITERATOR);
#	undef NW_ITERATOR
}
#	undef NW_FOREACH
#	undef NW_INVOKER
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_MATRIX_H