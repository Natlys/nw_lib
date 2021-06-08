#ifndef NC_LIB_NUMBER_HXX
#	define NC_LIB_NUMBER_HXX
#	include "../nc_lib_pch.hxx"
#	if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* includes */
#   	include <stdint.h>
#   	include <float.h>
#   	include <math.h>
#   	include <limits.h>
/* defines */
/** constants **/
#		define NC_NUM_EUL ( NC_CAST_V1F(2.718281828) )
#		define NC_NUM_PIN ( NC_CAST_V1F(3.141592653) )
#		define NC_NUM_RAD ( NC_CAST_V1F(57.29577951) )
/** functions **/
/*** general  ***/
#		define NC_NUM_IMOD(num, mod) ( num % mod )
#		define NC_NUM_FMOD(num, mod) ( num > mod ? (num - mod) : (num < -mod ? (num + mod) : num) )
#		define NC_NUM_FABS(num) ( num > NC_ZERO ? +num : -num )
#		define NC_NUM_FEXP(num) ( exp(num) )
#		define NC_NUM_FPOW(num, base) ( pow(num, base) )
#		define NC_NUM_FROT(num, base) ( pow(num, NC_CAST_V1F(NC_UNIT) / base) )
#		define NC_NUM_IS_DIV(num, div) ( num % div == NC_ZERO )
#		define NC_NUM_DIRS(num0, num1) ( num0 > num1 ? -NC_UNIT : +NC_UNIT )
#		define NC_NUM_DIFF(num0, num1) ( NC_NUM_FABS(NC_CAST(num0, v1s_t) - NC_CAST(num1, v1s_t)) )
#		define NC_NUM_SWAP(num0, num1) ({ num0 = num1 - num0; num1 = num1 - num0; num0 = num1 + num0; })
#		define NC_NUM_LERP(lower, upper, value) ( (upper - lower) * (1.0f - value) )
#		define NC_NUM_CLIP(num, lower, upper)   ( NC_NUM_MIN(NC_NUM_MAX(num, lower), upper) )
#		define NC_NUM_CLIP_SNORM(num)   ( NC_NUM_CLIP(num, -NC_UNIT, +NC_UNIT) )
#		define NC_NUM_CLIP_UNORM(num)   ( NC_NUM_CLIP(num, NC_ZERO, NC_UNIT) )
#   	define NC_NUM_ALIG(data, alig) ( NC_ZERO \
			+ (NC_CAST_SIZE(data)                \
			+ (NC_CAST_SIZE(alig) - NC_UNIT))    \
			& ~(NC_CAST_SIZE(alig) - NC_UNIT)    \
		)
/*** comparison  ***/
#		define NC_NUM_MIN(num0, num1)  ( num0 < num1 ? num0 : num1 )
#		define NC_NUM_MAX(num0, num1)  ( num0 > num1 ? num0 : num1 )
#		define NC_NUM_MORE(num0, num1) ( num0 > num1 ) /* more than */
#		define NC_NUM_TEQU(num0, num1) ( num0 == num1 ) /* truth equal to */
#		define NC_NUM_FEQU(num0, num1) ( num0 != num1 ) /* false equal to */
#		define NC_NUM_LESS(num0, num1) ( num0 < num1 ) /* less than */
#		define NC_NUM_MEQU(num0, num1) ( num0 >= num1 ) /* more than or equal to */
#		define NC_NUM_LEQU(num0, num1) ( num0 <= num1 ) /* less than or equal to */
#		define NC_NUM_ISIDE(num, lower, upper)    ( ((num) >= (lower)) && ((num) <= (upper)) )
#		define NC_NUM_OSIDE(num, lower, upper)    ( ((num) <= (lower)) || ((num) >= (upper)) )
/*** trigonometry  ***/
#		define NC_NUM_TO_DEG(angle) ( NC_CAST_V1F(angle) / NC_NUM_PIN * NC_CAST_V1F(180.0))
#		define NC_NUM_TO_RAD(angle) ( NC_CAST_V1F(angle) * NC_NUM_PIN / NC_CAST_V1F(180.0))
#		define NC_NUM_ANGLE(angle)  ( NC_NUM_TO_RAD(angle) )
#		define NC_NUM_CSIN(angle)   ( cosf(NC_NUM_ANGLE(angle)) )
#		define NC_NUM_FSIN(angle)   ( sinf(NC_NUM_ANGLE(angle)) )
#		define NC_NUM_FTAN(angle)   ( NC_NUM_FSIN(angle) / NC_NUM_CSIN(angle) )
#		define NC_NUM_CTAN(angle)   ( NC_NUM_CSIN(angle) / NC_NUM_FSIN(angle) )
#		define NC_NUM_FASIN(ratio)  ( asinf(ratio) )
#		define NC_NUM_FCSIN(ratio)  ( csinf(ratio) )
/*** combinatorics  ***/
#		define NC_NUM_FACT(num) ( nc_num_fact(num) )
#		define NC_NUM_PERM(from, what, repeat) ( \
			repeat ? ( NC_UNIT                   \
				/ NC_NUM_FPOW(from)              \
			) : ( NC_UNIT                        \
				/ NC_NUM_FACT(from)              \
				/ NC_NUM_FACT(from - what)       \
			)                                    \
/* NC_NUM_PERM */
#		define NC_NUM_COMB(from, what, repeat) ( \
			repeat ? ( NC_UNIT                   \
				/ NC_NUM_FACT(what + from + 1u)  \
				/ NC_NUM_FACT(what)              \
				/ NC_NUM_FACT(from - 1u)         \
			) :                                  \
			( NC_UNIT                            \
				/ NC_NUM_FACT(from)              \
				/ NC_NUM_FACT(what)              \
				/ NC_NUM_FACT(from - what)       \
			)                                    \
		)                                        \
/*** NC_NUM_COMB ***/
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else	/* nc_lib_num.hxx is included without nc_lib_core.hxx */
#	    error "nc_lib_core.hxx must be included before this header"
#	endif	/* NC_LIB_CORE_HXX */
/* end_of_file */
#endif	/* NC_LIB_NUMBER_HXX */