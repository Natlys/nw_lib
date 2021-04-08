#ifndef NW_CORE_VECTOR_H
#define NW_CORE_VECTOR_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
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
#	if (1)
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
		static constexpr inline cv1f get_cos(cvec& vector_0, cvec& vector_1) {
			return get_dot(vector_0, vector_1) / (vector_0.get_len() * vector_1.get_len());
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
#	endif
		// --operators
		// math
#	if (1)
		// // vector - value
#		if (1)
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
#		endif
		// // vector - vector
#		if (1)
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
#		endif
#		if (1)
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
#		endif
		// logic
#		if (1)
		inline v1b operator==(cvec& vector) const {
			for (v1u ix = 0u; ix < size_x; ix++) {
				if (this->elems[ix] != vector[ix]) { return false; }
			}
			return true;
		}
#		endif
		// accessors
#		if (1)
		inline val& operator[](csize idx) { return this->elems[idx]; }
		inline cval& operator[](csize idx) const { return this->elems[idx]; }
#		endif
		// input_output
#		if (1)
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
#		endif
#	endif
		// --core_methods
#	if (1)
		inline vec& norm() {
			*this /= this->get_len();
			return *this;
		}
		inline vec& cross(cvec& vector) { return *this = make_cross(*this, vector);; }
#	endif
	public:
		val elems[size_x];
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
#	define NW_INVOKER(tname, ITERATOR) \
	ITERATOR(v2##tname, v1##tname, 2u)  \
	ITERATOR(v3##tname, v1##tname, 3u)  \
	ITERATOR(v4##tname, v1##tname, 4u)  \
// that's it
#	endif	// NW_FOREACH & NW_INVOKER & NW_ITERATOR
namespace NW
{
#	define NW_ITERATOR(tname, vname, size_x)   \
	typedef vec_t<vname, size_x> tname; \
	typedef const tname       c##tname; \
// that's it
	NW_FOREACH(NW_INVOKER, NW_ITERATOR);
#	undef NW_ITERATOR
}
#	undef NW_INVOKER
#	undef NW_FOREACH
#else
#	error "nw_lib_core.hpp must be included before this header"
#endif	// NW_LIB_CORE_HPP
#endif	// NW_CORE_VECTOR_H