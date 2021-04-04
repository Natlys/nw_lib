#ifndef NW_CORE_VECTOR_H
#define NW_CORE_VECTOR_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
#	if (NW_GAPI & NW_GAPI_OGL && 0)
#		include "../ext/glm/vector_relational.hpp"
namespace NW
{
	/// value vector struct template
	template<typename vtype, csize size_x>
	struct vec_t : public glm::vec<size_x, vtype, glm::defaultp>
	{
		static_assert(size_x > 1u, "vector must be greater than a single value");
		using val = vtype;
		using cval = const val;
		using vec = vec_t<vtype, size_x>;
		using cvec = const vec;
	public:
		// --getters
		static constexpr inline csize get_size() { return size_x; }
		inline cval get_len() const {
			return glm::length(*this);
		}
		static constexpr inline cv1f get_dot(cvec& vector_0, cvec& vector_1) {
			return glm::dot(vector_0, vector_1)
		}
		inline cv1f get_dot(cvec& vector) const {
			return glm::dot(*this, vector);
		}
		static constexpr inline cvec make_norm(cvec& vector) {
			return glm::normalize(vector);
		}
		static constexpr inline cvec make_cross(cvec& vector_0, cvec& vector_1) {
			static_assert(size_x >= 3, "not enough dimensions for cross product");
			return glm::cross(vector_0, vector_1);
		}
		// --methods
		inline vec& norm() {
			*this = glm::normalize(*this);
			return *this;
		}
		inline vec& cross(cvec& vector) {
			*this = glm::cross(*this, vector);
			return *this;
		}
	};
}
#	else
namespace NW
{
	/// value vector struct template
	template<typename vtype, csize size_x>
	struct vec_t
	{
		static_assert(size_x > 1u, "vector must be greater than a single value");
		using val = vtype;
		using cval = const val;
		using vec = vec_t<vtype, size_x>;
		using cvec = const vec;
	public:
		constexpr inline vec_t(cval& value = static_cast<val>(0))
		{
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] = value;
			}
		}
		constexpr inline vec_t(const std::initializer_list<val>& value) : vec_t()
		{
			for (v1u ix = 0u; ix < value.size(); ix++) {
				this->elems[ix] = *(value.begin() + ix);
			}
		}
		constexpr inline vec_t(cvec& cpy) = default;
		constexpr inline vec_t(vec&& cpy) = default;
		inline ~vec_t() = default;
		// --getters
		static constexpr inline csize get_size() { return size_x; }
		inline cval get_len() const {
			val len = static_cast<val>(0);
			for (v1u ix = 0u; ix < size_x; ix++) {
				len += NW_MATH_POW(this->elems[ix], 2);
			}
			return NW_MATH_ROOT(len, 2);
		}
		static constexpr inline cv1f get_dot(cvec& vector_0, cvec& vector_1) {
			v1f dot = static_cast<v1f>(0);
			for (v1u ix = 0u; ix < size_x; ix++) {
				dot += vector_0[ix] * vector_1[ix];
			}
			return dot;
		}
		inline cv1f get_dot(cvec& vector) const {
			v1f dot = static_cast<v1f>(0);
			for (v1u ix = 0u; ix < size_x; ix++) {
				dot += this->elems[ix] * vector[ix];
			}
			return dot;
		}
		static constexpr inline cvec make_norm(cvec& vector) {
			vec result = vector / vector.get_len();
			return result;
		}
		static constexpr inline cvec make_cross(cvec& vector_0, cvec& vector_1) {
			static_assert(size_x >= 3, "not enough dimensions for cross product");
			vec result(static_cast<val>(0));
			result[0] = (vector_0[1] * vector_1[2]) - (vector_0[2] * vector_1[1]);
			result[1] = (vector_0[2] * vector_1[0]) - (vector_0[0] * vector_1[2]);
			result[2] = (vector_0[0] * vector_1[1]) - (vector_0[1] * vector_1[0]);
			return result;
		}
		// --operators
		// math
		// // vector - value
		inline cvec operator+(cval& value) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] + value;
			}
			return result;
		}
		inline cval operator-(cval& value) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] - value;
			}
			return result;
		}
		inline cvec operator*(cval& value) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] * value;
			}
			return result;
		}
		inline cvec operator/(cval& value) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] / value;
			}
			return result;
		}
		inline vec& operator+=(cval& value) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] += value;
			}
			return *this;
		}
		inline vec& operator-=(cval& value) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] -= value;
			}
			return *this;
		}
		inline vec& operator*=(cval& value) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] *= value;
			}
			return *this;
		}
		inline vec& operator/=(cval& value) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] /= value;
			}
			return *this;
		}
		inline vec& operator=(cval& value) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] = value;
			}
			return *this;
		}
		// // vector - vector
		inline cvec operator+(cvec& vector) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] + vector[ix];
			}
			return result;
		}
		inline cvec operator-(cvec& vector) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] - vector[ix];
			}
			return result;
		}
		inline cvec operator*(cvec& vector) const {
			vec result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] * vector[ix];
			}
			return result;
		}
		inline cvec operator/(cvec& vector) const {
			val result(static_cast<val>(0));
			for (v1u ix = 0u; ix < size_x; ix++) {
				result[ix] = this->elems[ix] / vector[ix];
			}
			return result;
		}
		inline vec& operator+=(cvec& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] += vector[ix];
			}
			return *this;
		}
		inline vec& operator-=(cvec& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] -= vector[ix];
			}
			return *this;
		}
		inline vec& operator*=(cvec& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] *= vector[ix];
			}
			return *this;
		}
		inline vec& operator/=(cvec& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] /= vector[ix];
			}
			return *this;
		}
		inline vec& operator=(cvec& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) {
				this->elems[ix] = vector[ix];
			}
			return *this;
		}
		// // vector only
		inline cvec operator+() const {
			vec result(*this); for (v1f ix = 0u; ix < size_x; ix++) { result[ix] = +this->elems[ix]; }
			return result;
		}
		inline cvec operator-() const {
			vec result(*this);
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = -this->elems[ix]; }
			return result;
		}
		// logic
		inline v1b operator==(cvec& vector) const {
			for (v1u ix = 0u; ix < size_x; ix++) {
				if (this->elems[ix] != vector[ix]) { return false; }
			}
			return true;
		}
		// accessors
		inline val& operator[](csize idx) { return this->elems[idx]; }
		inline cval& operator[](csize idx) const { return this->elems[idx]; }
		// input_output
		inline std::ostream& operator<<(std::ostream& stm) const {
			for (v1u ix = 0u; ix < size_x; ix++) {
				stm << this->elems[ix] << "\t";
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
		// --methods
		inline vec& norm() {
			*this /= this->get_len();
			return *this;
		}
		inline vec& cross(cvec& vector) { return *this = make_cross(*this, vector);; }
	public:
		val elems[size_x];
	};
}
#	endif	// NW_GAPI
namespace NW
{
	// values boolean 8 bit
	typedef vec_t<v1b, 2u>        v2b;
	typedef vec_t<v1b, 3u>        v3b;
	typedef vec_t<v1b, 4u>        v4b;
	typedef const v2b            cv2b;
	typedef const v3b            cv3b;
	typedef const v4b            cv4b;
	// values signed int 8 bit
	typedef vec_t<v1s8, 2u>      v2s8;
	typedef vec_t<v1s8, 3u>      v3s8;
	typedef vec_t<v1s8, 4u>      v4s8;
	typedef const v2s8          cv2s8;
	typedef const v3s8          cv3s8;
	typedef const v4s8          cv4s8;
	// values unsigned int 8 bit
	typedef vec_t<v1u8, 2u>      v2u8;
	typedef vec_t<v1u8, 3u>      v3u8;
	typedef vec_t<v1u8, 4u>      v4u8;
	typedef const v2u8          cv2u8;
	typedef const v3u8          cv3u8;
	typedef const v4u8          cv4u8;
	// values signed int 16 bit
	typedef vec_t<v1s16, 2u>    v2s16;
	typedef vec_t<v1s16, 3u>    v3s16;
	typedef vec_t<v1s16, 4u>    v4s16;
	typedef const v2s16        cv2s16;
	typedef const v3s16        cv3s16;
	typedef const v4s16        cv4s16;
	// values unsigned int 16 bit
	typedef vec_t<v1u16, 2u>    v2u16;
	typedef vec_t<v1u16, 3u>    v3u16;
	typedef vec_t<v1u16, 4u>    v4u16;
	typedef const v2u16        cv2u16;
	typedef const v3u16        cv3u16;
	typedef const v4u16        cv4u16;
	// values signed int 32 bit
	typedef vec_t<v1s32, 2u>    v2s32;
	typedef vec_t<v1s32, 3u>    v3s32;
	typedef vec_t<v1s32, 4u>    v4s32;
	typedef const v2s32        cv2s32;
	typedef const v3s32        cv3s32;
	typedef const v4s32        cv4s32;
	// values unsigned int 32 bit
	typedef vec_t<v1u32, 2u>    v2u32;
	typedef vec_t<v1u32, 3u>    v3u32;
	typedef vec_t<v1u32, 4u>    v4u32;
	typedef const v2u32        cv2u32;
	typedef const v3u32        cv3u32;
	typedef const v4u32        cv4u32;
	// values signed int 64 bit
	typedef vec_t<v1s64, 2u>    v2s64;
	typedef vec_t<v1s64, 3u>    v3s64;
	typedef vec_t<v1s64, 4u>    v4s64;
	typedef const v2s64        cv2s64;
	typedef const v3s64        cv3s64;
	typedef const v4s64        cv4s64;
	// values unsigned int 64 bit
	typedef vec_t<v1u64, 2u>    v2u64;
	typedef vec_t<v1u64, 3u>    v3u64;
	typedef vec_t<v1u64, 4u>    v4u64;
	typedef const v2u64        cv2u64;
	typedef const v3u64        cv3u64;
	typedef const v4u64        cv4u64;
	// values float 32 bit
	typedef vec_t<v1f32, 2u>    v2f32;
	typedef vec_t<v1f32, 3u>    v3f32;
	typedef vec_t<v1f32, 4u>    v4f32;
	typedef const v2f32        cv2f32;
	typedef const v3f32        cv3f32;
	typedef const v4f32        cv4f32;
	// values float 64 bit
	typedef vec_t<v1f64, 2u>    v2f64;
	typedef vec_t<v1f64, 3u>    v3f64;
	typedef vec_t<v1f64, 4u>    v4f64;
	typedef const v2f64        cv2f64;
	typedef const v3f64        cv3f64;
	typedef const v4f64        cv4f64;
	// default values signed int
	typedef v2s32            v2s;
	typedef v3s32            v3s;
	typedef v4s32            v4s;
	typedef const v2s32     cv2s;
	typedef const v3s32     cv3s;
	typedef const v4s32     cv4s;
	// default values unsigned int
	typedef v2u32            v2u;
	typedef v3u32            v3u;
	typedef v4u32            v4u;
	typedef const v2u32     cv2u;
	typedef const v3u32     cv3u;
	typedef const v4u32     cv4u;
	// default values float
	typedef v2f32            v2f;
	typedef v3f32            v3f;
	typedef v4f32            v4f;
	typedef const v2f32     cv2f;
	typedef const v3f32     cv3f;
	typedef const v4f32     cv4f;
}
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_VECTOR_H