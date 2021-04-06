#ifndef NW_CORE_MATRIX_H
#define NW_CORE_MATRIX_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	/// value matrix struct template
	template<typename vtype, csize size_x, csize size_y = size_x>
	struct mat_t
	{
		static_assert(size_x > 1u && size_y > 1u, "matrix must be greater than one value or a vector");
		// value type
		using val = vtype;
		using cval = const val;
		using vec = vec_t<vtype, size_y>;
		using cvec = const vec;
		// vector type
		template<csize vec_size>
		using vec_s = vec_t<vtype, vec_size>;
		template<csize vec_size>
		using cvec_s = const vec_s<vec_size>;
		// matrix type
		using mat = mat_t<vtype, size_x, size_y>;
		using cmat = const mat;
		// // same vtype, same size_y
		template<csize mat_size_x>
		using mat_x = mat_t<vtype, mat_size_x, size_y>;
		template<csize mat_size_x>
		using cmat_x = const mat_x<mat_size_x>;
		// // same vtype, same size_x
		template<csize mat_size_y>
		using mat_y = mat_t<vtype, size_x, mat_size_y>;
		template<csize mat_size_y>
		using cmat_y = const mat_y<mat_size_y>;
		// // same vtype
		template<csize mat_size_x, csize mat_size_y>
		using mat_xy = mat_t<vtype, mat_size_x, mat_size_y>;
		template<csize mat_size_x, csize mat_size_y>
		using cmat_xy = const mat_xy<mat_size_x, mat_size_y>;
		// // same vtype, square size
		template<csize mat_size_xy>
		using mat_s = mat_t<vtype, mat_size_xy, mat_size_xy>;
		template<csize mat_size_xy>
		using cmat_s = const mat_s<mat_size_xy>;
	public:
		constexpr inline mat_t(cval& value = static_cast<val>(0)) : elems{ value }
		{
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = value;
				}
			}
		}
		constexpr inline mat_t(const std::initializer_list<val>& value) : mat_t()
		{
			for (v1u iy = 0u; iy < value.size() / size_y; iy++) {
				for (v1u ix = 0u; ix < value.size() % size_x; ix++) {
					this->elems[iy][ix] = *(value.begin() + NW_XY_TO_X(ix, iy, size_x));
				}
			}
		}
		constexpr inline mat_t(cmat& cpy) = default;
		constexpr inline mat_t(mat&& cpy) = default;
		inline ~mat_t() = default;
		// --getters
#	if (1)
		static constexpr inline csize get_size() { return size_x * size_y; }
		static constexpr inline csize get_size_x() { return size_x; }
		static constexpr inline csize get_size_y() { return size_y; }
		static constexpr inline csize get_size_min() { return size_x < size_y ? size_x : size_y; }
		static constexpr inline csize get_size_max() { return size_x > size_y ? size_x : size_y; }
		static constexpr inline csize get_rows() { return size_y; }
		static constexpr inline csize get_cols() { return size_x; }
#	endif
		// --operators
		// math
#	if (1)
		// // matrix - value
#		if (1)
		inline cmat operator+(cval& value) const {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] + value;
				}
			}
			return result;
		}
		inline cmat operator-(cval& value) const {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] - value;
				}
			}
			return result;
		}
		inline cmat operator*(cval& value) const {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] * value;
				}
			}
			return result;
		}
		inline cmat operator/(cval& value) const {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] / value;
				}
			}
			return result;
		}
		inline mat& operator+=(cval& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] += value;
				}
			}
			return *this;
		}
		inline mat& operator-=(cval& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] -= value;
				}
			}
			return *this;
		}
		inline mat& operator*=(cval& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] *= value;
				}
			}
			return *this;
		}
		inline mat& operator/=(cval& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] /= value;
				}
			}
			return *this;
		}
		inline mat& operator=(cval& value) {
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = value;
				}
			}
			return *this;
		}
#		endif
		// // matrix - vector
#		if (1)
		inline cvec operator*(cvec& vector) const {
			cvec result(static_cast<val>(0));
			for (v1u iy; iy < size_x; iy++) {
				for (v1u itr; itr < size_x; itr++) {
					result[iy] += this->elems[iy][itr] * vector[itr];
				}
			}
		}
