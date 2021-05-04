#ifndef NW_NUM_IMAGINARY_H
#define NW_NUM_IMAGINARY_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_num_vec.h"
#	include "nw_num_mat.h"
namespace NW
{
	/// number_imaginary_type
	template<size_tc dims>
	struct num_imag_t
	{
	public:
		// --imaginary_number
		using inum_t = num_imag_t<dims>;
		using inum_tc = const inum_t;
		template<size_tc inum_dims> using num_imag_tc = const num_imag_t<dims>;
		// --real_part
		using real_t = v1f;
		using real_tc = const real_t;
		// --imag_part
		using imag_t = num_vec_t<v1f, dims>;
		using imag_tc = const imag_t;
		// --vector
		using vec_t = num_vec_t<v1f, dims>;
		using vec_tc = const vec_t;
		// --matrix
		using mat_t = num_mat_t<v1f, dims, dims>;
		using mat_tc = const mat_t;
	public:
		// --ctor_dtor
#	if (NW_TRUE)
		constexpr inline num_imag_t() : m_real(real_t()), m_imag(imag_t()) { }
		constexpr inline num_imag_t(real_tc real) : num_imag_t() { operator=(real); }
		constexpr inline num_imag_t(imag_tc& imag) : num_imag_t() { operator=(imag); }
		constexpr inline num_imag_t(real_tc real, imag_tc& imag) : num_imag_t() { m_real = real; m_imag = imag; }
		constexpr inline num_imag_t(inum_tc& inum) : num_imag_t() { operator=(inum); }
		constexpr inline num_imag_t(inum_t&& inum) : num_imag_t() { operator=(inum); }
		template<size_tc inum_dims> num_imag_t(num_imag_tc<inum_dims>& inum) : num_imag_t() { operator=(inum); ; }
		template<size_tc inum_dims> num_imag_t(num_imag_t<inum_dims>&& inum) : num_imag_t() { operator=(inum); }
		inline ~num_imag_t() = default;
#	endif	// ctor_dtor
		// --getters
#	if (NW_TRUE)
		// // --info
		static constexpr inline size_tc get_dcount() { return dims; }
		// // --real_part
		inline inum_tc get_add(real_tc real) const { return make_add(*this, real); }
		inline inum_tc get_sub(real_tc real) const { return make_sub(*this, real); }
		inline inum_tc get_mul(real_tc real) const { return make_mul(*this, real); }
		inline inum_tc get_div(real_tc real) const { return make_div(*this, real); }
		inline real_tc get_dst(inum_tc& inum) const { return make_dst(*this, inum); }
		inline real_tc get_dot(inum_tc& inum) const { return make_dot(*this, inum); }
		inline real_tc get_len() const { return make_len(*this); }
		// // --imag_part
		inline inum_tc get_add(imag_tc& iamg) const { return make_add(*this, imag); }
		inline inum_tc get_sub(imag_tc& iamg) const { return make_sub(*this, imag); }
		inline inum_tc get_mul(imag_tc& iamg) const { return make_mul(*this, imag); }
		inline inum_tc get_div(imag_tc& iamg) const { return make_div(*this, imag); }
		// // --imaginary_number
		inline inum_tc get_add(inum_tc& inum) const { return make_add(*this, inum); }
		inline inum_tc get_sub(inum_tc& inum) const { return make_sub(*this, inum); }
		inline inum_tc get_mul(inum_tc& inum) const { return make_mul(*this, inum); }
		inline inum_tc get_div(inum_tc& inum) const { return make_div(*this, inum); }
		inline inum_tc get_conj() const { return make_conj(*this); }
		inline inum_tc get_inver() const { return make_inver(*this); }
#	endif	// getters
		// --setters
#	if (NW_TRUE)
		// // --real_part
		inline inum_t& set_add(real_tc real) const { return *this = make_add(*this, real); }
		inline inum_t& set_sub(real_tc real) const { return *this = make_sub(*this, real); }
		inline inum_t& set_mul(real_tc real) const { return *this = make_mul(*this, real); }
		inline inum_t& set_div(real_tc real) const { return *this = make_div(*this, real); }
		// // --imag_part
		inline inum_t& set_add(imag_tc& iamg) const { return *this = make_add(*this, imag); }
		inline inum_t& set_sub(imag_tc& iamg) const { return *this = make_sub(*this, imag); }
		inline inum_t& set_mul(imag_tc& iamg) const { return *this = make_mul(*this, imag); }
		inline inum_t& set_div(imag_tc& iamg) const { return *this = make_div(*this, imag); }
		// // --imaginary_number
		inline inum_t& set_add(inum_tc& inum) const { return *this = make_add(*this, inum); }
		inline inum_t& set_sub(inum_tc& inum) const { return *this = make_sub(*this, inum); }
		inline inum_t& set_mul(inum_tc& inum) const { return *this = make_mul(*this, inum); }
		inline inum_t& set_div(inum_tc& inum) const { return *this = make_div(*this, inum); }
#	endif	// setters
		// --predicates
#	if (NW_TRUE)
#	endif	// predicates
		// --operators
#	if (NW_TRUE)
		// // --mathematics
#		if (NW_TRUE)
		// // // --real_part
		inline inum_tc operator+(real_tc& real) const { return make_add(*this, real); }
		inline inum_tc operator-(real_tc& real) const { return make_sub(*this, real); }
		inline inum_tc operator*(real_tc& real) const { return make_mul(*this, real); }
		inline inum_tc operator/(real_tc& real) const { return make_div(*this, real); }
		inline inum_t& operator+=(real_tc& real) { return *this = make_add(*this, real); }
		inline inum_t& operator-=(real_tc& real) { return *this = make_sub(*this, real); }
		inline inum_t& operator*=(real_tc& real) { return *this = make_mul(*this, real); }
		inline inum_t& operator/=(real_tc& real) { return *this = make_div(*this, real); }
		// // // --imag_part
		inline inum_tc operator+(imag_tc& imag) const { return make_add(*this, imag); }
		inline inum_tc operator-(imag_tc& imag) const { return make_sub(*this, imag); }
		inline inum_tc operator*(imag_tc& imag) const { return make_mul(*this, imag); }
		inline inum_tc operator/(imag_tc& imag) const { return make_div(*this, imag); }
		inline inum_t& operator+=(imag_tc& imag) { return *this = make_add(*this, imag); }
		inline inum_t& operator-=(imag_tc& imag) { return *this = make_sub(*this, imag); }
		inline inum_t& operator*=(imag_tc& imag) { return *this = make_mul(*this, imag); }
		inline inum_t& operator/=(imag_tc& imag) { return *this = make_div(*this, imag); }
		// // // --imaginary_numbers
		inline inum_tc operator+(inum_tc& inum) const { return make_add(*this, inum); }
		inline inum_tc operator-(inum_tc& inum) const { return make_sub(*this, inum); }
		inline inum_tc operator*(inum_tc& inum) const { return make_mul(*this, inum); }
		inline inum_tc operator/(inum_tc& inum) const { return make_div(*this, inum); }
		inline inum_t& operator+=(inum_tc& inum) { return *this = make_add(*this, inum); }
		inline inum_t& operator-=(inum_tc& inum) { return *this = make_sub(*this, inum); }
		inline inum_t& operator*=(inum_tc& inum) { return *this = make_mul(*this, inum); }
		inline inum_t& operator/=(inum_tc& inum) { return *this = make_div(*this, inum); }
		inline inum_t& operator+()       { m_real = +m_real; m_imag = +m_imag; return *this; }
		inline inum_tc operator+() const { return inum_t(+m_real, +m_imag); }
		inline inum_t& operator-()       { m_real = -m_real; m_imag = -m_imag; return *this; }
		inline inum_tc operator-() const { return inum_t(-m_real, -m_imag); }
#		endif	// mathematics
		// // --assignment
#		if (NW_TRUE)
		// // // --real_part
		inline inum_t& operator=(real_tc real) { m_real = real; return *this; }
		// // // --imag_part
		inline inum_t& operator=(imag_tc& imag) { m_imag = imag; return *this; }
		// // // --imaginary_numbers
		inline inum_t& operator=(inum_tc& inum) { m_real = inum.m_real; m_imag = inum.m_imag; return *this; }
		inline inum_t& operator=(inum_t&& inum) { m_real = inum.m_real; m_imag = inum.m_imag; return *this; }
		template<size_tc inum_dims> inum_t& operator=(num_imag_tc<inum_dims>& inum) { m_real = inum.m_real; m_imag = inum.m_imag; return *this; }
		template<size_tc inum_dims> inum_t& operator=(num_imag_t<inum_dims>&& inum) { m_real = inum.m_real; m_imag = inum.m_imag; return *this; }
#		endif	// assignment
		// // --conversion
#		if (NW_TRUE)
		inline operator real_t&()        { return m_real; }
		inline operator real_tc&() const { return m_real; }
		inline operator imag_t&()        { return m_imag; }
		inline operator imag_tc&() const { return m_imag; }
		template<size_tc inum_dims> operator num_imag_t<inum_dims>() const { return num_imag_t(m_real, m_imag); }
#		endif	// conversion
		// // --input_output
#		if (NW_TRUE)
		inline std::ostream& operator<<(std::ostream& stm) const { stm << "{" << m_real << m_imag; stm << "};"; return stm; }
		inline std::istream& operator>>(std::istream& stm)       { stm >> m_real >> m_imag; return stm; }
#		endif	// input_output
#	endif	// operators
		// --core_methods
#	if (NW_TRUE)
		// // --real_part
		static constexpr inline inum_tc make_add(inum_tc& inum, real_tc real) {
			inum_t res;
			res.m_real = inum.m_real + real;
			res.m_imag = inum.m_imag + 0.0f;
			return res;
		}
		static constexpr inline inum_tc make_sub(inum_tc& inum, real_tc real) {
			inum_t res;
			res.m_real = inum.m_real - real;
			res.m_imag = inum.m_imag - 0.0f;
			return res;
		}
		static constexpr inline inum_tc make_mul(inum_tc& inum, real_tc real) {
			inum_t res;
			res.m_imag = inum.m_real * real;
			res.m_imag = inum.m_imag * real;
			return res;
		}
		static constexpr inline inum_tc make_div(inum_tc& inum, real_tc real) {
			inum_t res;
			res.m_imag = inum.m_real / real;
			res.m_imag = inum.m_imag / real;
			return res;
		}
		static constexpr inline real_tc make_len(inum_tc& inum) {
			real_t res(inum.m_real * inum.m_real);
			for (v1u idim(0u); idim < dims; idim++) { res += inum.m_imag[idim] * inum.m_imag[idim]; }
			return NW_NUM_ROOT(res, 2u);
		}
		static constexpr inline real_tc make_dst(inum_tc& inum0, inum_tc& inum1) {
			real_t res((inum1.m_real * inum1.m_real) - (inum0.m_real * inum0.m_real));
			for (v1u idim(0u); idim < dims; idim++) { res += (inum1.m_imag[idim] - inum0.m_imag[idim]) * (inum1.m_imag[idim] - inum0.m_imag[idim]); }
			return NW_NUM_ROOT(res, 2u);
		}
		static constexpr inline real_tc make_dot(inum_tc& inum0, inum_tc& inum1) {
			real_t res(inum0.m_real * inum1.m_real);
			for (v1u idim(0u); idim < dims; idim++) { res += inum0.m_imag[idim] * inum1.m_imag[idim]; }
			return res;
		}
		// // --imag_part
		static constexpr inline inum_tc make_add(inum_tc& inum, imag_tc& imag) {
			inum_t res;
			res.m_real = inum.m_real + 0.0f;
			res.m_imag = inum.m_imag + imag;
			return res;
		}
		static constexpr inline inum_tc make_sub(inum_tc& inum, imag_tc& imag) {
			inum_t res;
			res.m_real = inum.m_real - 0.0f;
			res.m_imag = inum.m_imag - imag;
			return res;
		}
		static constexpr inline inum_tc make_mul(inum_tc& inum, imag_tc& imag) {
			inum_t res;
			//res.m_real = (inum.m_real * 0.0f) - imag_t::make_dot(inum.m_imag, imag);
			//res.m_imag = (inum.m_real * imag) + (0.0f * imag) - imag_t::make_crs(inum.m_imag, imag);
			res.m_real = -imag_t::make_dot(inum.m_imag, imag);
			res.m_imag = (inum.m_real * imag) - imag_t::make_crs(inum.m_imag, imag);
			return res;
		}
		static constexpr inline inum_tc make_div(inum_tc& inum, imag_tc& imag) {
			inum_t res;
			res.m_real = (inum.m_real / 0.0f) - imag_t::make_dot(inum.m_imag, imag);
			res.m_imag = (inum.m_real / imag) + (0.0f / imag) - imag_t::make_crs(inum.m_imag, imag);
			return res;
		}
		// // --imaginary_number
		static constexpr inline inum_tc make_add(inum_tc& inum0, inum_tc& inum1) {
			inum_t res;
			res.m_real = inum0.m_real + inum1.m_real;
			res.m_imag = inum0.m_imag + inum1.m_imag;
			return res;
		}
		static constexpr inline inum_tc make_sub(inum_tc& inum0, inum_tc& inum1) {
			inum_t res;
			res.m_real = inum0.m_real + inum1.m_real;
			res.m_imag = inum0.m_imag + inum1.m_imag;
			return res;
		}
		static constexpr inline inum_tc make_mul(inum_tc& inum0, inum_tc& inum1) {
			inum_t res;
			res.m_real = (inum0.m_real * inum1.m_real) - imag_t::make_dot(inum0.m_imag, inum1.m_imag);
			res.m_imag = (inum0.m_real * inum1.m_imag) + (inum1.m_real * inum0.m_imag) + imag_t::make_crs(inum0.m_imag, inum1.m_imag);
			return res;
		}
		static constexpr inline inum_tc make_div(inum_tc& inum0, inum_tc& inum1) {
			inum_t res;
			res.m_real = (inum0.m_real / inum1.m_real) - imag_t::make_dot(inum0.m_imag, inum1.m_imag);
			res.m_imag = (inum0.m_real / inum1.m_imag) + (inum1.m_real / inum0.m_imag) + imag_t::make_crs(inum0.m_imag, inum1.m_imag);
			return res;
		}
		static constexpr inline inum_tc make_conj(inum_tc& inum) { return inum_tc(inum.m_real, -inum.m_imag); }
		static constexpr inline inum_tc make_norm(inum_tc& inum) { return inum / make_len(inum); }
		static constexpr inline inum_tc make_diff(inum_tc& inum0, inum_tc& inum1) { return inum_tc(); }
		static constexpr inline inum_tc make_inver(inum_tc& inum) { return make_conj(inum) / make_len(inum); }
		static constexpr inline inum_tc make_rotat(real_tc angle, imag_tc& axis, vec_tc& vec) {
			inum_t rotat(NW_NUM_COS(angle), axis.get_norm() * NW_NUM_SIN(angle));
			inum_t inver(make_inver(rotat));
			inum_t res = make_mul(rotat, vec);
			//res = make_mul(res, inver);
			return res;
		}
		// // --matrix
		static constexpr inline mat_tc make_mat(inum_tc& inum) {
			mat_t res;
			return res;
		}
#	endif	// core_methods
	public:
		real_t m_real;
		imag_t m_imag;
	};
	// --typedefs
	template<size_tc dims> using num_imag_tc = const num_imag_t<dims>;
	// --mathematics
	template<typename tname, size_tc dims> num_imag_tc<dims> operator+(tname val, num_imag_tc<dims>& inum) { return inum.operator+(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator-(tname val, num_imag_tc<dims>& inum) { return inum.operator-(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator*(tname val, num_imag_tc<dims>& inum) { return inum.operator*(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator/(tname val, num_imag_tc<dims>& inum) { return inum.operator/(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator+=(tname val, num_imag_tc<dims>& inum) { return inum.operator+=(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator-=(tname val, num_imag_tc<dims>& inum) { return inum.operator-=(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator*=(tname val, num_imag_tc<dims>& inum) { return inum.operator*=(val); }
	template<typename tname, size_tc dims> num_imag_tc<dims> operator/=(tname val, num_imag_tc<dims>& inum) { return inum.operator/=(val); }
	// --input_output
	template<size_tc dims> std::ostream& operator<<(std::ostream& stm, num_imag_tc<dims>& inum) { return inum.operator<<(stm); }
	template<size_tc dims> std::istream& operator>>(std::istream& stm, num_imag_t<dims>& inum) { return inum.operator>>(stm); }
	// --typedefs
	typedef num_imag_t<1u> inum1d_t;
	typedef num_imag_t<2u> inum2d_t;
	typedef num_imag_t<3u> inum3d_t;
}
#endif	// NW_API
#endif	// NW_NUM_IMAGINARY_H