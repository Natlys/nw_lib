#ifndef NW_CORE_VECTOR_H
#define NW_CORE_VECTOR_H
#include "nw_lib_pch.hpp"
#if (defined NW_LIB_CORE_HPP)
namespace NW
{
	/// value vector struct template
	template<typename vtype, cv1u size_x>
	struct t_vec
	{
		// static_assert(size_x > 1u, "vector must be greater than a single value");
		using val_t = vtype;
		using val_tc = const val_t;
		using vec_t = t_vec<vtype, size_x>;
		using vec_tc = const vec_t;
	public:
		constexpr inline t_vec(val_tc& value = static_cast<val_t>(0))
		{
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] = value; }
		}
		constexpr inline t_vec(const std::initializer_list<val_t>& value) : t_vec()
		{
			for (v1u ix = 0u; ix < value.size(); ix++) { this->elems[ix] = *(value.begin() + ix); }
		}
		constexpr inline t_vec(vec_tc& copy) = default;
		constexpr inline t_vec(vec_t&& copy) = default;
		inline ~t_vec() = default;
		// --getters
#	if (NW_TRUE)
		static constexpr inline cv1u get_size() { return size_x; }
		inline val_tc get_len() const {
			val_t len = static_cast<val_t>(0);
			for (v1u ix = 0u; ix < size_x; ix++) { len += NW_MATH_POW(this->elems[ix], 2); }
			return NW_MATH_ROOT(len, 2);
		}
		static constexpr inline cv1f get_dot(vec_tc& vector_0, vec_tc& vector_1) {
			v1f dot = static_cast<v1f>(0);
			for (v1u ix = 0u; ix < size_x; ix++) { dot += vector_0[ix] * vector_1[ix]; }
			return dot;
		}
		static constexpr inline cv1f get_cos(vec_tc& vector_0, vec_tc& vector_1) {
			return get_dot(vector_0, vector_1) / (vector_0.get_len() * vector_1.get_len());
		}
		inline cv1f get_dot(vec_tc& vector) const {
			v1f dot = static_cast<v1f>(0);
			for (v1u ix = 0u; ix < size_x; ix++) { dot += this->elems[ix] * vector[ix]; }
			return dot;
		}
		static constexpr inline vec_tc make_norm(vec_tc& vector) { return vector / vector.get_len(); }
		static constexpr inline vec_tc make_cross(vec_tc& vector_0, vec_tc& vector_1) {
			static_assert(size_x >= 3, "not enough dimensions for cross product");
			vec_t result(static_cast<val_t>(0));
			result[0] = (vector_0[1] * vector_1[2]) - (vector_0[2] * vector_1[1]);
			result[1] = (vector_0[2] * vector_1[0]) - (vector_0[0] * vector_1[2]);
			result[2] = (vector_0[0] * vector_1[1]) - (vector_0[1] * vector_1[0]);
			return result;
		}
#	endif
		// --operators
		// math
#	if (NW_TRUE)
		// // vector - value
#		if (NW_TRUE)
		inline vec_tc operator+(val_tc& value) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] + value; }
			return result;
		}
		inline val_tc operator-(val_tc& value) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] - value; }
			return result;
		}
		inline vec_tc operator*(val_tc& value) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] * value; }
			return result;
		}
		inline vec_tc operator/(val_tc& value) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] / value; }
			return result;
		}
		inline vec_t& operator+=(val_tc& value) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] += value; }
			return *this;
		}
		inline vec_t& operator-=(val_tc& value) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] -= value; }
			return *this;
		}
		inline vec_t& operator*=(val_tc& value) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] *= value; }
			return *this;
		}
		inline vec_t& operator/=(val_tc& value) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] /= value; }
			return *this;
		}
		inline vec_t& operator=(val_tc& value) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] = value; }
			return *this;
		}
#		endif
		// // vector - vector
#		if (NW_TRUE)
		inline vec_tc operator+(vec_tc& vector) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] + vector[ix]; }
			return result;
		}
		inline vec_tc operator-(vec_tc& vector) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] - vector[ix]; }
			return result;
		}
		inline vec_tc operator*(vec_tc& vector) const {
			vec_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] * vector[ix]; }
			return result;
		}
		inline vec_tc operator/(vec_tc& vector) const {
			val_t result(static_cast<val_t>(0));
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = this->elems[ix] / vector[ix]; }
			return result;
		}
		inline vec_t& operator+=(vec_tc& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] += vector[ix]; }
			return *this;
		}
		inline vec_t& operator-=(vec_tc& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] -= vector[ix]; }
			return *this;
		}
		inline vec_t& operator*=(vec_tc& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] *= vector[ix]; }
			return *this;
		}
		inline vec_t& operator/=(vec_tc& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] /= vector[ix]; }
			return *this;
		}
		inline vec_t& operator=(vec_tc& vector) {
			for (v1u ix = 0u; ix < size_x; ix++) { this->elems[ix] = vector[ix]; }
			return *this;
		}
#		endif
#		if (NW_TRUE)
		// // vector only
		inline vec_tc operator+() const {
			vec_t result(*this); for (v1f ix = 0u; ix < size_x; ix++) { result[ix] = +this->elems[ix]; }
			return result;
		}
		inline vec_tc operator-() const {
			vec_t result(*this);
			for (v1u ix = 0u; ix < size_x; ix++) { result[ix] = -this->elems[ix]; }
			return result;
		}
#		endif
		// logic
#		if (NW_TRUE)
		inline v1b operator==(vec_tc& vector) const {
			for (v1u ix = 0u; ix < size_x; ix++) { if (this->elems[ix] != vector[ix]) { return false; }}
			return true;
		}
#		endif
		// accessors
#		if (NW_TRUE)
		inline val_t& operator[](cv1u idx)        { return this->elems[idx]; }
		inline val_tc& operator[](cv1u idx) const { return this->elems[idx]; }
#		endif
		// input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const {
			for (v1u ix = 0u; ix < size_x; ix++) { stm << this->elems[ix] << "\t"; }
			return stm;
		}
		inline std::istream& operator>>(std::istream& stm) {
			for (v1u ix = 0u; ix < size_x; ix++) { stm >> this->elems[ix]; stm.get(); }
			return stm;
		}
#		endif
#	endif
		// --core_methods
#	if (NW_TRUE)
		inline vec_t& norm() { return *this /= this->get_len(); }
		inline vec_t& cross(vec_tc& vector) { return *this = make_cross(*this, vector);; }
#	endif
	public:
		val_t elems[size_x];
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
	typedef t_vec<vname, size_x> tname; \
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