#		endif
		// // matrix - matrix
#		if (1)
		inline cmat operator+(cmat& matrix) const {
			mat result(static_cast<val>(0));
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] + matrix[iy][ix];
				}
			}
			return result;
		}
		inline cmat operator-(cmat& matrix) const {
			mat result(static_cast<val>(0));
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					result[iy][ix] = this->elems[iy][ix] - matrix[iy][ix];
				}
			}
			return result;
		}
		inline cmat operator*(cmat& matrix) const {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					for (v1u itr = 0u; itr < size_x; itr++) {
						result[iy][ix] += this->elems[iy][itr] * matrix[itr][ix];
					}
				}
			}
			return result;
		}
		inline mat& operator+=(cmat& matrix) {
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					this->elems[iy][ix] += matrix[iy][ix];
				}
			}
			return *this;
		}
		inline mat& operator-=(cmat& matrix) {
			for (v1u iy; iy < size_y; iy++) {
				for (v1u ix; ix < size_x; ix++) {
					this->elems[iy][ix] -= matrix[iy][ix];
				}
			}
			return *this;
		}
		inline mat& operator*=(cmat& matrix) {
			for (v1u iy = 0u; iy < size_x; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					for (v1u itr = 0u; itr < size_x; itr++) {
						this->elems[iy][ix] += this->elems[iy][itr] * matrix[itr][ix];
					}
				}
			}
			return *this;
		}
		inline mat& operator=(cmat& matrix) {
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
#		if (1)
		inline vec& operator[](csize idx) { return this->elems[idx]; }
		inline cvec& operator[](csize idx) const { return this->elems[idx]; }
#		endif
		// input_output
#		if (1)
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
#	if (1)
		static constexpr inline cmat make_ident(vtype value = static_cast<vtype>(1)) {
			mat result(static_cast<vtype>(0));
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			for (v1u idiag = 0u; idiag < get_size_max(); idiag++) {
				result[idiag][idiag] = value;
			}
			return result;
		}
		static constexpr inline cmat make_trpos(cmat& matrix) {
			mat result(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					result[iy][ix] = matrix[ix][iy];
				}
			}
			return result;
		}
		static constexpr inline cmat make_inver(cmat& matrix) {
			static_assert(size_x == size_y, "not square matrix cannot be inversed");
			mat_xy<size_x, size_y * 2> result(static_cast<val>(0));
			for (v1u iy = 0; iy < size_y; iy++) {
				for (v1u ix = 0; ix < size_x; ix++) {
					result[iy][ix] = matrix[iy][ix];
				}
				result[iy][iy + size_y] = static_cast<val>(1);
			}
			{
				for (v1u iy = 0u, ix = 0u; iy < size_y && ix < size_x; iy++, ix++) {
					v1u itr = iy;
					while (result[iy][ix] == static_cast<val>(0)) {
						if (itr == size_y) {
							itr = iy;
							if (ix++ == size_x) { return matrix; }
						}
					}
					result.trpos();
					if (result[iy][ix] != static_cast<val>(0)) {
						val temp = result[iy][ix];
						for (v1u itr = 0u; itr < size_x; itr++)
							result[iy][ix] /= temp;
					}
					for (v1u itr_y = 0; itr_y < size_y; itr_y++) {
						if (itr_y == iy) { continue; }
						val temp = result[itr_y][ix];
						for (v1u itr_x = 0u; itr_x < size_x; itr_x++) {
							result[itr_y][itr_x] -= temp * result[iy][itr_x];
						}
					}
				}
			}
			mat inversed(static_cast<val>(0));
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					inversed[iy][ix] = result[iy][ix + size_y];
				}
			}
			return inversed;
		}
		template<csize diag_size>
		static constexpr inline cmat make_scale(cvec_s<diag_size>& diagonal) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			static_assert(diag_size <= get_size_min(), "diagonal is too big for this matrix");
			mat result = make_ident();
			for (v1u idiag = 0u; idiag < diag_size; idiag++) {
				result[idiag][idiag] *= diagonal[idiag];
			}
			return result;
		}
		template<csize vec_size>
		static constexpr inline cmat make_coord(cvec_s<vec_size>& vector) {
			static_assert(size_x > 1u, "matrix is too small for this operation");
			static_assert(vec_size <= size_y, "vector is too big for this matrix");
			mat result = make_ident();
			for (v1u itr = 0u; itr < vec_size; itr++) {
				result[size_x - 1u][itr] += vector[itr];
			}
			return result;
		}
		static constexpr inline cmat make_rotat_x(cv1f& value) { // rotate around axis "x"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");

			mat result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[1][1] = +cos_x; result[1][2] = -sin_x;
			result[2][1] = +sin_x; result[2][2] = +cos_x;

			return result;
		}
		static constexpr inline cmat make_rotat_y(cv1f& value) { // rotate around axis "y"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");

			mat result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[0][0] = +cos_x; result[0][2] = +sin_x;
			result[2][0] = -sin_x; result[2][2] = +cos_x;

			return result;
		}
		static constexpr inline cmat make_rotat_z(cv1f& value) { // rotate around axis "z"
			static_assert(size_x >= 2u && size_y >= 2u, "matrix size is too small for this operation");

			mat result = make_ident();
			cv1f cos_x = NW_MATH_COS(value);
			cv1f sin_x = NW_MATH_SIN(value);
			result[0][0] = +cos_x; result[0][1] = -sin_x;
			result[1][0] = +sin_x; result[1][1] = +cos_x;

			return result;
		}
		static constexpr inline cmat make_rotat_xyz(cvec_s<3u>& vector) { // rotate around "x" "y" "z"
			static_assert(size_x >= 3u && size_y >= 3u, "matrix size is too small for this operation");
			/// i advice you not to change this order;
			/// we were suffering two weeks with "drunk" gfx_cam because of this;
			return make_rotat_y(vector[1]) * make_rotat_x(vector[0]) * make_rotat_z(vector[2]);
		}
		static constexpr inline cmat_xy<size_x - 1u, size_y - 1u> make_erase(cmat& matrix, v1u erase_x, v1u erase_y) {
			mat_xy<size_x - 1u, size_y - 1u> result(static_cast<vtype>(0));
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
		inline mat& ident(v1f value) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			for (v1u idiag = 0u; idiag < get_size_max(); idiag++) {
				this->elems[idiag][idiag] = value;
			}
			return *this;
		}
		inline mat& inver() {
			static_assert(size_x == size_y, "not square matrix cannot be inversed");
			return *this;
		}
		inline mat& trpos() {
			mat matrix(*this);
			for (v1u iy = 0u; iy < size_y; iy++) {
				for (v1u ix = 0u; ix < size_x; ix++) {
					this->elems[iy][ix] = matrix[ix][iy];
				}
			}
			return *this;
		}
		template<csize vec_size>
		inline mat& scale(cvec_s<vec_size>& vector) {
			static_assert(size_x == size_y, "this operation cannot be used for a not square matrix");
			static_assert(vec_size <= size_y, "vector size is too big for this operation");
			for (v1u idiag = 0u; idiag < vec_size; idiag++) {
				this->elems[idiag][idiag] *= value;
			}
			return *this;
		}
		template<csize vec_size>
		inline mat& coord(cvec_s<vec_size>& vector) {
			static_assert(size_x > 1u, "matrix size is too small for this operation");
			static_assert(vec_size <= size_y, "vector size is too big for this operation");
			for (v1u itr = 0u; itr < vec_size; itr++) {
				this->elems[size_x - 1u][itr] += vector[itr];
			}
			return *this;
		}
		inline cmat_xy<size_x - 1u, size_y - 1u> erase(v1u erase_x, v1u erase_y) const { return make_erase(*this, erase_x, erase_y); }
