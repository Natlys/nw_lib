#ifndef NC_LIB_VALUE_HXX
#	define NC_LIB_VALUE_HXX
#	include "../nc_lib_pch.hxx"
#	if (defined(NC_LIB_CORE_HXX))
#		if (NC_LANG & NC_LANG_CPP)
extern "C" {
#		endif	/* NC_LANG_CPP */
/* defines */
/** constants **/
#   	define NC_ZERO     0
#   	define NC_UNIT     1
#   	define NC_FALSE    0
#   	define NC_TRUTH    1
#   	define NC_VOID_VAL NC_ZERO
/** functions **/
#       define NC_VAL_HASH(val, buf) ({  \
			buf = NC_ZERO;               \
			size_t size = NC_ZERO;       \
			byte_t* data = (byte_t*)val; \
			while(size < sizeof(val)) {  \
				buf += ~(*data) * 8u;    \
				data = data + 1u;        \
				size = size + 1u;        \
			}                            \
			buf = NC_NUM_ABS(buf);       \
		})
#       define NC_VAL_SWAP(val0, val1) ({       \
            typeof(val0) cpy;                   \
            memmove(&cpy, &val0, sizeof(val0)); \
            memmove(&val0, &val1, sizeof(cpy)); \
            memmove(&val1, &cpy, sizeof(val1)); \
        })
/* typedefs */
#		if (!defined(NC_FOREACH) && !defined(NC_INVOKER) && !defined(NC_ITERATE))
#			define NC_FOREACH(INVOKER, ITERATE)        \
				INVOKER(byte, char, ITERATE)           \
				INVOKER(sbyte, signed char, ITERATE)   \
				INVOKER(ubyte, unsigned char, ITERATE) \
				INVOKER(data, unsigned char*, ITERATE) \
				INVOKER(indx, unsigned long, ITERATE)  \
				INVOKER(flag, unsigned long, ITERATE)  \
				INVOKER(hand, void*, ITERATE)          \
				INVOKER(nil, void, ITERATE)            \
				INVOKER(ptr, void*, ITERATE)           \
				INVOKER(bit, unsigned int, ITERATE)    \
				INVOKER(num, float, ITERATE)           \
				INVOKER(s08, signed char, ITERATE)     \
				INVOKER(u08, unsigned char, ITERATE)   \
				INVOKER(s16, signed short, ITERATE)    \
				INVOKER(u16, unsigned short, ITERATE)  \
				INVOKER(s32, signed int, ITERATE)      \
				INVOKER(u32, unsigned int, ITERATE)    \
				INVOKER(s64, signed long, ITERATE)     \
				INVOKER(u64, unsigned long, ITERATE)   \
				INVOKER(f32, float, ITERATE)           \
				INVOKER(f64, double, ITERATE)          \
				INVOKER(b, unsigned int, ITERATE)      \
				INVOKER(s, signed int, ITERATE)        \
				INVOKER(u, unsigned int, ITERATE)      \
				INVOKER(f, float, ITERATE)             \
				INVOKER(n, double, ITERATE)            \
/* that is it */
#		define NC_INVOKER(tname, vtype, ITERATE) \
			ITERATE(tname, vtype)                \
			ITERATE(v1##tname, vtype)            \
/* that is it */
#		define NC_ITERATE(tname, vtype)         \
			typedef vtype            tname##_t; \
			typedef const tname##_t tname##_tc; \
/* that is it */
NC_FOREACH(NC_INVOKER, NC_ITERATE);
// typedef unsigned long size_t;
typedef const size_t   size_tc;
// typedef signed long ssize_t;
typedef const ssize_t ssize_tc;
typedef unsigned long  usize_t;
typedef const usize_t usize_tc;
#			undef NC_ITERATE
#			undef NC_INVOKER
#			undef NC_FOREACH
#		else
#			error "macroses named above must not be defined here"
#		endif	/* NC_FOREACH & NC_INVOKER & NC_ITERATE */
#		if (NC_LANG & NC_LANG_CPP)
}
#		endif	/* NC_LANG_CPP */
#   else
#	    error "nc_lib_core.hxx must be included before this header"
#	endif	/* NC_LIB_CORE_HXX */
#endif	/* NC_LIB_VALUE_HXX */