#	endif
	public:
		vec elems[size_y];
	};
}
namespace NW
{
	// value matrix bool 8 bit
	typedef mat_t<v1b, 2u>      m2b;
	typedef mat_t<v1b, 3u>      m3b;
	typedef mat_t<v1b, 4u>      m4b;
	typedef const m2b          cm2b;
	typedef const m3b          cm3b;
	typedef const m4b          cm4b;
	// value matrix signed int 8 bit
	typedef mat_t<v1s8, 2u>    m2s8;
	typedef mat_t<v1s8, 3u>    m3s8;
	typedef mat_t<v1s8, 4u>    m4s8;
	typedef const m2s8        cm2s8;
	typedef const m3s8        cm3s8;
	typedef const m4s8        cm4s8;
	// value matrix unsigned int 8 bit
	typedef mat_t<v1u8, 2u>    m2u8;
	typedef mat_t<v1u8, 3u>    m3u8;
	typedef mat_t<v1u8, 4u>    m4u8;
	typedef const m2u8        cm2u8;
	typedef const m3u8        cm3u8;
	typedef const m4u8        cm4u8;
	// value matrix signed int 16 bit
	typedef mat_t<v1s16, 2u>  m2s16;
	typedef mat_t<v1s16, 3u>  m3s16;
	typedef mat_t<v1s16, 4u>  m4s16;
	typedef const m2s16      cm2s16;
	typedef const m3s16      cm3s16;
	typedef const m4s16      cm4s16;
	// value matrix unsigned int 16 bit
	typedef mat_t<v1u16, 2u>  m2u16;
	typedef mat_t<v1u16, 3u>  m3u16;
	typedef mat_t<v1u16, 4u>  m4u16;
	typedef const m2u16      cm2u16;
	typedef const m3u16      cm3u16;
	typedef const m4u16      cm4u16;
	// value matrix signed int 32 bit
	typedef mat_t<v1s32, 2u>  m2s32;
	typedef mat_t<v1s32, 3u>  m3s32;
	typedef mat_t<v1s32, 4u>  m4s32;
	typedef const m2s32      cm2s32;
	typedef const m3s32      cm3s32;
	typedef const m4s32      cm4s32;
	// value matrix unsigned int 32 bit
	typedef mat_t<v1u32, 2u>  m2u32;
	typedef mat_t<v1u32, 3u>  m3u32;
	typedef mat_t<v1u32, 4u>  m4u32;
	typedef const m2u32      cm2u32;
	typedef const m3u32      cm3u32;
	typedef const m4u32      cm4u32;
	// value matrix signed int 64 bit
	typedef mat_t<v1s64, 2u>  m2s64;
	typedef mat_t<v1s64, 3u>  m3s64;
	typedef mat_t<v1s64, 4u>  m4s64;
	typedef const m2s64      cm2s64;
	typedef const m3s64      cm3s64;
	typedef const m4s64      cm4s64;
	// value matrix unsigned int 64 bit
	typedef mat_t<v1u64, 2u>  m2u64;
	typedef mat_t<v1u64, 3u>  m3u64;
	typedef mat_t<v1u64, 4u>  m4u64;
	typedef const m2u64      cm2u64;
	typedef const m3u64      cm3u64;
	typedef const m4u64      cm4u64;
	// value matrix float 32 bit
	typedef mat_t<v1f32, 2u>  m2f32;
	typedef mat_t<v1f32, 3u>  m3f32;
	typedef mat_t<v1f32, 4u>  m4f32;
	typedef const m2f32      cm2f32;
	typedef const m3f32      cm3f32;
	typedef const m4f32      cm4f32;
	// value matrix float 64 bit
	typedef mat_t<v1f64, 2u>  m2f64;
	typedef mat_t<v1f64, 3u>  m3f64;
	typedef mat_t<v1f64, 4u>  m4f64;
	typedef const m2f64      cm2f64;
	typedef const m3f64      cm3f64;
	typedef const m4f64      cm4f64;
	// default value matrix signed integer
	typedef m2s32          m2s;
	typedef m3s32          m3s;
	typedef m4s32          m4s;
	typedef const m2s32   cm2s;
	typedef const m3s32   cm3s;
	typedef const m4s32   cm4s;
	// default value matrix unsigned integer
	typedef m2u32          m2u;
	typedef m3u32          m3u;
	typedef m4u32          m4u;
	typedef const m2u32   cm2u;
	typedef const m3u32   cm3u;
	typedef const m4u32   cm4u;
	// default value matrix float
	typedef m2f32          m2f;
	typedef m3f32          m3f;
	typedef m4f32          m4f;
	typedef const m2f32   cm2f;
	typedef const m3f32   cm3f;
	typedef const m4f32   cm4f;
}
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_MATRIX_H